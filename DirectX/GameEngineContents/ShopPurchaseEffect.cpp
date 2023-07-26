#include "PrecompileHeader.h"
#include "ShopPurchaseEffect.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

ShopPurchaseEffect::ShopPurchaseEffect() 
{
}

ShopPurchaseEffect::~ShopPurchaseEffect() 
{
}

void ShopPurchaseEffect::Start()
{
	Coin = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::UI);
	Coin->CreateAnimation({ .AnimationName = "A", .SpriteName = "Purchase_CoinA",.FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	Coin->CreateAnimation({ .AnimationName = "B", .SpriteName = "Purchase_CoinB",.FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	Coin->ChangeAnimation("A");
}

void ShopPurchaseEffect::Update(float _DeltaTime)
{
	if (true == Coin->IsAnimationEnd())
	{
		Death();
		return;
	}
	GetTransform()->AddLocalPosition(Dir * MoveSpeed * _DeltaTime);
	Dir.y += Grav * _DeltaTime;
}

void ShopPurchaseEffect::SetBType()
{
	Coin->ChangeAnimation("B");
	Dir = float4(0.5f, 1.0f, 0);
}
