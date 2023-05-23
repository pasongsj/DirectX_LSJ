#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEnermy : public GameEngineActor
{
public:
	// constrcuter destructer
	GameEnermy();
	~GameEnermy();

	// delete Function
	GameEnermy(const GameEnermy& _Other) = delete;
	GameEnermy(GameEnermy&& _Other) noexcept = delete;
	GameEnermy& operator=(const GameEnermy& _Other) = delete;
	GameEnermy& operator=(GameEnermy&& _Other) noexcept = delete;

	inline void Attack(int _Dmg)
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

