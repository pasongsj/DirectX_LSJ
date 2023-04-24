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
	NextState = PlayerAirPlaneModeState::IDLE;
}
void PlayerAirPlaneMode::Intro_End()
{
}


void PlayerAirPlaneMode::Idle_Start()
{
	PlayerRender->SetTexture("cuphead_plane_idle_straight_0001.png");
}
void PlayerAirPlaneMode::Idle_Update(float _DeltaTime)
{
	int a = 0;
}
void PlayerAirPlaneMode::Idle_End()
{
}


void PlayerAirPlaneMode::MoveUp_Start()
{
	PlayerRender->SetTexture("cuphead_plane_idle_up_0001.png");
}
void PlayerAirPlaneMode::MoveUp_Update(float _DeltaTime)
{
}
void PlayerAirPlaneMode::MoveUp_End()
{
}


void PlayerAirPlaneMode::MoveDown_Start()
{
	PlayerRender->SetTexture("cuphead_plane_idle_down_0001.png");
}
void PlayerAirPlaneMode::MoveDown_Update(float _DeltaTime)
{
}
void PlayerAirPlaneMode::MoveDown_End()
{
}


void PlayerAirPlaneMode::Parry_Start()
{
}
void PlayerAirPlaneMode::Parry_Update(float _DeltaTime)
{
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