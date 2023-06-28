#include "PrecompileHeader.h"
#include "Wally2.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>



void Wally2::Intro_Start()
{
	BossRender->ChangeAnimation("Idle");
	ResetLiveTime();
}

void Wally2::Intro_Update(float _DeltaTime)
{
	if (GetLiveTime() > 2.0f)
	{
		NextState = Wally2State::IDLE;
	}
}

void Wally2::Intro_End()
{
}



void Wally2::Idle_Start()
{
	BossRender->ChangeAnimation("Idle",false);

}

void Wally2::Idle_Update(float _DeltaTime)
{
	MoveUpdate(_DeltaTime);
	if (true == isTransAnimatioin && true == BossRender->IsAnimationEnd())
	{
		BossRender->ChangeAnimation("Idle",false);

		isTransAnimatioin = false;
	}
}

void Wally2::Idle_End()
{
}


void Wally2::Shoot_Start()
{
	GetTransform()->SetLocalScale(float4::One);
	BossRender->ChangeAnimation("Shoot");
}

void Wally2::Shoot_Update(float _DeltaTime)
{
	if (true == BossRender->IsAnimationEnd())
	{
		NextState = Wally2State::IDLE;
	}
}

void Wally2::Shoot_End()
{
}


void Wally2::Death_Start()
{
	BossRender->ChangeAnimation("Death_Trans");
	isDeathLoop = false;
	DeathLoopCount = 0;
}

void Wally2::Death_Update(float _DeltaTime)
{
	if (false == isDeathLoop && true == BossRender->IsAnimationEnd())
	{
		isDeathLoop = true;
		BossRender->ChangeAnimation("Death_Loop");
	}
	else if (true == isDeathLoop && DeathLoopCount > 5)
	{
		NextState = Wally2State::IDLE;
	}
}

void Wally2::Death_End()
{
}
