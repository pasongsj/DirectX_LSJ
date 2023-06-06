#pragma once
#include "GameEnemyAttack.h"

// Ό³Έν :
class SagittariusArrow : public GameEnemyAttack
{
public:
	// constrcuter destructer
	SagittariusArrow();
	~SagittariusArrow();

	// delete Function
	SagittariusArrow(const SagittariusArrow& _Other) = delete;
	SagittariusArrow(SagittariusArrow&& _Other) noexcept = delete;
	SagittariusArrow& operator=(const SagittariusArrow& _Other) = delete;
	SagittariusArrow& operator=(SagittariusArrow&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
		 
private:
	std::shared_ptr<class GameEngineSpriteRenderer> ArrowRender = nullptr;
	std::shared_ptr<class GameEngineCollision> ArrowCollision = nullptr;

	float ArrowSpeed = 800;
	void MakeSprite();

};

