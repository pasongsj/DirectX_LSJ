#pragma once
#include <GameEngineCore/GameEngineActor.h>
// Ό³Έν :
class HildaDashBackExplodeFX : public GameEngineActor
{
	friend class Hilda;
public:
	// constrcuter destructer
	HildaDashBackExplodeFX();
	~HildaDashBackExplodeFX();

	// delete Function
	HildaDashBackExplodeFX(const HildaDashBackExplodeFX& _Other) = delete;
	HildaDashBackExplodeFX(HildaDashBackExplodeFX&& _Other) noexcept = delete;
	HildaDashBackExplodeFX& operator=(const HildaDashBackExplodeFX& _Other) = delete;
	HildaDashBackExplodeFX& operator=(HildaDashBackExplodeFX&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	std::shared_ptr<class GameEngineSpriteRenderer> ExplodeFX = nullptr;
	void MakeSprite();

	void MakeBigFX(float _Ratio);
};

