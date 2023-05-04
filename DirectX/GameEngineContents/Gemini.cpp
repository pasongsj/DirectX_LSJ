#include "PrecompileHeader.h"
#include "Gemini.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

Gemini::Gemini() 
{
}

Gemini::~Gemini() 
{
}

void Gemini::Start()
{
	BossA = CreateComponent<GameEngineSpriteRenderer>();
	BossA->SetScaleToTexture("gemini_idle_0016.png");
	BossA->GetTransform()->SetLocalPosition(float4(-100, 0));

	BossB = CreateComponent<GameEngineSpriteRenderer>();
	BossB->SetScaleToTexture("gemini_idle_0001.png");
	BossB->GetTransform()->SetLocalPosition(float4(100, 0));


	//FSM

	//IDLE
	StartFuncPtr[static_cast<int>(GeminiState::IDLE)] = std::bind(&Gemini::Idle_Start, this);
	UpdateFuncPtr[static_cast<int>(GeminiState::IDLE)] = std::bind(&Gemini::Idle_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(GeminiState::IDLE)] = std::bind(&Gemini::Idle_End, this);

	//SHOOT
	StartFuncPtr[static_cast<int>(GeminiState::SHOOT)] = std::bind(&Gemini::Shoot_Start, this);
	UpdateFuncPtr[static_cast<int>(GeminiState::SHOOT)] = std::bind(&Gemini::Shoot_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(GeminiState::SHOOT)] = std::bind(&Gemini::Shoot_End, this);
}

void Gemini::Update(float _DeltaTime)
{

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

}

void Gemini::Idle_Update(float _DeltaTime)
{
	IdleMoveTime += _DeltaTime;

	GetTransform()->SetLocalPosition(float4(cosf(IdleMoveTime * 2.5f) * SpinSpeed, CircleMove * (1 - sinf(IdleMoveTime * 2.5f)) * SpinSpeed) + float4(300.0f, 0)); // 힐다베르그  8자 움직임

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
	BossA->GetTransform()->SetLocalPosition(float4(-100 * cosf(SpinTime), 50 * sinf(SpinTime), 100 * sinf(SpinTime)));
	BossB->GetTransform()->SetLocalPosition(float4(100 * cosf(SpinTime), -50 * sinf(SpinTime), -100 * sinf(SpinTime)));

	// 랜더 순서를 변경하기 위해 setorder
	BossA->SetOrder(static_cast<int>(-100*sinf(SpinTime)));
	BossB->SetOrder(static_cast<int>(100 * sinf(SpinTime)));
}

void Gemini::Idle_End()
{

}


void Gemini::Shoot_Start()
{

}

void Gemini::Shoot_Update(float _DeltaTime)
{

}

void Gemini::Shoot_End()
{

}