#include "PrecompileHeader.h"
#include "HildaBoss.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "HIldaBigCloudFX.h"
#include "HildaDashBackExplodeFX.h"

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

void HildaBoss::HildaDeath()
{

	std::shared_ptr<HIldaBigCloudFX> Explode0 = GetLevel()->CreateActor< HIldaBigCloudFX>(CupHeadActorOrder::EnemyEffect);
	Explode0->GetTransform()->SetLocalPosition(float4(300, 0, 450));
	std::shared_ptr<HildaDashBackExplodeFX> Explode1 = GetLevel()->CreateActor< HildaDashBackExplodeFX>(CupHeadActorOrder::EnemyEffect);
	Explode1->GetTransform()->SetLocalPosition(float4(120, 150, 450));
	std::shared_ptr<HildaDashBackExplodeFX> Explode2 = GetLevel()->CreateActor< HildaDashBackExplodeFX>(CupHeadActorOrder::EnemyEffect);
	Explode2->GetTransform()->SetLocalPosition(float4(90, 0, 450));
	std::shared_ptr<HildaDashBackExplodeFX> Explode3 = GetLevel()->CreateActor< HildaDashBackExplodeFX>(CupHeadActorOrder::EnemyEffect);
	Explode3->GetTransform()->SetLocalPosition(float4(150, -150, 450));
	std::shared_ptr<HildaDashBackExplodeFX> Explode4 = GetLevel()->CreateActor< HildaDashBackExplodeFX>(CupHeadActorOrder::EnemyEffect);
	Explode4->GetTransform()->SetLocalPosition(float4(500, -120, 450));

	Death();
}
