#pragma once
#include <GameEngineCore/GameEngineActor.h>
// 설명 :
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

	bool CollisionPlayer(std::shared_ptr<class GameEngineCollision> _EnermyCol);

	bool IsPink()
	{
		return Pink;
	}

protected:

	bool Pink = false; // 패리가능 개체
private:

};

