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
	std::shared_ptr< GameEngineSpriteRenderer> GetExplainRender()
	{
		return ExplainRender;
	}

	void SetState(ItemState _State);
	ItemState GetState()
	{
		return CurState;
	}

	void SetPurchaseFunc(std::function<void()> _Func)
	{
		Purchase = _Func;
	}

	void DoPurchase()
	{
		if (ItemState::SOLD != CurState && nullptr != Purchase)
		{
			Purchase();
		}
	}

	inline void SetPrice(int _Pr)
	{
		Price = _Pr;
	}

	int GetPrice()
	{
		return Price;
	}

protected:
	void Start() override;
	

private:
	std::shared_ptr<class GameEngineSpriteRenderer> ItemRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> ExplainRender = nullptr;
	ItemState CurState = ItemState::DIM;
	std::function<void()> Purchase = nullptr;
	int Price;


};

