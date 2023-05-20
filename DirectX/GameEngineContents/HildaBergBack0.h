#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : BackGround Sky, Cloud
class HildaBergBack0 : public GameEngineActor
{
public:
	// constrcuter destructer
	HildaBergBack0();
	~HildaBergBack0();

	// delete Function
	HildaBergBack0(const HildaBergBack0& _Other) = delete;
	HildaBergBack0(HildaBergBack0&& _Other) noexcept = delete;
	HildaBergBack0& operator=(const HildaBergBack0& _Other) = delete;
	HildaBergBack0& operator=(HildaBergBack0&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> MainBack = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> SubBack = nullptr;

};

