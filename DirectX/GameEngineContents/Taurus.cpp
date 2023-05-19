#include "PrecompileHeader.h"
#include "Taurus.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>

Taurus::Taurus() 
{
}

Taurus::~Taurus() 
{
}

void Taurus::MakeSprite()
{
	if (nullptr == GameEngineSprite::Find("Taurus_Idle"))
	{

		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources\\Texture\\stage1\\Boss\\Hilda\\Taurus");


		GameEngineSprite::LoadFolder("Taurus_Idle", NewDir.GetPlusFileName("Idle").GetFullPath());
		GameEngineSprite::LoadFolder("Taurus_Charge", NewDir.GetPlusFileName("Attack\\Charge").GetFullPath());
		GameEngineSprite::LoadFolder("Taurus_Attack", NewDir.GetPlusFileName("Attack\\Attack").GetFullPath());

	}
}



void Taurus::Start()
{
	SetPhase(2);
	MakeSprite();
	Boss = CreateComponent<GameEngineSpriteRenderer>();
	Boss->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "Taurus_Idle", .FrameInter = 0.05f, .Loop = true , .ScaleToTexture = true });
	Boss->CreateAnimation({ .AnimationName = "ChargeAttack", .SpriteName = "Taurus_Charge", .FrameInter = 0.05f, .Loop = false , .ScaleToTexture = true });
	Boss->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "Taurus_Attack",  .FrameInter = 0.05f, .Loop = false , .ScaleToTexture = true });
	
	Boss->ChangeAnimation("Idle");

	//GetTransform()->SetLocalPosition(float4(300.0f, 0));											
																			
																							
	//FSM																							
	//INTRO
	StartFuncPtr[static_cast<int>(TaurusState::IDLE)] = std::bind(&Taurus::Idle_Start, this);
	UpdateFuncPtr[static_cast<int>(TaurusState::IDLE)] = std::bind(&Taurus::Idle_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(TaurusState::IDLE)] = std::bind(&Taurus::Idle_End, this);

	//SHOOT
	StartFuncPtr[static_cast<int>(TaurusState::ATTACK)] = std::bind(&Taurus::Attack_Start, this);
	UpdateFuncPtr[static_cast<int>(TaurusState::ATTACK)] = std::bind(&Taurus::Attack_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(TaurusState::ATTACK)] = std::bind(&Taurus::Attack_End, this);
}

void Taurus::Update(float _DeltaTime)
{

	UpdateState(_DeltaTime);

}

void Taurus::Render(float _DeltaTime)
{

}

void Taurus::UpdateState(float _DeltaTime)
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


void Taurus::Idle_Start()
{
	ResetLiveTime();
	Boss->ChangeAnimation("Idle");
	//Boss->SetScaleToTexture("taurus_idle_0001.png");
}
void Taurus::Idle_Update(float _DeltaTime)
{
	if (AttackInterval < GetLiveTime())
	{
		NextState = TaurusState::ATTACK;
	}

	GetTransform()->SetLocalPosition(GetHildaMove(_DeltaTime) + float4(300.0f, 0));
}
void Taurus::Idle_End()
{

}

void Taurus::Attack_Start()
{
	ResetLiveTime();
	AttackInterval = GameEngineRandom::MainRandom.RandomFloat(5.0f, 8.0f);
	Boss->ChangeAnimation("ChargeAttack");
	//Boss->SetScaleToTexture("taurus_attack_0012.png");

	CurPos = GetTransform()->GetLocalPosition();
	DestPos = CurPos + float4(-200, 0);
	isCharge = true;
}
void Taurus::Attack_Update(float _DeltaTime)
{
	if (true == isCharge && true == Boss->IsAnimationEnd())
	{
		isCharge = false;
		Boss->ChangeAnimation("Attack");
	}
	else if(false == isCharge)
	{
		GetTransform()->SetLocalPosition(float4::Zero.LerpClamp(CurPos, DestPos, GetLiveTime()*2));
		if (true == Boss->IsAnimationEnd())
			//if (GetLiveTime() > 1.0f)
		{
			NextState = TaurusState::IDLE;

		}

	}
}
void Taurus::Attack_End()
{
	GetTransform()->SetLocalPosition(CurPos);
}