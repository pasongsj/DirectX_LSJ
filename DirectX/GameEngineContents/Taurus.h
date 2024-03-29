#pragma once
#include "HildaBoss.h"

enum class TaurusState
{
	IDLE,
	ATTACK,
	MAX,

};


// ���� :
class Taurus : public HildaBoss
{
public:
	// constrcuter destructer
	Taurus();
	~Taurus();

	// delete Function
	Taurus(const Taurus& _Other) = delete;
	Taurus(Taurus&& _Other) noexcept = delete;
	Taurus& operator=(const Taurus& _Other) = delete;
	Taurus& operator=(Taurus&& _Other) noexcept = delete;

	void Attack(int _Dmg) override;


protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	std::shared_ptr<class GameContentsEnemyRenderer> BossRender = nullptr;
	std::shared_ptr<class GameEngineCollision> BossCollision = nullptr;

	float AttackInterval = 5.0f;

	TaurusState CurState = TaurusState::IDLE;
	TaurusState NextState = TaurusState::IDLE;

	void SettingRender();
	void SettingCollision();

	// attack
	bool isCharge = true;
	float4 CurPos = float4::Zero;
	float4 DestPos = float4::Zero;
	float IdleSoundInterval = 3.0f;
	
	void UpdateState(float _DeltaTime);

	void MakeSprite();

	//	IDLE,
	//	STING,
	void Idle_Start();
	void Idle_Update(float _DeltaTime);
	void Idle_End();

	void Attack_Start();
	void Attack_Update(float _DeltaTime);
	void Attack_End();


	std::function<void()> StartFuncPtr[static_cast<int>(TaurusState::MAX)];
	std::function<void(float)> UpdateFuncPtr[static_cast<int>(TaurusState::MAX)];
	std::function<void()> EndFuncPtr[static_cast<int>(TaurusState::MAX)];
};