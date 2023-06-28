#pragma once
#include "GameEnemyWeapon.h"

// Ό³Έν :
class WallyEggSpin : public GameEnemyWeapon
{
public:
	// constrcuter destructer
	WallyEggSpin();
	~WallyEggSpin();

	// delete Function
	WallyEggSpin(const WallyEggSpin& _Other) = delete;
	WallyEggSpin(WallyEggSpin&& _Other) noexcept = delete;
	WallyEggSpin& operator=(const WallyEggSpin& _Other) = delete;
	WallyEggSpin& operator=(WallyEggSpin&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:
	std::shared_ptr<class GameEngineSpriteRenderer> EggRender = nullptr;
	float MoveSpeed = 800;
	float4 ScreenSize = float4::Zero;
	bool isDeadAnimation = false;

	void MakeSprite();
};

