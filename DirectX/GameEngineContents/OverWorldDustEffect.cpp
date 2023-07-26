#include "PrecompileHeader.h"
#include "OverWorldDustEffect.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

OverWorldDustEffect::OverWorldDustEffect()
{
}

OverWorldDustEffect::~OverWorldDustEffect()
{
}

void OverWorldDustEffect::Start()
{
	SmokeREnder = CreateComponent< GameEngineSpriteRenderer>(CupHeadRendererOrder::PlayerEffect);
	SmokeREnder->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "OverWorldDust",.FrameInter = 0.01f, .Loop = false, .ScaleToTexture = true });
	SmokeREnder->ChangeAnimation("Idle");
}

void OverWorldDustEffect::Update(float _DeltaTime)
{
	if (true == SmokeREnder->IsAnimationEnd())
	{
		Death();
		return;
	}
}
