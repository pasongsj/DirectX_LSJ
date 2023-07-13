#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 :
class Player : public GameEngineActor
{
	friend class GameEnemy;
	friend class PeaShooter;
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

	inline int GetSuperModeEnergy()
	{
		return (SuperModeEnergy > 500 ? 500 : SuperModeEnergy);
	}
	virtual void Attack(int _Dmg)
	{
		if (InvincibleTime < 0)
		{
			PlayerHP -= _Dmg;
			InvincibleTime = 2.0f; // 2 초동안 무적 상태
		}

	}

protected:
	int PlayerHP = 3;
	int SuperModeEnergy = 0;
	float InvincibleTime = 0.0f;

	void Start() override;
	


private:

};

