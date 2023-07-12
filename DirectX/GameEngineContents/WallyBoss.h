#pragma once
#include "GameEnemy.h"

class WallyBoss : public GameEnemy
{
	friend class WallyLevel;
public:
	// constrcuter destructer
	WallyBoss() ;
	~WallyBoss();

	// delete Function
	WallyBoss(const WallyBoss& _Other) = delete;
	WallyBoss(WallyBoss&& _Other) noexcept = delete;
	WallyBoss& operator=(const WallyBoss& _Other) = delete;
	WallyBoss& operator=(WallyBoss&& _Other) noexcept = delete;

	inline int GetPhase()
	{
		return Phase;
	}

	virtual void BossDeath()
	{
		Death();
	};

protected:

	bool isAttack = false;


	virtual void SetPhase(int _Phase)
	{
		Phase = _Phase;
	}


private:
	// idle Move

	int Phase = 1;
};

