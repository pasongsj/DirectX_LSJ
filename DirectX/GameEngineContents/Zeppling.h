#pragma once
#include <functional>
#include <GameEngineCore/GameEngineActor.h>

enum class ZepplingState
{
	MOVE,
	SHOOT,
	TURN,
	BACK,
	DEAD,
	MAX,
};

// Ό³Έν :
class Zeppling : public GameEngineActor
{
public:

	//static std::vector<std::shared_ptr<Zeppling>> AllZepplings;
	// constrcuter destructer
	Zeppling();
	~Zeppling();

	// delete Function
	Zeppling(const Zeppling& _Other) = delete;
	Zeppling(Zeppling&& _Other) noexcept = delete;
	Zeppling& operator=(const Zeppling& _Other) = delete;
	Zeppling& operator=(Zeppling&& _Other) noexcept = delete;

	void Reset();

protected:

	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> Monster;

	std::shared_ptr<class ZepplingBullet> Bullet;

	ZepplingState CurState = ZepplingState::MOVE;
	ZepplingState NextState = ZepplingState::MOVE;

	float MoveSpeed = 200.0f;
	float MoveLen = 0.0f;

	std::string Mode = "Green_";




	void UpdateState(float _DeltaTime);

	void MakeSprite();



	void Move_Start();
	void Move_Update(float _DeltaTime);
	void Move_End();

	void Shoot_Start();
	void Shoot_Update(float _DeltaTime);
	void Shoot_End();

	void Turn_Start();
	void Turn_Update(float _DeltaTime);
	void Turn_End();

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

