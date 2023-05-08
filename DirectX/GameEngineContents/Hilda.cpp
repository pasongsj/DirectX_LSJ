#include "PrecompileHeader.h"
#include "Hilda.h"
#include <GameEnginePlatform/GameEngineInput.h>

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
	Boss->CreateAnimation({ .AnimationName = "Intro",  .TextureName = "blimp_intro_00", .Start = 1, .End = 43,.InterTime = 0.05f, .Loop = false });
	Boss->CreateAnimation({ .AnimationName = "Idle",  .TextureName = "blimp_idle_00", .Start = 1, .End = 21,.InterTime = 0.05f, .Loop = true });
	Boss->CreateAnimation({ .AnimationName = "shoot",  .TextureName = "blimp_shoot_00", .Start = 1, .End = 19,.InterTime = 0.05f, .Loop = false });
	Boss->CreateAnimation({ .AnimationName = "Dash",  .TextureName = "blimp_dash_00", .Start = 1, .End = 18,.InterTime = 0.05f, .Loop = false });
	Boss->CreateAnimation({ .AnimationName = "DashBack",  .TextureName = "blimp_dash_00", .Start = 19, .End = 24,.InterTime = 0.05f, .Loop = false });
	Boss->CreateAnimation({ .AnimationName = "Summon",  .TextureName = "blimp_summon_00", .Start = 1, .End = 21,.InterTime = 0.05f, .Loop = false });
	Boss->CreateAnimation({ .AnimationName = "Tornato",  .TextureName = "blimp_tornado_00", .Start = 1, .End = 38,.InterTime = 0.05f, .Loop = false });
	Boss->ChangeAnimation("Intro");
	//Boss->SetTexture("blimp_idle_0001.png");									
	//Boss->SetScaleToTexture("blimp_idle_0001.png");
																				
	GetTransform()->SetLocalPosition(float4(300.0f,0));							
																				

	//FSM

	//INTRO
	StartFuncPtr[static_cast<int>(HildaState::INTRO)] = std::bind(&Hilda::Intro_Start, this);
	UpdateFuncPtr[static_cast<int>(HildaState::INTRO)] = std::bind(&Hilda::Intro_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(HildaState::INTRO)] = std::bind(&Hilda::Intro_End, this);

	//IDLE
	StartFuncPtr[static_cast<int>(HildaState::IDLE)] = std::bind(&Hilda::Idle_Start, this);
	UpdateFuncPtr[static_cast<int>(HildaState::IDLE)] = std::bind(&Hilda::Idle_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(HildaState::IDLE)] = std::bind(&Hilda::Idle_End, this);

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
	


	// TestCode
	if (false == GameEngineInput::IsKey("Test"))
	{
		GameEngineInput::CreateKey("Test", VK_SPACE);
	}

}

void Hilda::Update(float _DeltaTime)
{


	UpdateState(_DeltaTime);
	if (true == GameEngineInput::IsPress("Test"))
	{
		NextState = HildaState::TORNADO;
	}


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