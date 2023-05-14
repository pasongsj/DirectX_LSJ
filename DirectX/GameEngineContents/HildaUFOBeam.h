#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class HildaUFOBeam : public GameEngineActor
{
public:
	// constrcuter destructer
	HildaUFOBeam();
	~HildaUFOBeam();

	// delete Function
	HildaUFOBeam(const HildaUFOBeam& _Other) = delete;
	HildaUFOBeam(HildaUFOBeam&& _Other) noexcept = delete;
	HildaUFOBeam& operator=(const HildaUFOBeam& _Other) = delete;
	HildaUFOBeam& operator=(HildaUFOBeam&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> UFOBeamRender = nullptr;

	void MakeSprite();
};

