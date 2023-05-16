#include "PrecompileHeader.h"
#include "Gemini.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "GeminiOrb.h"
#include <GameEngineCore/GameEngineLevel.h>

#include "GeminiObject.h"

Gemini::Gemini() 
{
}

Gemini::~Gemini() 
{
}

void Gemini::Start()
{
	BossA = GetLevel()->CreateActor<GeminiObject>("BossA");
	BossA->GetTransform()->SetLocalPosition(float4(100, 0));
	BossA->ChangeGeminiAnimation("Idle");
	BossA->SetGeminiController(DynamicThis<GameEngineActor>());

	//BossA->GetTransform()->SetParent(GetTransform());

	BossB = GetLevel()->CreateActor<GeminiObject>("BossB");
	BossB->GetTransform()->SetLocalPosition(float4(-100, 0));
	BossB->ChangeGeminiAnimation("Idle", 15);
	BossB->SetGeminiController(DynamicThis<GameEngineActor>());

	//BossB->GetTransform()->SetParent(GetTransform());

	


	//FSM

	//IDLE
	StartFuncPtr[static_cast<int>(GeminiState::IDLE)] = std::bind(&Gemini::Idle_Start, this);
	UpdateFuncPtr[static_cast<int>(GeminiState::IDLE)] = std::bind(&Gemini::Idle_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(GeminiState::IDLE)] = std::bind(&Gemini::Idle_End, this);

	//SHOOT
	StartFuncPtr[static_cast<int>(GeminiState::ATTACK)] = std::bind(&Gemini::Attack_Start, this);
	UpdateFuncPtr[static_cast<int>(GeminiState::ATTACK)] = std::bind(&Gemini::Attack_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(GeminiState::ATTACK)] = std::bind(&Gemini::Attack_End, this);

	Orb = GetLevel()->CreateActor<GeminiOrb>(2);
	Orb->SetGeminiController(DynamicThis<GameEngineActor>());
	//Orb->GetTransform()->SetParent(GetTransform());
}

void Gemini::Update(float _DeltaTime)
{
	if (nullptr == BossA || nullptr == BossB || nullptr == Orb)
	{
		MsgAssert("Gemini 랜더러가 제대로 생성되지 않았습니다.");
		return;
	}
	UpdateState(_DeltaTime);
}

void Gemini::Render(float _DletaTime)
{
	
}


void Gemini::UpdateState(float _DeltaTime)
{
	if (CurState != NextState)
	{
		// CurState에 대한 ending
		EndFuncPtr[static_cast<int>(CurState)]();

		// NextState에 대한 Start
		StartFuncPtr[static_cast<int>(NextState)]();

		// State변경
		CurState = NextState;
		return;
	}

	UpdateFuncPtr[static_cast<int>(CurState)](_DeltaTime);
}


void Gemini::Idle_Start()
{
	BossA->ChangeGeminiAnimation("Idle");
	BossB->ChangeGeminiAnimation("Idle",15);
}

void Gemini::Idle_Update(float _DeltaTime)
{
	IdleMoveTime += _DeltaTime;


	float4 MoveVec = float4(cosf(IdleMoveTime * 2.5f) * SpinSpeed, CircleMove * (1 - sinf(IdleMoveTime * 2.5f)) * SpinSpeed) + float4(300.0f, 0);
	//GetTransform()->SetLocalPosition(float4(cosf(IdleMoveTime * 2.5f) * SpinSpeed, CircleMove * (1 - sinf(IdleMoveTime * 2.5f)) * SpinSpeed) + float4(300.0f, 0)); // 힐다베르그  8자 움직임

	float degree = (IdleMoveTime * 2.5f) / GameEngineMath::PIE2 + GameEngineMath::PIE / 4;

	if (LastShare < degree)
	{
		int RandNum = GameEngineRandom::MainRandom.RandomInt(0, 9);
		if (0 == (RandNum & 1))
		{
			CircleMove = 1;
		}
		else
		{
			CircleMove = -1;
		}
		LastShare = static_cast<int>(degree) + 1;
	}

	//y축 회전 + y축 진동
	//x=acosθy=bsinθ

	float SpinTime = -GetLiveTime() * 4;
	BossA->GetTransform()->SetLocalPosition(MoveVec + float4(100 * cosf(SpinTime), -50 * sinf(SpinTime)/*, -1-sinf(SpinTime)*/));
	BossB->GetTransform()->SetLocalPosition(MoveVec + float4(-100 * cosf(SpinTime), 50 * sinf(SpinTime)/*, -1+sinf(SpinTime)*/));
	if (false == Orb->IsAttack())
	{
		Orb->GetTransform()->SetLocalPosition(MoveVec +float4(0,-45));
	}
	// A > B
	if (-sinf(SpinTime) > sinf(SpinTime))
	{
		BossA->SetOrder(1);
		BossB->SetOrder(3);
	}
	else
	{
		BossA->SetOrder(3);
		BossB->SetOrder(1);

	}
	//// 랜더 순서를 변경하기 위해 setorder
	//BossA->SetOrder(static_cast<int>(-10*sinf(SpinTime)));
	//BossB->SetOrder(static_cast<int>(10 * sinf(SpinTime)));

	if (false == isAttack && GetLiveTime() > 5.6f)
	{
		NextState = GeminiState::ATTACK;
	}
}

void Gemini::Idle_End()
{

}


void Gemini::Attack_Start()
{
	BossA->ChangeGeminiAnimation("AttackA");
	BossB->ChangeGeminiAnimation("AttackB");
	isAttack = true;
	Orb->Attack();
}

void Gemini::Attack_Update(float _DeltaTime)
{
	if (true == BossA->isGeminiAnimationEnd())
	{
		NextState = GeminiState::IDLE;
	}
}

void Gemini::Attack_End()
{

}