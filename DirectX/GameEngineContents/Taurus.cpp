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

void Taurus::Start()
{
	Boss = CreateComponent<GameEngineSpriteRenderer>();
	Boss->CreateAnimation({ .AnimationName = "Idle", .TextureName = "taurus_idle_00", .Start = 1,.End = 16, .InterTime = 0.05f, .Loop = true });
	Boss->CreateAnimation({ .AnimationName = "ChargeAttack", .TextureName = "taurus_attack_00", .Start = 1,.End = 10, .InterTime = 0.05f, .Loop = false });
	Boss->CreateAnimation({ .AnimationName = "Attack", .TextureName = "taurus_attack_00", .Start = 11,.End = 21, .InterTime = 0.05f, .Loop = false });
	
	Boss->ChangeAnimation("Idle");
	//Boss->SetTexture("blimp_idle_0001.png");														
	//Boss->SetScaleToTexture("taurus_idle_0001.png");

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
	DestPos = CurPos + float4(-500, 0);
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