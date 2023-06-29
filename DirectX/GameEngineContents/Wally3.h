#pragma once
#include "WallyBoss.h"

enum class Wally3State
{
	INTRO,
	IDLE,
	GARBAGE,
	REGURGITATE,
	DEATH,
	MAX,
};

// Ό³Έν :
class Wally3 : public WallyBoss
{
public:
	// constrcuter destructer
	Wally3();
	~Wally3();

	// delete Function
	Wally3(const Wally3& _Other) = delete;
	Wally3(Wally3&& _Other) noexcept = delete;
	Wally3& operator=(const Wally3& _Other) = delete;
	Wally3& operator=(Wally3&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameContentsEnemyRenderer> BossRender = nullptr;
	std::shared_ptr<GameEngineActor> RightBird = nullptr;
	std::shared_ptr<GameEngineActor> LeftBird = nullptr;

	//Garbage
	bool isGarbageIntroDone = false;
	bool isGarbageLoopDone = false;
	int GarbageCount = 0;

	//Regurgitate
	bool isRegurgitateIntroDone = false;
	bool isRegurgitateLoopDone = false;
	int RegurgitateCount = 0;

	// state
	Wally3State CurState = Wally3State::INTRO;
	Wally3State NextState = Wally3State::INTRO;

	void MoveUpdate(float _DeltaTime);
	void UpdateState(float _DeltaTime);

	//fsm
	void Intro_Start();
	void Intro_Update(float _DeltaTime);
	void Intro_End();

	void Idle_Start();
	void Idle_Update(float _DeltaTime);
	void Idle_End();

	void Garbage_Start();
	void Garbage_Update(float _DeltaTime);
	void Garbage_End();

	void Regurgitate_Start();
	void Regurgitate_Update(float _DeltaTime);
	void Regurgitate_End();

	void Death_Start();
	void Death_Update(float _DeltaTime);
	void Death_End();


	std::function<void()> StartFuncPtr[static_cast<int>(Wally3State::MAX)];
	std::function<void(float)> UpdateFuncPtr[static_cast<int>(Wally3State::MAX)];
	std::function<void()> EndFuncPtr[static_cast<int>(Wally3State::MAX)];

	void MakeSprite();

};

