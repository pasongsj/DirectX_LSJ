#include "PrecompileHeader.h"
#include "Hilda.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>


void Hilda::Intro_Start()
{
}
void Hilda::Intro_Update(float _DeltaTime)
{
	if (true == Boss->IsAnimationEnd())
	{
		NextState = HildaState::IDLE;
	}
}
void Hilda::Intro_End()
{
}


void Hilda::Idle_Start()
{
	Boss->ChangeAnimation("Idle");

}

void Hilda::Idle_Update(float _DeltaTime)
{
	IdleMoveTime += _DeltaTime;

	GetTransform()->SetLocalPosition(float4(cosf(IdleMoveTime * 2.5f) * SpinSpeed, CircleMove * (1 - sinf(IdleMoveTime * 2.5f)) * SpinSpeed) + float4(300.0f, 0)); // 힐다베르그  8자 움직임

	float degree = (IdleMoveTime * 2.5f) / GameEngineMath::PIE2 + GameEngineMath::PIE / 4;

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
		LastShare = static_cast<int>(degree) + 1;
	}
}

void Hilda::Idle_End()
{

}

void Hilda::Shoot_Start()
{
	Boss->ChangeAnimation("shoot");
}
void Hilda::Shoot_Update(float _DeltaTime)
{
	if (true == Boss->IsAnimationEnd())
	{
		NextState = HildaState::IDLE;
	}
}
void Hilda::Shoot_End()
{
}

void Hilda::ChangePhase_Start()
{

	DashTurn = true;
;
	WaitingTime = 3.0f;
	Boss->ChangeAnimation("Dash");
}
void Hilda::ChangePhase_Update(float _DeltaTime)
{
	if (true == DashTurn && true == Boss->IsAnimationEnd())
	{
		WaitingTime -= _DeltaTime;
	}
	if (WaitingTime < 0.0f)
	{
		DashTurn = false;

		Boss->ChangeAnimation("Summon");
	}
	if (false == DashTurn && true == Boss->IsAnimationEnd())
	{
		NextState = HildaState::IDLE;
	}


}
void Hilda::ChangePhase_End()
{
}

void Hilda::Tornado_Start()
{
}
void Hilda::Tornado_Update(float _DeltaTime)
{
}
void Hilda::Tornado_End()
{
}