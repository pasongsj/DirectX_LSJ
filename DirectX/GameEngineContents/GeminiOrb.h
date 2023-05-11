#pragma once
#include <GameEngineCore/GameEngineActor.h>
// Ό³Έν :

enum class OrbState
{
	IDLE,
	ATTACK,
	MAX
};

class GeminiOrb : public GameEngineActor
{
public:
	// constrcuter destructer
	GeminiOrb();
	~GeminiOrb();

	// delete Function
	GeminiOrb(const GeminiOrb& _Other) = delete;
	GeminiOrb(GeminiOrb&& _Other) noexcept = delete;
	GeminiOrb& operator=(const GeminiOrb& _Other) = delete;
	GeminiOrb& operator=(GeminiOrb&& _Other) noexcept = delete;

	void Attack()
	{
		isAttack = true;
	}

	bool IsAttack() {
		return isAttack;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> Orb = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> OrbAttackEffect = nullptr;

	OrbState CurState = OrbState::IDLE;
	OrbState NextState = OrbState::IDLE;

	bool isLoop = false;
	bool isAttack = false;
	bool isLeaveAnimation = false;
	
	float StateChangeInterval = 2.0f;

	void MakeSprite();

	void UpdateState(float _DeltaTime);

	//	IDLE,
	//	ATTACK,
	void Idle_Start();
	void Idle_Update(float _DeltaTime);
	void Idle_End();

	void Attack_Start();
	void Attack_Update(float _DeltaTime);
	void Attack_End();


	std::function<void()> StartFuncPtr[static_cast<int>(OrbState::MAX)];
	std::function<void(float)> UpdateFuncPtr[static_cast<int>(OrbState::MAX)];
	std::function<void()> EndFuncPtr[static_cast<int>(OrbState::MAX)];


	
};

