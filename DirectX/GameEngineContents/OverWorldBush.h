#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class OverWorldBush : public GameEngineActor
{
public:
	// constrcuter destructer
	OverWorldBush();
	~OverWorldBush();

	// delete Function
	OverWorldBush(const OverWorldBush& _Other) = delete;
	OverWorldBush(OverWorldBush&& _Other) noexcept = delete;
	OverWorldBush& operator=(const OverWorldBush& _Other) = delete;
	OverWorldBush& operator=(OverWorldBush&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

