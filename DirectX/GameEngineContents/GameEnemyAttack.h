#pragma once
#include <GameEngineCore/GameEngineActor.h>
// 설명 :
class GameEnemyAttack : public GameEngineActor
{
public:
	// constrcuter destructer
	GameEnemyAttack();
	~GameEnemyAttack();

	// delete Function
	GameEnemyAttack(const GameEnemyAttack& _Other) = delete;
	GameEnemyAttack(GameEnemyAttack&& _Other) noexcept = delete;
	GameEnemyAttack& operator=(const GameEnemyAttack& _Other) = delete;
	GameEnemyAttack& operator=(GameEnemyAttack&& _Other) noexcept = delete;

	bool CollisionPlayer(std::shared_ptr<class GameEngineCollision> _EnermyCol);

	bool IsPink()
	{
		return Pink;
	}

protected:

	bool Pink = false; // 패리가능 개체
private:

};

