#pragma once
#include "GameEnemy.h"

// ���� :
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

	bool CollisionPlayer(std::shared_ptr<class GameEngineCollision> _EnermyCol);

	bool IsPink()
	{
		return Pink;
	}

protected:

	bool Pink = false; // �и����� ��ü
private:

};

