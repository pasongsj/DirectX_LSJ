#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class BoomEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	BoomEffect();
	~BoomEffect();

	// delete Function
	BoomEffect(const BoomEffect& _Other) = delete;
	BoomEffect(BoomEffect&& _Other) noexcept = delete;
	BoomEffect& operator=(const BoomEffect& _Other) = delete;
	BoomEffect& operator=(BoomEffect&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Update(float _DeltaTime) override;

private:

	std::shared_ptr<class GameEngineSpriteRenderer> Explode;
	std::shared_ptr<class GameEngineSpriteRenderer> Boom;

};

