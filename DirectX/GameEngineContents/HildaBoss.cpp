#include "PrecompileHeader.h"
#include "HildaBoss.h"

#include <GameEngineBase/GameEngineRandom.h>


HildaBoss::HildaBoss() 
{
}

HildaBoss::~HildaBoss() 
{
}


float4 HildaBoss::GetHildaMove(float _Delta)
{
	IdleMoveTime += _Delta;
	float4 ReturnValue = float4(cosf(IdleMoveTime * 2.5f) * SpinSpeed, CircleMove * (1 - sinf(IdleMoveTime * 2.5f)) * SpinSpeed);

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
	return ReturnValue;


}