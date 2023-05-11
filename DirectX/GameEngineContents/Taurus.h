#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class TaurusState
{
	IDLE,
	ATTACK,
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
	float IdleMoveTime = 0.0f;
	float AttackInterval = 5.0f;

	TaurusState CurState = TaurusState::IDLE;
	TaurusState NextState = TaurusState::IDLE;

	// attack
	bool isCharge = true;
	float4 CurPos = float4::Zero;
	float4 DestPos = float4::Zero;
	
	void UpdateState(float _DeltaTime);

	void MakeSprite();

	//	IDLE,
	//	STING,
	void Idle_Start();
	void Idle_Update(float _DeltaTime);
	void Idle_End();

	void Attack_Start();
	void Attack_Update(float _DeltaTime);
	void Attack_End();


	std::function<void()> StartFuncPtr[static_cast<int>(TaurusState::MAX)];
	std::function<void(float)> UpdateFuncPtr[static_cast<int>(TaurusState::MAX)];
	std::function<void()> EndFuncPtr[static_cast<int>(TaurusState::MAX)];
};