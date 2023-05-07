#include "PrecompileHeader.h"
#include "PlayerAirPlaneMode.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

void PlayerAirPlaneMode::Intro_Start()
{
	ChangePlayerAnimation("Intro");
}
void PlayerAirPlaneMode::Intro_Update(float _DeltaTime)
{

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
	ChangePlayerAnimation("Idle");

	Spark->GetTransform()->SetLocalPosition(float4(80, -5));
	//PlayerRender->ChangeAnimation("Idle");
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
	isStartAnimationDone = false;
	ChangePlayerAnimation("MoveUpTrans");

	Spark->GetTransform()->SetLocalPosition(float4(80, 0));
	//PlayerRender->ChangeAnimation("MoveUpTrans");
}
void PlayerAirPlaneMode::MoveUp_Update(float _DeltaTime)
{
	if (false == isStartAnimationDone && true == PlayerRender->IsAnimationEnd())
	{
		isStartAnimationDone = true;
		ChangePlayerAnimation("MoveUp");
		//PlayerRender->ChangeAnimation("MoveUp");
	}
	CheckInput();
}
void PlayerAirPlaneMode::MoveUp_End()
{
}


void PlayerAirPlaneMode::MoveDown_Start()
{
	isStartAnimationDone = false;
	ChangePlayerAnimation("MoveDownTrans");

	Spark->GetTransform()->SetLocalPosition(float4(80, 5));
	//PlayerRender->ChangeAnimation("MoveDownTrans");
}
void PlayerAirPlaneMode::MoveDown_Update(float _DeltaTime)
{
	if (false == isStartAnimationDone && true == PlayerRender->IsAnimationEnd())
	{
		isStartAnimationDone = true;
		ChangePlayerAnimation("MoveDown");
		//PlayerRender->ChangeAnimation("MoveDown");
	}
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

