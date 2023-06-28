#pragma once
#include "GameEnemyWeapon.h"

// Ό³Έν :
class FlappyBird : public GameEnemyWeapon
{
public:
	// constrcuter destructer
	FlappyBird();
	~FlappyBird();

	// delete Function
	FlappyBird(const FlappyBird& _Other) = delete;
	FlappyBird(FlappyBird&& _Other) noexcept = delete;
	FlappyBird& operator=(const FlappyBird& _Other) = delete;
	FlappyBird& operator=(FlappyBird&& _Other) noexcept = delete;

	void SetPink();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> BirdRender = nullptr;

	void MakeSprite();

};

