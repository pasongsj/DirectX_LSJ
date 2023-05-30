#pragma once
#include <GameEngineCore/GameEngineActor.h>
// Ό³Έν :
class GameEnermyAttack : public GameEngineActor
{
public:
	// constrcuter destructer
	GameEnermyAttack();
	~GameEnermyAttack();

	// delete Function
	GameEnermyAttack(const GameEnermyAttack& _Other) = delete;
	GameEnermyAttack(GameEnermyAttack&& _Other) noexcept = delete;
	GameEnermyAttack& operator=(const GameEnermyAttack& _Other) = delete;
	GameEnermyAttack& operator=(GameEnermyAttack&& _Other) noexcept = delete;

	void CollisionPlayer(std::shared_ptr<class GameEngineCollision> _EnermyCol);
protected:

private:

};

