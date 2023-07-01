#pragma once
#include "WallyBoss.h"

enum class Wally2State
{
	INTRO,
	IDLE,
	SHOOT,
	DEATH,
	MAX,
};

// Ό³Έν :
class Wally2 : public WallyBoss
{
public:
	// constrcuter destructer
	Wally2();
	~Wally2();

	// delete Function
	Wally2(const Wally2& _Other) = delete;
	Wally2(Wally2&& _Other) noexcept = delete;
	Wally2& operator=(const Wally2& _Other) = delete;
	Wally2& operator=(Wally2&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	std::shared_ptr<class GameEngineSpriteRenderer> BossRender = nullptr;
	std::shared_ptr<GameEngineActor> EggController = nullptr;
	std::vector < std::shared_ptr<class Wally2_Egg>> Eggs;

	// idle
	bool isTransAnimatioin = false;
	float BeforDir = 1.0f;
	float AttackInterval = 1.0f;

	// idle Move
	float MoveDuration = 0.0f;
	float SpinSpeed = 200;

	// death
	bool isDeathLoop = false;
	int DeathLoopCount = 0;

	//state
	Wally2State CurState = Wally2State::INTRO;
	Wally2State NextState = Wally2State::INTRO;

	void MoveUpdate(float _DeltaTime);
	void UpdateState(float _DeltaTime);

	//fsm
	void Intro_Start();
	void Intro_Update(float _DeltaTime);
	void Intro_End();

	void Idle_Start();
	void Idle_Update(float _DeltaTime);
	void Idle_End();

	void Shoot_Start();
	void Shoot_Update(float _DeltaTime);
	void Shoot_End();

	void Death_Start();
	void Death_Update(float _DeltaTime);
	void Death_End();


	std::function<void()> StartFuncPtr[static_cast<int>(Wally2State::MAX)];
	std::function<void(float)> UpdateFuncPtr[static_cast<int>(Wally2State::MAX)];
	std::function<void()> EndFuncPtr[static_cast<int>(Wally2State::MAX)];

	void MakeSprite();
	void SettingEggs();
};

