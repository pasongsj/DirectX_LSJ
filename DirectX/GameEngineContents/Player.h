#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Player : public GameEngineActor
{
	friend class GameEnermy;
public:

	static Player* MainPlayer;

	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	inline int GetHP()
	{
		return PlayerHP;
	}

	inline float GetSuperModeEnergy()
	{
		return SuperModeEnergy;
	}
	inline void Attack(int _Dmg)
	{
		PlayerHP -= _Dmg;
	}

protected:
	int PlayerHP = 3;
	float SuperModeEnergy = 0;


private:

};

