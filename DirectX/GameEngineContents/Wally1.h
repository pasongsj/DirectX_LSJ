#pragma once
#include "WallyBoss.h"

enum class Wally1State
{
	CUCKOOINTRO,
	INTRO,
	IDLE,
	BARF, //egg,  handgun, 
	HANDGUN,
	STEAM, 
	FLAP,
	PANT,
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

	void Attack(int _Dmg) override;

protected:

	void Start() override;
	void Update(float _DeltaTime) override;

private:

	// idle Move
	float MoveDuration = 0.0f;
	float MoveRange = 200.0f;
	float AttackInterval = 1.0f;
	// cuckoo intro
	int IntroCount = 0;
	bool isFeetIntroEnd = false;

	// flap intro
	bool isFlapIntroDone = false;
	int FlapLoopCout = 0;
	bool isFlapLoopDone = false;
	float FeatherInterval = 0.1f;
	bool FeatherDegree = true;

	// pant
	int PantLoopCount = 0;
	int PantCount = 0;

	// state
	Wally1State CurState = Wally1State::CUCKOOINTRO;
	Wally1State NextState = Wally1State::CUCKOOINTRO;

	// flappy
	float4 FlappyPos = float4(640, 200);
	float FlappyPatternInterval = 5.0f;
	int FlappyCount = 4;
	float FlappySponeInterval = 0.0f;


	std::shared_ptr<class ContentsSortRenderer> HouseRender = nullptr;
	std::shared_ptr<class ContentsSortRenderer> FeetRender = nullptr;
	std::shared_ptr<class ContentsSortRenderer> HeadRender = nullptr;
	std::shared_ptr<class GameEngineCollision> HeadCollision = nullptr;
	std::shared_ptr<class GameEngineCollision> BodyCollision = nullptr;

	void SettingRender();
	void SettingCollision();

	void UpdateState(float _DeltaTime);
	void MoveUpdate(float _DeltaTime);

	void CuckooIntro_Start();
	void CuckooIntro_Update(float _DeltaTime);
	void CuckooIntro_End();

	void Intro_Start();
	void Intro_Update(float _DeltaTime);
	void Intro_End();

	void Idle_Start();
	void Idle_Update(float _DeltaTime);
	void Idle_End();

	void Barf_Start();
	void Barf_Update(float _DeltaTime);
	void Barf_End();

	void HandGun_Start();
	void HandGun_Update(float _DeltaTime);
	void HandGun_End();

	void Steam_Start();
	void Steam_Update(float _DeltaTime);
	void Steam_End();

	void Flap_Start();
	void Flap_Update(float _DeltaTime);
	void Flap_End();
	
	void Pant_Start();
	void Pant_Update(float _DeltaTime);
	void Pant_End();

	void ChangePhase_Start();
	void ChangePhase_Update(float _DeltaTime);
	void ChangePhase_End();

	std::function<void()> StartFuncPtr[static_cast<int>(Wally1State::MAX)];
	std::function<void(float)> UpdateFuncPtr[static_cast<int>(Wally1State::MAX)];
	std::function<void()> EndFuncPtr[static_cast<int>(Wally1State::MAX)];

	void MakeSprite();
	void MakeFeather();

	void FlappyBirdSpone(float _DeltaTime);

};

