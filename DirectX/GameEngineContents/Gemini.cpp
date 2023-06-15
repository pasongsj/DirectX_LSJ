#include "PrecompileHeader.h"
#include "Gemini.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "GameContentsEnemyRenderer.h"

#include "GeminiOrb.h"

Gemini::Gemini() 
{
}

Gemini::~Gemini() 
{
}

void Gemini::Start()
{
	SetPhase(4);

	BossA = CreateComponent<GameContentsEnemyRenderer>(CupHeadRendererOrder::Boss);
	BossA->CreateAnimation({ .AnimationName = "Idle",  .SpriteName = "Gemini_Idle", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
	BossA->CreateAnimation({ .AnimationName = "AttackA",  .SpriteName = "Gemini_AttackA",  .FrameInter = 0.05f, .Loop = false , .ScaleToTexture = true });
	BossA->ChangeAnimation("Idle");
	
	
	Orb = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::Boss);
	Orb->CreateAnimation({ .AnimationName = "IdleIntro",  .SpriteName = "Orb_Idle_Intro", .FrameInter = 0.05f, .Loop = false , .ScaleToTexture = true });
	Orb->CreateAnimation({ .AnimationName = "IdleLoop",  .SpriteName = "Orb_Idle_Loop",.FrameInter = 0.05f, .Loop = true , .ScaleToTexture = true });
	Orb->CreateAnimation({ .AnimationName = "IdleLeave",  .SpriteName = "Orb_Idle_Leave", .FrameInter = 0.05f, .Loop = false , .ScaleToTexture = true });
	Orb->ChangeAnimation("IdleIntro");
	Orb->GetTransform()->SetLocalPosition(float4(0, -45, 0));
	
	BossB = CreateComponent<GameContentsEnemyRenderer>(CupHeadRendererOrder::Boss);
	BossB->CreateAnimation({ .AnimationName = "Idle",  .SpriteName = "Gemini_Idle", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
	BossB->CreateAnimation({ .AnimationName = "AttackB",  .SpriteName = "Gemini_AttackB",  .FrameInter = 0.05f, .Loop = false , .ScaleToTexture = true });
	BossB->ChangeAnimation("Idle", true, 15);


	BossCollisionA = CreateComponent<GameEngineCollision>(CupHeadCollisionOrder::Enemy);
	BossCollisionA->SetColType(ColType::AABBBOX2D);
	BossCollisionA->GetTransform()->SetLocalScale(float4(220, 520, 1));
	BossCollisionA->SetName("GeminiCollisionA");


	BossCollisionB = CreateComponent<GameEngineCollision>(CupHeadCollisionOrder::Enemy);
	BossCollisionB->SetColType(ColType::AABBBOX2D);
	BossCollisionB->GetTransform()->SetLocalScale(float4(220, 520, 1));
	BossCollisionB->SetName("GeminiCollisionA");




	//FSM

	//IDLE
	StartFuncPtr[static_cast<int>(GeminiState::IDLE)] = std::bind(&Gemini::Idle_Start, this);
	UpdateFuncPtr[static_cast<int>(GeminiState::IDLE)] = std::bind(&Gemini::Idle_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(GeminiState::IDLE)] = std::bind(&Gemini::Idle_End, this);

	//SHOOT
	StartFuncPtr[static_cast<int>(GeminiState::ATTACK)] = std::bind(&Gemini::Attack_Start, this);
	UpdateFuncPtr[static_cast<int>(GeminiState::ATTACK)] = std::bind(&Gemini::Attack_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(GeminiState::ATTACK)] = std::bind(&Gemini::Attack_End, this);



	GetTransform()->SetLocalPosition(float4(0, 0, 600));

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


// fsm
void Gemini::Idle_Start()
{
	BossA->ChangeAnimation("Idle");
	BossB->ChangeAnimation("Idle", true, 15);
	isOrbIntroEnd = false;
}

void Gemini::Idle_Update(float _DeltaTime)
{

	float4 MoveVec = GetHildaMove(_DeltaTime) + float4(300.0f, 0, 600);
	GetTransform()->SetLocalPosition(MoveVec);
	
	//y축 회전 + y축 진동
	//x=acosθy=bsinθ

	float SpinTime = -GetLiveTime() * 4;

	BossA->GetTransform()->SetLocalPosition(float4(100 * cosf(SpinTime), -50 * sinf(SpinTime), -sinf(SpinTime)));
	BossCollisionA->GetTransform()->SetLocalPosition(float4(100 * cosf(SpinTime), -50 * sinf(SpinTime), - sinf(SpinTime)));

	BossB->GetTransform()->SetLocalPosition(float4(-100 * cosf(SpinTime), 50 * sinf(SpinTime), sinf(SpinTime)));
	BossCollisionB->GetTransform()->SetLocalPosition(float4(-100 * cosf(SpinTime), 50 * sinf(SpinTime), sinf(SpinTime)));

	if (false == isOrbIntroEnd && Orb->IsAnimationEnd())
	{
		isOrbIntroEnd = true;
		Orb->ChangeAnimation("IdleLoop");
	}

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
	BossA->ChangeAnimation("AttackA");
	BossB->ChangeAnimation("AttackB");
	Orb->ChangeAnimation("IdleLeave");
	isAttack = true;
}

void Gemini::Attack_Update(float _DeltaTime)
{
	if (true == BossA->IsAnimationEnd())
	{
		NextState = GeminiState::IDLE;
	}
	if (true == Orb->IsAnimationEnd())
	{
		Orb->Death();
	}
}

void Gemini::Attack_End()
{
	std::shared_ptr<GeminiOrb> AttackOrb = GetLevel()->CreateActor<GeminiOrb>(CupHeadActorOrder::EnemyWeapon);
	AttackOrb->GetTransform()->SetLocalPosition(float4(-300, 0, 500));

}

void Gemini::Attack(int _Dmg)
{
	BossA->MakeBright();
	BossB->MakeBright();
	GameEnemy::Attack(_Dmg);
}
