#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class HildaState
{
	INTRO,

};

// Ό³Έν :
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
};

