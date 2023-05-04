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
	//Boss->SetTexture("blimp_idle_0001.png");														
	Boss->SetScaleToTexture("taurus_idle_0001.png");

	//GetTransform()->SetLocalPosition(float4(300.0f, 0));											
																			
																							
	//FSM																							
	//INTRO
	StartFuncPtr[static_cast<int>(TaurusState::IDLE)] = std::bind(&Taurus::Idle_Start, this);
	UpdateFuncPtr[static_cast<int>(TaurusState::IDLE)] = std::bind(&Taurus::Idle_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(TaurusState::IDLE)] = std::bind(&Taurus::Idle_End, this);

	//SHOOT
	StartFuncPtr[static_cast<int>(TaurusState::STING)] = std::bind(&Taurus::String_Start, this);
	UpdateFuncPtr[static_cast<int>(TaurusState::STING)] = std::bind(&Taurus::String_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(TaurusState::STING)] = std::bind(&Taurus::String_End, this);
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
	Boss->SetScaleToTexture("taurus_idle_0001.png");
}
void Taurus::Idle_Update(float _DeltaTime)
{
	if (StingInterval < GetLiveTime())
	{
		NextState = TaurusState::STING;
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

void Taurus::String_Start()
{
	ResetLiveTime();
	StingInterval = GameEngineRandom::MainRandom.RandomFloat(3.0f, 8.0f);
	Boss->SetScaleToTexture("taurus_attack_0012.png");
}
void Taurus::String_Update(float _DeltaTime)
{
	if (GetLiveTime() > 1.0f)
	{
		NextState = TaurusState::IDLE;

	}
}
void Taurus::String_End()
{

}