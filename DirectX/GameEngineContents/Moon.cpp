#include "PrecompileHeader.h"
#include "Moon.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

Moon::Moon() 
{
}

Moon::~Moon() 
{
}


void Moon::Start()
{
	Boss = CreateComponent<GameEngineSpriteRenderer>();
	Boss->CreateAnimation({ .AnimationName = "Idle",  .TextureName = "blimp_moon_idle_00", .Start = 1, .End = 16,.InterTime = 0.05f, .Loop = true });
	Boss->ChangeAnimation("Idle");
	//Boss->SetScaleToTexture("blimp_moon_idle_0001.png");
	GetTransform()->SetLocalPosition(float4(300, -20));



	//FSM																				

	//IDLE
	StartFuncPtr[static_cast<int>(MoonState::IDLE)] = std::bind(&Moon::Idle_Start, this);
	UpdateFuncPtr[static_cast<int>(MoonState::IDLE)] = std::bind(&Moon::Idle_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(MoonState::IDLE)] = std::bind(&Moon::Idle_End, this);

	//ATTACK
	StartFuncPtr[static_cast<int>(MoonState::ATTACK)] = std::bind(&Moon::Attack_Start, this);
	UpdateFuncPtr[static_cast<int>(MoonState::ATTACK)] = std::bind(&Moon::Attack_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(MoonState::ATTACK)] = std::bind(&Moon::Attack_End, this);

	//SHOOT
	StartFuncPtr[static_cast<int>(MoonState::DEATH)] = std::bind(&Moon::Death_Start, this);
	UpdateFuncPtr[static_cast<int>(MoonState::DEATH)] = std::bind(&Moon::Death_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(MoonState::DEATH)] = std::bind(&Moon::Death_End, this);

}

void Moon::Update(float _DeltaTime)
{

}


void Moon::UpdateState(float _DeltaTime)
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



// FSM

void Moon::Idle_Start()
{

}
void Moon::Idle_Update(float _DeltaTime)
{

}
void Moon::Idle_End()
{

}
void Moon::Attack_Start()
{

}
void Moon::Attack_Update(float _DeltaTime)
{
}
void Moon::Attack_End()
{
}
void Moon::Death_Start()
{
}
void Moon::Death_Update(float _DeltaTime)
{
}
void Moon::Death_End()
{
}