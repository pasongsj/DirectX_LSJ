#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Wally3_LeftBird : public GameEngineActor
{
	friend class Wally3;
public:
	// constrcuter destructer
	Wally3_LeftBird();
	~Wally3_LeftBird();

	// delete Function
	Wally3_LeftBird(const Wally3_LeftBird& _Other) = delete;
	Wally3_LeftBird(Wally3_LeftBird&& _Other) noexcept = delete;
	Wally3_LeftBird& operator=(const Wally3_LeftBird& _Other) = delete;
	Wally3_LeftBird& operator=(Wally3_LeftBird&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class ContentsSortRenderer> BirdRender = nullptr;
	float AttackInterval = 10.0f;
	bool isAttackAnimation = false;
	void MakeSprite();
};

