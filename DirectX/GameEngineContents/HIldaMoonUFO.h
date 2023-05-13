#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class HIldaMoonUFO : public GameEngineActor
{
public:
	// constrcuter destructer
	HIldaMoonUFO();
	~HIldaMoonUFO();

	// delete Function
	HIldaMoonUFO(const HIldaMoonUFO& _Other) = delete;
	HIldaMoonUFO(HIldaMoonUFO&& _Other) noexcept = delete;
	HIldaMoonUFO& operator=(const HIldaMoonUFO& _Other) = delete;
	HIldaMoonUFO& operator=(HIldaMoonUFO&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> UFORender = nullptr;
	float UFOSpeed = 300.0f;

	void MakeSprite();
};

