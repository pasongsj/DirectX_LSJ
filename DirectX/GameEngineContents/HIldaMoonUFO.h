#pragma once
#include "GameEnemyAttack.h"

// Ό³Έν :
class HIldaMoonUFO : public GameEnemyAttack
{
public:
	// constrcuter destructer
	HIldaMoonUFO();
	~HIldaMoonUFO();

	// delete Function
	HIldaMoonUFO(const HIldaMoonUFO& _Other) = delete;
	HIldaMoonUFO(HIldaMoonUFO&& _Other) noexcept = delete;
	HIldaMoonUFO& operator=(const HIldaMoonUFO& _Other) = delete;
	HIldaMoonUFO& operator=(HIldaMoonUFO&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> UFORender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> UFOBeamRender = nullptr;
	std::shared_ptr<class GameEngineCollision> UFOBeamCollision = nullptr;

	float UFOSpeed = 300.0f;
	float4 Point[4] = {};
	int index = 0;

	void MakeSprite();

	void UFOMove(float _DeltaTime);
};

