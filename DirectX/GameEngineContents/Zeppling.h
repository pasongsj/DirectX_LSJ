#pragma once
#include <functional>
#include <GameEngineCore/GameEngineActor.h>

enum class ZepplingState
{
	MOVE,
	SHOOT,
	BACK,
	DEAD,
	MAX,
};

// ���� :
class Zeppling : public GameEngineActor
{
public:
	// constrcuter destructer
	Zeppling();
	~Zeppling();

	// delete Function
	Zeppling(const Zeppling& _Other) = delete;
	Zeppling(Zeppling&& _Other) noexcept = delete;
	Zeppling& operator=(const Zeppling& _Other) = delete;
	Zeppling& operator=(Zeppling&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> Monster;
	ZepplingState CurState = ZepplingState::MOVE;
	ZepplingState NextState = ZepplingState::MOVE;

	float MoveSpeed = 200.0f;
	float MoveLen = 0.0f;



	void UpdateState(float _DeltaTime);



	void Move_Start();
	void Move_Update(float _DeltaTime);
	void Move_End();

	void Shoot_Start();
	void Shoot_Update(float _DeltaTime);
	void Shoot_End();

	void Dead_Start();
	void Dead_Update(float _DeltaTime);
	void Dead_End();

	void Back_Start();
	void Back_Update(float _DeltaTime);
	void Back_End();


	std::function<void()> StartFuncPtr[static_cast<int>(ZepplingState::MAX)];
	std::function<void(float)> UpdateFuncPtr[static_cast<int>(ZepplingState::MAX)];
	std::function<void()> EndFuncPtr[static_cast<int>(ZepplingState::MAX)];

};

