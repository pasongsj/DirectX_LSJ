#pragma once
#include "GameEnemyWeapon.h"

// Ό³Έν :
class Wally3_Heart : public GameEnemyWeapon
{
public:
	// constrcuter destructer
	Wally3_Heart();
	~Wally3_Heart();

	// delete Function
	Wally3_Heart(const Wally3_Heart& _Other) = delete;
	Wally3_Heart(Wally3_Heart&& _Other) noexcept = delete;
	Wally3_Heart& operator=(const Wally3_Heart& _Other) = delete;
	Wally3_Heart& operator=(Wally3_Heart&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> HeartRender = nullptr;
	void MakeSprite();

};

