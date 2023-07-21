#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

enum class ItemState
{
	GLOW,
	DIM,
	SOLD,
};
// Ό³Έν :
class ShopItem : public GameEngineActor
{
	friend class ShopLevel;
public:
	// constrcuter destructer
	ShopItem();
	~ShopItem();

	// delete Function
	ShopItem(const ShopItem& _Other) = delete;
	ShopItem(ShopItem&& _Other) noexcept = delete;
	ShopItem& operator=(const ShopItem& _Other) = delete;
	ShopItem& operator=(ShopItem&& _Other) noexcept = delete;
	std::shared_ptr< GameEngineSpriteRenderer> GetItemRender()
	{
		return ItemRender;
	}

	void SetState(ItemState _State);

protected:
	void Start() override;
	

private:
	std::shared_ptr<class GameEngineSpriteRenderer> ItemRender = nullptr;


};

