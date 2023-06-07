#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEnemy : public GameEngineActor
{
public:
	// constrcuter destructer
	GameEnemy();
	~GameEnemy();

	// delete Function
	GameEnemy(const GameEnemy& _Other) = delete;
	GameEnemy(GameEnemy&& _Other) noexcept = delete;
	GameEnemy& operator=(const GameEnemy& _Other) = delete;
	GameEnemy& operator=(GameEnemy&& _Other) noexcept = delete;

	virtual void Attack(int _Dmg)
	{
		HP -= _Dmg;
	}

	inline int GetHP()
	{
		return HP;
	}

protected:
	int HP = 1;

	inline void SetHP(int _HP)
	{
		HP = _HP;
	}

private:


};

