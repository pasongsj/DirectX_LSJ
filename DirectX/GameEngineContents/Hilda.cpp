#include "PrecompileHeader.h"
#include "Hilda.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

Hilda::Hilda() 
{
}																				 
																				 
Hilda::~Hilda() 																 
{
}																				
																				
void Hilda::Start()																
{
	// 랜더러 설정																
	Boss = CreateComponent<GameEngineSpriteRenderer>();							
	//Boss->SetTexture("blimp_idle_0001.png");									
	Boss->SetScaleToTexture("blimp_idle_0001.png");
																				
	GetTransform()->SetLocalPosition(float4(300.0f,0));							
																				

	//FSM

	//INTRO
	StartFuncPtr[static_cast<int>(HildaState::INTRO)] = std::bind(&Hilda::Intro_Start, this);
	UpdateFuncPtr[static_cast<int>(HildaState::INTRO)] = std::bind(&Hilda::Intro_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(HildaState::INTRO)] = std::bind(&Hilda::Intro_End, this);

	//SHOOT
	StartFuncPtr[static_cast<int>(HildaState::SHOOT)] = std::bind(&Hilda::Shoot_Start, this);
	UpdateFuncPtr[static_cast<int>(HildaState::SHOOT)] = std::bind(&Hilda::Shoot_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(HildaState::SHOOT)] = std::bind(&Hilda::Shoot_End, this);

	//CHANGEPHASE
	StartFuncPtr[static_cast<int>(HildaState::CHANGEPHASE)] = std::bind(&Hilda::ChangePhase_Start, this);
	UpdateFuncPtr[static_cast<int>(HildaState::CHANGEPHASE)] = std::bind(&Hilda::ChangePhase_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(HildaState::CHANGEPHASE)] = std::bind(&Hilda::ChangePhase_End, this);

	//TORNADO
	StartFuncPtr[static_cast<int>(HildaState::TORNADO)] = std::bind(&Hilda::Tornado_Start, this);
	UpdateFuncPtr[static_cast<int>(HildaState::TORNADO)] = std::bind(&Hilda::Tornado_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(HildaState::TORNADO)] = std::bind(&Hilda::Tornado_End, this);
	

}

void Hilda::Update(float _DeltaTime)
{

	Boss->GetTransform()->SetLocalPosition(float4(cosf(GetLiveTime() * 2.5f) * SpinSpeed, CircleMove * (1-sinf(GetLiveTime() * 2.5f)) * SpinSpeed)); // 힐다베르그  8자 움직임

	float degree = (GetLiveTime() * 2.5f) / GameEngineMath::PIE2 + GameEngineMath::PIE/4;

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
		LastShare = static_cast<int>(degree)+1;
	}

	UpdateState(_DeltaTime);


}

void Hilda::Render(float _DeltaTime)
{

}

void Hilda::UpdateState(float _DeltaTime)
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