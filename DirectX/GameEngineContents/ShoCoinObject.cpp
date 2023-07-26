#include "PrecompileHeader.h"
#include "ShoCoinObject.h"
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "ShopLevel.h"

ShoCoinObject::ShoCoinObject()
{
}

ShoCoinObject::~ShoCoinObject()
{
}


void ShoCoinObject::Start()
{
	CoinUI = CreateComponent<GameEngineUIRenderer>(CupHeadRendererOrder::UI);
	CoinUI->CreateAnimation({ .AnimationName = "Idle",.SpriteName = "Shop_Coin",.FrameInter = 0.05f,.Loop = true ,.ScaleToTexture = true });
	CoinUI->ChangeAnimation("Idle");
	CoinUI->GetTransform()->SetLocalPosition(float4(-30, 0, 0));
	GoldNum = CreateComponent<GameEngineUIRenderer>(CupHeadRendererOrder::UI);
	CurCoin = ShopLevel::CoinCount;
	std::string TextureName = "ch_world_map_gold_number_" + std::to_string(CurCoin) + ".png";
	GoldNum->SetScaleToTexture(TextureName);
	GoldNum->GetTransform()->SetLocalPosition(float4(20, 10, 0));

}


void ShoCoinObject::Update(float _DeltaTime)
{
	if (ShopLevel::CoinCount == CurCoin)
	{
		return;
	}
	CurCoin = ShopLevel::CoinCount;
	std::string TextureName = "ch_world_map_gold_number_" + std::to_string(CurCoin) + ".png";
	GoldNum->SetScaleToTexture(TextureName);
}

