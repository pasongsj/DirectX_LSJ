#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class OverWorldDustEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	OverWorldDustEffect();
	~OverWorldDustEffect();

	// delete Function
	OverWorldDustEffect(const OverWorldDustEffect& _Other) = delete;
	OverWorldDustEffect(OverWorldDustEffect&& _Other) noexcept = delete;
	OverWorldDustEffect& operator=(const OverWorldDustEffect& _Other) = delete;
	OverWorldDustEffect& operator=(OverWorldDustEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> SmokeREnder = nullptr;

};

