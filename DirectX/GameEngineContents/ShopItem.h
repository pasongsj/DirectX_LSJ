#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class ItemState
{
	DIM,
	GLOW
};
// ���� :
class ShopItem
{
public:
	// constrcuter destructer
	ShopItem();
	~ShopItem();

	// delete Function
	ShopItem(const ShopItem& _Other) = delete;
	ShopItem(ShopItem&& _Other) noexcept = delete;
	ShopItem& operator=(const ShopItem& _Other) = delete;
	ShopItem& operator=(ShopItem&& _Other) noexcept = delete;

protected:

private:

};

