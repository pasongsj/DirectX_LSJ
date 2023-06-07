#pragma once
#include "HildaBoss.h"

enum class HildaState
{
	INTRO,
	IDLE,
	SHOOT,
	CHANGEPHASE,
	TORNADO, // 특정 페이즈에만 적용됨
	MAX,

};

// 설명 :
class Hilda : public HildaBoss
{
public:
	// constrcuter destructer
	Hilda();
	~Hilda();

	// delete Function
	Hilda(const Hilda& _Other) = delete;
	Hilda(Hilda&& _Other) noexcept = delete;
	Hilda& operator=(const Hilda& _Other) = delete;
	Hilda& operator=(Hilda&& _Other) noexcept = delete;

	void Attack(int _Dmg) override;

protected:

	void Start() override;
	void Update(float _DeltaTime) override;

	void SetPhase(int _Phase) override;

	void HildaDeath() override;


private:
	std::shared_ptr<class GameContentsBossRenderer> BossRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> BossSmokeRender = nullptr;
	std::shared_ptr<class GameEngineCollision> BossCollision = nullptr;

	// idle
	
	// attack
	float AttackInterval = 5.0f;
	
	//changephase
	bool isDashBackTurn = false;
	bool isBackTurn = false;
	float WaitingTime = 0.0f;
	float4 CurPos = float4::Zero;
	float4 DestPos = float4::Zero;

	HildaState CurState = HildaState::INTRO;
	HildaState NextState = HildaState::INTRO;


	void UpdateState(float _DeltaTime);

	void MakeSprite();

	//INTRO,
	//	SHOOT,
	//	CHANGEPHASE,
	//	TORNADO,

	void Intro_Start();
	void Intro_Update(float _DeltaTime);
	void Intro_End();

	void Idle_Start();
	void Idle_Update(float _DeltaTime);
	void Idle_End();

	void Shoot_Start();
	void Shoot_Update(float _DeltaTime);
	void Shoot_End();

	void ChangePhase_Start();
	void ChangePhase_Update(float _DeltaTime);
	void ChangePhase_End();

	void Tornado_Start();
	void Tornado_Update(float _DeltaTime);
	void Tornado_End();


	std::function<void()> StartFuncPtr[static_cast<int>(HildaState::MAX)];
	std::function<void(float)> UpdateFuncPtr[static_cast<int>(HildaState::MAX)];
	std::function<void()> EndFuncPtr[static_cast<int>(HildaState::MAX)];

};

