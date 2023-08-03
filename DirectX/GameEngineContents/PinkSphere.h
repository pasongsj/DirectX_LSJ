#pragma once
#include "GameEnemy.h"

// Ό³Έν :
class PinkSphere : public GameEnemy
{
public:
	// constrcuter destructer
	PinkSphere();
	~PinkSphere();

	// delete Function
	PinkSphere(const PinkSphere& _Other) = delete;
	PinkSphere(PinkSphere&& _Other) noexcept = delete;
	PinkSphere& operator=(const PinkSphere& _Other) = delete;
	PinkSphere& operator=(PinkSphere&& _Other) noexcept = delete;

protected:
	void Start() override;
	//void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> PinkRender = nullptr;
	std::shared_ptr<class GameEngineCollision> PinkCollision = nullptr;

};

