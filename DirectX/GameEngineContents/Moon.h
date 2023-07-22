#pragma once
#include "HildaBoss.h"

enum class MoonState
{
	INTRO,
	IDLE,
	ATTACK,
	DEATH,
	MAX,
};

// 설명 :
class Moon : public HildaBoss
{
public:
	// constrcuter destructer
	Moon();
	~Moon();

	// delete Function
	Moon(const Moon& _Other) = delete;
	Moon(Moon&& _Other) noexcept = delete;
	Moon& operator=(const Moon& _Other) = delete;
	Moon& operator=(Moon&& _Other) noexcept = delete;

	void Attack(int _Dmg) override;


protected:

	void Start() override;
	void Update(float _DeltaTime) override;
	void HildaDeath() override;

private:
	std::shared_ptr<class GameContentsEnemyRenderer> BossRender = nullptr;
	std::shared_ptr<class GameEngineCollision> BossCollision = nullptr;

	MoonState CurState = MoonState::INTRO;
	MoonState NextState = MoonState::INTRO;
	void SettingRender();
	void SettingCollision();

	float4 StartPos = float4::Zero;
	float4 DestPos = float4::Zero;

	// intro
	int IntroAnimationIndex = 0;
	float IntroAnimationTimer = 0.0f;

	// idle 3초 attack 14초
	float IntervalTimer = 3.0f;

	// attack
	bool isAttackIntroDone = false;
	bool isAttackDone = false;
	
	// Death
	float DeathWaiting = 0.0f;

	// spone star
	float StarInterval = 1.0f;


	void MakeStar(float _DeltaTime);

	void MakeSprite();

	void UpdateState(float _DeltaTime);

	void Intro_Start();
	void Intro_Update(float _DeltaTime);
	void Intro_End();

	void Idle_Start();
	void Idle_Update(float _DeltaTime);
	void Idle_End();

	void Attack_Start();
	void Attack_Update(float _DeltaTime);
	void Attack_End();

	void Death_Start();
	void Death_Update(float _DeltaTime);
	void Death_End();


	std::function<void()> StartFuncPtr[static_cast<int>(MoonState::MAX)];
	std::function<void(float)> UpdateFuncPtr[static_cast<int>(MoonState::MAX)];
	std::function<void()> EndFuncPtr[static_cast<int>(MoonState::MAX)];

};

