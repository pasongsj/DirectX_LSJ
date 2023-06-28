#pragma once
#include "GameEnemyWeapon.h"

// Ό³Έν :
class Wally1_Egg_Spin : public GameEnemyWeapon
{
public:
	// constrcuter destructer
	Wally1_Egg_Spin();
	~Wally1_Egg_Spin();

	// delete Function
	Wally1_Egg_Spin(const Wally1_Egg_Spin& _Other) = delete;
	Wally1_Egg_Spin(Wally1_Egg_Spin&& _Other) noexcept = delete;
	Wally1_Egg_Spin& operator=(const Wally1_Egg_Spin& _Other) = delete;
	Wally1_Egg_Spin& operator=(Wally1_Egg_Spin&& _Other) noexcept = delete;

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

