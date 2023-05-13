#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class MoonState
{
	INTRO,
	IDLE,
	ATTACK,
	DEATH,
	MAX,
};

// 설명 :
class Moon : public GameEngineActor
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

protected:

	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> Boss = nullptr;

	MoonState CurState = MoonState::INTRO;
	MoonState NextState = MoonState::INTRO;

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

