#include "PrecompileHeader.h"
#include "PlayerAirPlaneMode.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

void PlayerAirPlaneMode::Intro_Start()
{
	int a = 0;
}
void PlayerAirPlaneMode::Intro_Update(float _DeltaTime)
{
	int a = 0;
	if (true == PlayerRender->IsAnimationEnd())
	{
		NextState = PlayerAirPlaneModeState::IDLE;

	}
}
void PlayerAirPlaneMode::Intro_End()
{
}


void PlayerAirPlaneMode::Idle_Start()
{
	PlayerRender->ChangeAnimation("Idle");
	//PlayerRender->SetTexture("cuphead_plane_idle_straight_0001.png");
}
void PlayerAirPlaneMode::Idle_Update(float _DeltaTime)
{
	CheckInput();
}
void PlayerAirPlaneMode::Idle_End()
{
}


void PlayerAirPlaneMode::MoveUp_Start()
{
	PlayerRender->ChangeAnimation("MoveUp");
	//PlayerRender->SetTexture("cuphead_plane_idle_up_0001.png");
}
void PlayerAirPlaneMode::MoveUp_Update(float _DeltaTime)
{
	CheckInput();
}
void PlayerAirPlaneMode::MoveUp_End()
{
}


void PlayerAirPlaneMode::MoveDown_Start()
{
	PlayerRender->ChangeAnimation("MoveDown");
	/*PlayerRender->SetTexture("cuphead_plane_idle_down_0001.png");*/
}
void PlayerAirPlaneMode::MoveDown_Update(float _DeltaTime)
{
	CheckInput();
}
void PlayerAirPlaneMode::MoveDown_End()
{
}


void PlayerAirPlaneMode::Parry_Start()
{
	PlayerRender->ChangeAnimation("Parry");
}
void PlayerAirPlaneMode::Parry_Update(float _DeltaTime)
{
	if (true == PlayerRender->IsAnimationEnd())
	{
		NextState = PlayerAirPlaneModeState::IDLE;
	}
}
void PlayerAirPlaneMode::Parry_End()
{
}


void PlayerAirPlaneMode::SuperSkill_Start()
{
}
void PlayerAirPlaneMode::SuperSkill_Update(float _DeltaTime)
{
}
void PlayerAirPlaneMode::SuperSkill_End()
{
}