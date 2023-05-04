#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class HildaState
{
	INTRO,
	IDLE,
	SHOOT,
	CHANGEPHASE,
	TORNADO, // 특정 페이즈에만 적용됨
	MAX,

};

// 설명 :
class Hilda : public GameEngineActor
{
public:
	// constrcuter destructer
	Hilda();
	~Hilda();

	// delete Function
	Hilda(const Hilda& _Other) = delete;
	Hilda(Hilda&& _Other) noexcept = delete;
	Hilda& operator=(const Hilda& _Other) = delete;
	Hilda& operator=(Hilda&& _Other) noexcept = delete;

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

	HildaState CurState = HildaState::IDLE;
	HildaState NextState = HildaState::IDLE;


	void UpdateState(float _DeltaTime);

	//INTRO,
	//	SHOOT,
	//	CHANGEPHASE,
	//	TORNADO,

	void Intro_Start();
	void Intro_Update(float _DeltaTime);
	void Intro_End();

	void Idle_Start();
	void Idle_Update(float _DeltaTime);
	void Idle_End();

	void Shoot_Start();
	void Shoot_Update(float _DeltaTime);
	void Shoot_End();

	void ChangePhase_Start();
	void ChangePhase_Update(float _DeltaTime);
	void ChangePhase_End();

	void Tornado_Start();
	void Tornado_Update(float _DeltaTime);
	void Tornado_End();


	std::function<void()> StartFuncPtr[static_cast<int>(HildaState::MAX)];
	std::function<void(float)> UpdateFuncPtr[static_cast<int>(HildaState::MAX)];
	std::function<void()> EndFuncPtr[static_cast<int>(HildaState::MAX)];
};

