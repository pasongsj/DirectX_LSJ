#include "PrecompileHeader.h"
#include "ShopItem.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

ShopItem::ShopItem()
{
}

ShopItem::~ShopItem()
{
}

void ShopItem::Start()
{
	ItemRender = CreateComponent< GameEngineSpriteRenderer>(CupHeadRendererOrder::PlayerBackGround);
}

void ShopItem::SetState(ItemState _State)
{
	ItemRender->ChangeAnimation(std::to_string(static_cast<int>(_State)));
}
