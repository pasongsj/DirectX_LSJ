#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class TaurusState
{
	IDLE,
	STING,
	MAX,

};


// Ό³Έν :
class Taurus : public GameEngineActor
{
public:
	// constrcuter destructer
	Taurus();
	~Taurus();

	// delete Function
	Taurus(const Taurus& _Other) = delete;
	Taurus(Taurus&& _Other) noexcept = delete;
	Taurus& operator=(const Taurus& _Other) = delete;
	Taurus& operator=(Taurus&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:

	std::shared_ptr<class GameEngineSpriteRenderer> Boss;

	int CircleMove = 1;
	int LastShare = -1;
	float SpinSpeed = 100.0f;

	float StingInterval = 5.0f;
	float IdleMoveTime = 0.0f;

	TaurusState CurState = TaurusState::IDLE;
	TaurusState NextState = TaurusState::IDLE;
	
	void UpdateState(float _DeltaTime);

	//	IDLE,
	//	STING,
	void Idle_Start();
	void Idle_Update(float _DeltaTime);
	void Idle_End();

	void String_Start();
	void String_Update(float _DeltaTime);
	void String_End();


	std::function<void()> StartFuncPtr[static_cast<int>(TaurusState::MAX)];
	std::function<void(float)> UpdateFuncPtr[static_cast<int>(TaurusState::MAX)];
	std::function<void()> EndFuncPtr[static_cast<int>(TaurusState::MAX)];
};