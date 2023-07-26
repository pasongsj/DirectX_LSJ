#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class PurchaseSmokeEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	PurchaseSmokeEffect();
	~PurchaseSmokeEffect();

	// delete Function
	PurchaseSmokeEffect(const PurchaseSmokeEffect& _Other) = delete;
	PurchaseSmokeEffect(PurchaseSmokeEffect&& _Other) noexcept = delete;
	PurchaseSmokeEffect& operator=(const PurchaseSmokeEffect& _Other) = delete;
	PurchaseSmokeEffect& operator=(PurchaseSmokeEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> Smoke = nullptr;

};

