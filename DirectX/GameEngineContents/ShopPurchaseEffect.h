#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class ShopPurchaseEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	ShopPurchaseEffect();
	~ShopPurchaseEffect();

	// delete Function
	ShopPurchaseEffect(const ShopPurchaseEffect& _Other) = delete;
	ShopPurchaseEffect(ShopPurchaseEffect&& _Other) noexcept = delete;
	ShopPurchaseEffect& operator=(const ShopPurchaseEffect& _Other) = delete;
	ShopPurchaseEffect& operator=(ShopPurchaseEffect&& _Other) noexcept = delete;

	void SetBType();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> Coin = nullptr;
	float4 Dir = float4(-2.0f, 1.0f, 0);
	float MoveSpeed = 100.0f;
	float Grav = -5.0f;
};

