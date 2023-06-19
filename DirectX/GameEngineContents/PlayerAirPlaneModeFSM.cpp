#include "PrecompileHeader.h"
#include "PlayerAirPlaneMode.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>


void PlayerAirPlaneMode::Intro_Start()
{
	ChangePlayerAnimation("Intro");
	if ("Super" == CurMode)
	{
		TimeStop();
		ShadowEffect->On();
	}
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
 	TimePlay();
	ShadowEffect->Off();
}


void PlayerAirPlaneMode::Idle_Start()
{
	ChangePlayerAnimation("Idle");

	Spark->GetTransform()->SetLocalPosition(float4(80, -5, -50));
}
void PlayerAirPlaneMode::Idle_Update(float _DeltaTime)
{
	CheckInput();
	CheckShoot(_DeltaTime);
	MakeSmoke(_DeltaTime);
}
void PlayerAirPlaneMode::Idle_End()
{
}


void PlayerAirPlaneMode::MoveUp_Start()
{
	isStartAnimationDone = false;
	ChangePlayerAnimation("MoveUpTrans");

	Spark->GetTransform()->SetLocalPosition(float4(80, 0, -50));
}
void PlayerAirPlaneMode::MoveUp_Update(float _DeltaTime)
{
	if (false == isStartAnimationDone && true == PlayerRender->IsAnimationEnd())
	{
		isStartAnimationDone = true;
		ChangePlayerAnimation("MoveUp");
	}
	CheckInput();
	CheckShoot(_DeltaTime);
	MakeSmoke(_DeltaTime);
}
void PlayerAirPlaneMode::MoveUp_End()
{
}


void PlayerAirPlaneMode::MoveDown_Start()
{
	isStartAnimationDone = false;
	ChangePlayerAnimation("MoveDownTrans");

	Spark->GetTransform()->SetLocalPosition(float4(80, 5, -50));
}
void PlayerAirPlaneMode::MoveDown_Update(float _DeltaTime)
{
	if (false == isStartAnimationDone && true == PlayerRender->IsAnimationEnd())
	{
		isStartAnimationDone = true;
		ChangePlayerAnimation("MoveDown");
	}
	CheckInput();
	CheckShoot(_DeltaTime);
	MakeSmoke(_DeltaTime);
}
void PlayerAirPlaneMode::MoveDown_End()
{
}


void PlayerAirPlaneMode::Parry_Start()
{
	PlayerRender->ChangeAnimation("Parry");
	PlayerCollision->Off();
	ParryCollision->On();
}
void PlayerAirPlaneMode::Parry_Update(float _DeltaTime)
{
	if (true == PlayerRender->IsAnimationEnd())
	{
		NextState = PlayerAirPlaneModeState::IDLE;
	}
	CheckPink();
}
void PlayerAirPlaneMode::Parry_End()
{
	ParryCollision->Off();
	PlayerCollision->On();
}

