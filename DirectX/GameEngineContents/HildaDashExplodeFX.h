#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class HildaDashExplodeFX : public GameEngineActor
{
public:
	// constrcuter destructer
	HildaDashExplodeFX();
	~HildaDashExplodeFX();

	// delete Function
	HildaDashExplodeFX(const HildaDashExplodeFX& _Other) = delete;
	HildaDashExplodeFX(HildaDashExplodeFX&& _Other) noexcept = delete;
	HildaDashExplodeFX& operator=(const HildaDashExplodeFX& _Other) = delete;
	HildaDashExplodeFX& operator=(HildaDashExplodeFX&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	std::shared_ptr<class GameEngineSpriteRenderer> ExplodeFX = nullptr;

	void MakeSprite();
};

