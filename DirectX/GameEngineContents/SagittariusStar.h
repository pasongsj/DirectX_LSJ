#pragma once
#include "GameEnermyAttack.h"
#include <queue>

// Ό³Έν :
class SagittariusStar : public GameEnermyAttack
{
public:
	// constrcuter destructer
	SagittariusStar();
	~SagittariusStar();

	// delete Function
	SagittariusStar(const SagittariusStar& _Other) = delete;
	SagittariusStar(SagittariusStar&& _Other) noexcept = delete;
	SagittariusStar& operator=(const SagittariusStar& _Other) = delete;
	SagittariusStar& operator=(SagittariusStar&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> StarRender = nullptr;
	std::shared_ptr<class GameEngineCollision> StarCollision = nullptr;

	std::queue<std::shared_ptr<class GameEngineSpriteRenderer>> Trail;
	float TrailInterval = 0.3f;

	float StarSpeed = 400;
	float4 Dir = float4::Left;
	bool isStarDeath = false;

	void MakeSprite();
	void CheckDir();

};

