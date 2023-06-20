#pragma once
#include <functional>
#include "Player.h"

enum class PlayerOverWorldModeState
{
	IDLE,
	MOVE,
	WIN,
	MAX,
};

// Ό³Έν :
class PlayerOverWorldMode : public Player
{
public:
	// constrcuter destructer
	PlayerOverWorldMode();
	~PlayerOverWorldMode();

	// delete Function
	PlayerOverWorldMode(const PlayerOverWorldMode& _Other) = delete;
	PlayerOverWorldMode(PlayerOverWorldMode&& _Other) noexcept = delete;
	PlayerOverWorldMode& operator=(const PlayerOverWorldMode& _Other) = delete;
	PlayerOverWorldMode& operator=(PlayerOverWorldMode&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:

	std::shared_ptr<class GameEngineSpriteRenderer> PlayerRender = nullptr;


	float  MoveSpeed = 500.0f;
	std::string CurAnimation = "Down_Right_";
	float4 MoveVec = float4::Zero;
	float4 MaxPlayerSize = float4(115, 102);


	PlayerOverWorldModeState CurState = PlayerOverWorldModeState::IDLE;
	PlayerOverWorldModeState NextState = PlayerOverWorldModeState::IDLE;

	void MoveUpdate(float _DeltaTime);
	void UpdateState(float _DeltaTime);
	void CheckInput();
	void MainCameraMove(float _DeltaTime);


	void Idle_Start();
	void Idle_Update(float _DeltaTime);
	void Idle_End();

	void MoveUp_Start();
	void MoveUp_Update(float _DeltaTime);
	void MoveUp_End();

	void Win_Start();
	void Win_Update(float _DeltaTime);
	void Win_End();

	std::function<void()> StartFuncPtr[static_cast<int>(PlayerOverWorldModeState::MAX)];
	std::function<void(float)> UpdateFuncPtr[static_cast<int>(PlayerOverWorldModeState::MAX)];
	std::function<void()> EndFuncPtr[static_cast<int>(PlayerOverWorldModeState::MAX)];

};

