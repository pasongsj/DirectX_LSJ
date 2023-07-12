#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 :
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

	// 플레이어를 공격
	bool CollisionPlayer(std::shared_ptr<class GameEngineCollision> _EnermyCol);

	bool IsPink()
	{
		return PinkObject;
	}

	// 플레이어로부터 공격을 받음
	virtual void Attack(int _Dmg)
	{
		HP -= _Dmg;
	}

	inline int GetHP()
	{
		return HP;
	}

protected:
	inline void SetHP(int _HP)
	{
		HP = _HP;
	}
	inline void SetPinkObject()
	{
		PinkObject = true;
	}

private:
	int HP = 1;
	bool PinkObject = false; // 패리가능 개체


};

