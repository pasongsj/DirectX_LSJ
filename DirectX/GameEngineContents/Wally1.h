#pragma once
#include "WallyBoss.h"

enum class Wally1State
{
	INTRO,
	IDLE,
	SHOOT, //egg,  handgun, 
	STEAM,
	CHANGEPHASE,
	MAX,
};

class Wally1 : public WallyBoss
{
public:
	// constrcuter destructer
	Wally1() ;
	~Wally1();

	// delete Function
	Wally1(const Wally1& _Other) = delete;
	Wally1(Wally1&& _Other) noexcept = delete;
	Wally1& operator=(const Wally1& _Other) = delete;
	Wally1& operator=(Wally1&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameContentsEnemyRenderer> HouseRender = nullptr;
	std::shared_ptr<class GameContentsEnemyRenderer> FeetRender = nullptr;
	std::shared_ptr<class GameContentsEnemyRenderer> HeadRender = nullptr;
	std::shared_ptr<class GameEngineCollision> BossCollision = nullptr;


	void Intro_Start();
	void Intro_Update(float _DeltaTime);
	void Intro_End();

	void Idle_Start();
	void Idle_Update(float _DeltaTime);
	void Idle_End();

	void Shoot_Start();
	void Shoot_Update(float _DeltaTime);
	void Shoot_End();

	void Steam_Start();
	void Steam_Update(float _DeltaTime);
	void Steam_End();

	void ChangePhase_Start();
	void ChangePhase_Update(float _DeltaTime);
	void ChangePhase_End();

	std::function<void()> StartFuncPtr[static_cast<int>(Wally1State::MAX)];
	std::function<void(float)> UpdateFuncPtr[static_cast<int>(Wally1State::MAX)];
	std::function<void()> EndFuncPtr[static_cast<int>(Wally1State::MAX)];

	void MakeSprite();

};

