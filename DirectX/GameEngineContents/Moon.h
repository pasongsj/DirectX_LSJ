#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class MoonState
{
	IDLE,
	ATTACK,
	DEATH,
	MAX,
};

// Ό³Έν :
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
	std::shared_ptr<class GameEngineSpriteRenderer> Boss;

	MoonState CurState = MoonState::IDLE;
	MoonState NextState = MoonState::IDLE;



	void UpdateState(float _DeltaTime);

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

