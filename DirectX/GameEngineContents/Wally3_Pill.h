#pragma once
#include "GameEnemy.h"

// Ό³Έν :
class Wally3_Pill : public GameEnemy
{
public:
	// constrcuter destructer
	Wally3_Pill();
	~Wally3_Pill();

	// delete Function
	Wally3_Pill(const Wally3_Pill& _Other) = delete;
	Wally3_Pill(Wally3_Pill&& _Other) noexcept = delete;
	Wally3_Pill& operator=(const Wally3_Pill& _Other) = delete;
	Wally3_Pill& operator=(Wally3_Pill&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> PillRender = nullptr;
	std::shared_ptr<class GameEngineCollision> PillCollision = nullptr;
	float MoveSpeed = 500;

	void MakeSprite();
};

