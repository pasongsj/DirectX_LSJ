#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� :
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
		return (SuperModeEnergy>500?500: SuperModeEnergy);
	}
	inline void Attack(int _Dmg)
	{
		if (InvincibleTime < 0)
		{
			PlayerHP -= _Dmg;
			InvincibleTime = 2.0f;
		}

	}

protected:
	int PlayerHP = 3;
	float SuperModeEnergy = 0.0f;
	float InvincibleTime = 0.0f;



private:

};

