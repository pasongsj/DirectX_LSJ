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
	ExplainRender = CreateComponent< GameEngineSpriteRenderer>(CupHeadRendererOrder::PlayerBackGround);
}

void ShopItem::SetState(ItemState _State)
{
	if (ItemState::SOLD == CurState)
	{
		return;
	}
	switch (_State)
	{
	case ItemState::GLOW:
		if (nullptr != ExplainRender)
		{
			ExplainRender->On();
		}
		break;
	case ItemState::DIM:
		ExplainRender->Off();
		break;
	case ItemState::SOLD:
		ExplainRender->Off();
		break;
	default:
		break;
	}
	CurState = _State;
	ItemRender->ChangeAnimation(std::to_string(static_cast<int>(_State)));
}
