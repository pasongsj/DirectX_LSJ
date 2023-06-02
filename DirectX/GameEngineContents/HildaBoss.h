#pragma once
#include "GameEnermy.h"

// Ό³Έν :
class HildaBoss : public GameEnermy
{
	friend class HildaBergLevel;
public:
	// constrcuter destructer
	HildaBoss();
	~HildaBoss();

	// delete Function
	HildaBoss(const HildaBoss& _Other) = delete;
	HildaBoss(HildaBoss&& _Other) noexcept = delete;
	HildaBoss& operator=(const HildaBoss& _Other) = delete;
	HildaBoss& operator=(HildaBoss&& _Other) noexcept = delete;



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

	float4 GetHildaMove(float _Delta);
	
	inline void AddIdleMoveTime(float _Delta)
	{
		IdleMoveTime += _Delta;
	}

	virtual void SetPhase(int _Phase)
	{
		Phase = _Phase;
	}

	virtual void HildaDeath();


private:



	// idle Move
	int CircleMove = 1;
	int LastShare = -1;
	float SpinSpeed = 100.0f;
	float IdleMoveTime = 0.0f;

	int Phase = 1;



};

