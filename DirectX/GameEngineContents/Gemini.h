#pragma once
#include "HildaBoss.h"

enum class GeminiState 
{
	IDLE,
	ATTACK,
	MAX,
};

// Ό³Έν :
class Gemini : public HildaBoss
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

	void Attack(int _Dmg) override;

protected:

	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameContentsEnemyRenderer> BossA = nullptr;
	std::shared_ptr<class GameContentsEnemyRenderer> BossB = nullptr;

	std::shared_ptr<class GameEngineCollision> BossCollisionA = nullptr;
	std::shared_ptr<class GameEngineCollision> BossCollisionB = nullptr;

	bool isOrbIntroEnd = false;

	GeminiState CurState = GeminiState::IDLE;
	GeminiState NextState = GeminiState::IDLE;

	void SettingRender();

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
	
	std::shared_ptr< class GameEngineSpriteRenderer> Orb = nullptr;
};

