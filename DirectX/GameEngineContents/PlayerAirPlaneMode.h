#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <functional>

enum class PlayerAirPlaneModeState
{
	INTRO,
	IDLE,
	MOVE_UP,
	MOVE_DOWN,
	PARRY,
	SUPER_SKILL,
	MAX,
};


// 설명 :
class PlayerAirPlaneMode : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayerAirPlaneMode();
	~PlayerAirPlaneMode();

	// delete Function
	PlayerAirPlaneMode(const PlayerAirPlaneMode& _Other) = delete;
	PlayerAirPlaneMode(PlayerAirPlaneMode&& _Other) noexcept = delete;
	PlayerAirPlaneMode& operator=(const PlayerAirPlaneMode& _Other) = delete;
	PlayerAirPlaneMode& operator=(PlayerAirPlaneMode&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:

	float  MoveSpeed = 500.0f;
	std::shared_ptr<class GameEngineSpriteRenderer> PlayerRender = nullptr;

	PlayerAirPlaneModeState CurState = PlayerAirPlaneModeState::INTRO;
	PlayerAirPlaneModeState NextState = PlayerAirPlaneModeState::INTRO;

	void MoveUpdate(float _DeltaTime);

	void UpdateState(float _DeltaTime);


	// fsm 에 대한 함수


	void Intro_Start	();
	void Intro_Update	(float _DeltaTime);
	void Intro_End		();

	void Idle_Start		();
	void Idle_Update	(float _DeltaTime);
	void Idle_End		();

	void MoveUp_Start	();
	void MoveUp_Update	(float _DeltaTime);
	void MoveUp_End		();

	void MoveDown_Start	();
	void MoveDown_Update(float _DeltaTime);
	void MoveDown_End	();

	void Parry_Start	();
	void Parry_Update	(float _DeltaTime);
	void Parry_End		();

	void SuperSkill_Start	();
	void SuperSkill_Update	(float _DeltaTime);
	void SuperSkill_End		();


	std::function<void()> StartFuncPtr[static_cast<int>(PlayerAirPlaneModeState::MAX)];
	std::function<void(float)> UpdateFuncPtr[static_cast<int>(PlayerAirPlaneModeState::MAX)];
	std::function<void()> EndFuncPtr[static_cast<int>(PlayerAirPlaneModeState::MAX)];

};

