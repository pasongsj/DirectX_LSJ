#include "PrecompileHeader.h"
#include "Hilda.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>


void Hilda::Intro_Start()
{
}
void Hilda::Intro_Update(float _DeltaTime)
{
}
void Hilda::Intro_End()
{
}


void Hilda::Idle_Start()
{

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
}
void Hilda::Shoot_Update(float _DeltaTime)
{
}
void Hilda::Shoot_End()
{
}

void Hilda::ChangePhase_Start()
{
}
void Hilda::ChangePhase_Update(float _DeltaTime)
{
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