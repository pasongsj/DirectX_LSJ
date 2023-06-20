#include "PrecompileHeader.h"
#include "PlayerOverWorldMode.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>


void PlayerOverWorldMode::Idle_Start()
{
}

void PlayerOverWorldMode::Idle_Update(float _DeltaTime)
{
	CheckInput();
	MoveUpdate(_DeltaTime);
}

void PlayerOverWorldMode::Idle_End()
{
}

void PlayerOverWorldMode::MoveUp_Start()
{
}

void PlayerOverWorldMode::MoveUp_Update(float _DeltaTime)
{
	CheckInput();
	MoveUpdate(_DeltaTime);
}

void PlayerOverWorldMode::MoveUp_End()
{
}

void PlayerOverWorldMode::Win_Start()
{
	PlayerRender->ChangeAnimation("InterAction_Win");
}

void PlayerOverWorldMode::Win_Update(float _DeltaTime)
{
	if (true == PlayerRender->IsAnimationEnd())
	{
		NextState = PlayerOverWorldModeState::IDLE;
	}
}

void PlayerOverWorldMode::Win_End()
{
}
