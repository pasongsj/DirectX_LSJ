#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "HildaBoss.h"


enum class SagittariusState
{
	IDLE,
	ATTACK,
	MAX,

};

// Ό³Έν :
class Sagittarius : public HildaBoss
{
public:
	// constrcuter destructer
	Sagittarius();
	~Sagittarius();

	// delete Function
	Sagittarius(const Sagittarius& _Other) = delete;
	Sagittarius(Sagittarius&& _Other) noexcept = delete;
	Sagittarius& operator=(const Sagittarius& _Other) = delete;
	Sagittarius& operator=(Sagittarius&& _Other) noexcept = delete;

	void Attack(int _Dmg) override;


protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:

	std::shared_ptr<class GameContentsEnemyRenderer> Upper = nullptr;
	std::shared_ptr<class GameContentsEnemyRenderer> Lower = nullptr;

	std::shared_ptr<class GameEngineCollision> BossCollision = nullptr;

	bool isShoot = false;

	float AttackInterval = 5.0f;

	SagittariusState CurState = SagittariusState::IDLE;
	SagittariusState NextState = SagittariusState::IDLE;

	void MakeSprite();

	void UpdateState(float _DeltaTime);

	//	IDLE,
	//	STING,
	void Idle_Start();
	void Idle_Update(float _DeltaTime);
	void Idle_End();

	void Attack_Start();
	void Attack_Update(float _DeltaTime);
	void Attack_End();


	std::function<void()> StartFuncPtr[static_cast<int>(SagittariusState::MAX)];
	std::function<void(float)> UpdateFuncPtr[static_cast<int>(SagittariusState::MAX)];
	std::function<void()> EndFuncPtr[static_cast<int>(SagittariusState::MAX)];
};

