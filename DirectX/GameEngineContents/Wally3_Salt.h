#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Wally3_Salt : public GameEngineActor
{
public:
	// constrcuter destructer
	Wally3_Salt();
	~Wally3_Salt();

	// delete Function
	Wally3_Salt(const Wally3_Salt& _Other) = delete;
	Wally3_Salt(Wally3_Salt&& _Other) noexcept = delete;
	Wally3_Salt& operator=(const Wally3_Salt& _Other) = delete;
	Wally3_Salt& operator=(Wally3_Salt&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> SaltRender = nullptr;
	void MakeSprtie();
};

