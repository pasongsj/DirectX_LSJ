#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class GeminiState 
{
	IDLE,
	ATTACK,
	MAX,
};

// Ό³Έν :
class Gemini : public GameEngineActor
{
public:
	// constrcuter destructer
	Gemini();
	~Gemini();

	// delete Function
	Gemini(const Gemini& _Other) = delete;
	Gemini(Gemini&& _Other) noexcept = delete;
	Gemini& operator=(const Gemini& _Other) = delete;
	Gemini& operator=(Gemini&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DletaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> BossA;
	std::shared_ptr<class GameEngineSpriteRenderer> BossB;

	int CircleMove = 1;
	int LastShare = -1;
	float SpinSpeed = 100.0f;
	float IdleMoveTime = 0.0f;
	bool isAttack = false;

	GeminiState CurState = GeminiState::IDLE;
	GeminiState NextState = GeminiState::IDLE;

	void UpdateState(float _DeltaTime);

	void Idle_Start();
	void Idle_Update(float _DeltaTime);
	void Idle_End();

	void Attack_Start();
	void Attack_Update(float _DeltaTime);
	void Attack_End();

	std::function<void()> StartFuncPtr[static_cast<int>(GeminiState::MAX)];
	std::function<void(float)> UpdateFuncPtr[static_cast<int>(GeminiState::MAX)];
	std::function<void()> EndFuncPtr[static_cast<int>(GeminiState::MAX)];
	
	std::shared_ptr< class GeminiOrb> Orb = nullptr;
};

