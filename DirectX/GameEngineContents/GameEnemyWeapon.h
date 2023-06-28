#pragma once
#include "GameEnemy.h"

// 설명 :
class GameEnemyWeapon : public GameEnemy
{
public:
	// constrcuter destructer
	GameEnemyWeapon();
	~GameEnemyWeapon();

	// delete Function
	GameEnemyWeapon(const GameEnemyWeapon& _Other) = delete;
	GameEnemyWeapon(GameEnemyWeapon&& _Other) noexcept = delete;
	GameEnemyWeapon& operator=(const GameEnemyWeapon& _Other) = delete;
	GameEnemyWeapon& operator=(GameEnemyWeapon&& _Other) noexcept = delete;

	// 플레이어를 공격
	bool CollisionPlayer(std::shared_ptr<class GameEngineCollision> _EnermyCol);

	bool IsPink()
	{
		return PinkObject;
	}

protected:

	bool PinkObject = false; // 패리가능 개체
private:

};

