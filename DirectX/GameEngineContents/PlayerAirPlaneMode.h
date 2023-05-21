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
	MAX,
};


// 설명 :
class PlayerAirPlaneMode : public GameEngineActor
{
public:

	static PlayerAirPlaneMode* MainPlayer;
	// constrcuter destructer
	PlayerAirPlaneMode();
	~PlayerAirPlaneMode();

	// delete Function
	PlayerAirPlaneMode(const PlayerAirPlaneMode& _Other) = delete;
	PlayerAirPlaneMode(PlayerAirPlaneMode&& _Other) noexcept = delete;
	PlayerAirPlaneMode& operator=(const PlayerAirPlaneMode& _Other) = delete;
	PlayerAirPlaneMode& operator=(PlayerAirPlaneMode&& _Other) noexcept = delete;

	inline int GetHP()
	{
		return PlayerHP;
	}
	
	inline int GetSuperModeEnergy()
	{
		return SuperModeEnergy;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:

	int PlayerHP = 3;
	int SuperModeEnergy = 0;

	float  MoveSpeed = 500.0f;
	float4 MoveVec = float4::Zero;


	std::shared_ptr<class GameEngineSpriteRenderer> PlayerRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> Spark = nullptr;

	std::shared_ptr<class GameEngineCollision> PlayerCollsion = nullptr;


	PlayerAirPlaneModeState CurState = PlayerAirPlaneModeState::INTRO;
	PlayerAirPlaneModeState NextState = PlayerAirPlaneModeState::INTRO;


	std::string CurMode = "Origin";


	// bullet
	float ShootInterVal = 1.0f;
	float BulletYPos = 20.0f;
	
	// Effect Interval
	float SmokeInterval = 0.3f;

	void MoveUpdate(float _DeltaTime);

	void UpdateState(float _DeltaTime);

	void CheckInput();

	void ChangePlayerAnimation(const std::string_view& _State);

	void CheckShoot(float _DeltaTime);

	void ChangeMode(const std::string_view& _Mode);

	void MakeSprite();

	void MakeSmoke(float _DeltaTime);

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


	std::function<void()> StartFuncPtr[static_cast<int>(PlayerAirPlaneModeState::MAX)];
	std::function<void(float)> UpdateFuncPtr[static_cast<int>(PlayerAirPlaneModeState::MAX)];
	std::function<void()> EndFuncPtr[static_cast<int>(PlayerAirPlaneModeState::MAX)];

	bool isStartAnimationDone = true;


};

