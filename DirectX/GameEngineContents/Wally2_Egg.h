#pragma once
#include "GameEnemy.h"

// Ό³Έν :
class Wally2_Egg : public GameEnemy
{
	friend class Wally2;
public:
	// constrcuter destructer
	Wally2_Egg();
	~Wally2_Egg();

	// delete Function
	Wally2_Egg(const Wally2_Egg& _Other) = delete;
	Wally2_Egg(Wally2_Egg&& _Other) noexcept = delete;
	Wally2_Egg& operator=(const Wally2_Egg& _Other) = delete;
	Wally2_Egg& operator=(Wally2_Egg&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> EggRender = nullptr;
	std::shared_ptr<class GameEngineCollision> EggCollision = nullptr;
	bool isDeathAnimation = false;
	void MakeSprite();
	void MakeDeath();

};

