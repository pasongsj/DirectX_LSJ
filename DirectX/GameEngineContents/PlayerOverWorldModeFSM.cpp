#include "PrecompileHeader.h"
#include "PlayerOverWorldMode.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "OverWorldDustEffect.h"


void PlayerOverWorldMode::Idle_Start()
{
}

void PlayerOverWorldMode::Idle_Update(float _DeltaTime)
{
	CheckInput();
	//MoveUpdate(_DeltaTime);
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
	FootSoundInterval -= _DeltaTime;
	DustInterval -= _DeltaTime;
	if (FootSoundInterval < 0) 
	{
		FootSoundInterval = 0.3f;
		if (MoveVec.Size() > 0)
		{
			GameEngineSound::Play("WorldMap_Footstep_001.wav");
		}
	}
	if (DustInterval < 0)
	{
		DustInterval = 0.2f;
		if (MoveVec.Size() > 0)
		{
			std::shared_ptr<GameEngineActor> dust = GetLevel()->CreateActor< OverWorldDustEffect>();
			dust->GetTransform()->SetLocalPosition(GetTransform()->GetWorldPosition() + float4(0,-30,-10));
		}
	}

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
