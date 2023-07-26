#include "PrecompileHeader.h"
#include "PurchaseSmokeEffect.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

PurchaseSmokeEffect::PurchaseSmokeEffect()
{
}

PurchaseSmokeEffect::~PurchaseSmokeEffect()
{
}


void PurchaseSmokeEffect::Start()
{
	Smoke = CreateComponent< GameEngineSpriteRenderer>(CupHeadRendererOrder::UI);
	Smoke->CreateAnimation({ .AnimationName = "Idle",.SpriteName = "Purchase_Effect",.FrameInter = 0.05f,.Loop = false ,.ScaleToTexture = true });
	Smoke->ChangeAnimation("Idle");
	Smoke->SetScaleRatio(2.0f);
}
void PurchaseSmokeEffect::Update(float _DeltaTime)
{
	if (true == Smoke->IsAnimationEnd())
	{
		Death();
		return;
	}
}
