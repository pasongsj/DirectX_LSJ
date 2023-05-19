#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class HildaBoss : public GameEngineActor
{
public:
	// constrcuter destructer
	HildaBoss();
	~HildaBoss();

	// delete Function
	HildaBoss(const HildaBoss& _Other) = delete;
	HildaBoss(HildaBoss&& _Other) noexcept = delete;
	HildaBoss& operator=(const HildaBoss& _Other) = delete;
	HildaBoss& operator=(HildaBoss&& _Other) noexcept = delete;

	inline void Attack(float _Dmg)
	{
		Hp -= _Dmg;
	}

	inline void SetPhase(int _Phase)
	{
		Phase = _Phase;
	}

	inline int GetPhase()
	{
		return Phase;
	}
	
	virtual void BossDeath() 
	{
		Death();
	};


protected:
	float Hp = 0;
	float4 GetHildaMove(float _Delta);
	
	inline void AddIdleMoveTime(float _Delta)
	{
		IdleMoveTime += _Delta;
	}
	bool isAttack = false;

private:

	// idle Move
	int CircleMove = 1;
	int LastShare = -1;
	float SpinSpeed = 100.0f;
	float IdleMoveTime = 0.0f;

	int Phase = 1;



};

