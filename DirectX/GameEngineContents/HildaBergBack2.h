#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class HildaBergBack2 : public GameEngineActor
{
public:
	// constrcuter destructer
	HildaBergBack2();
	~HildaBergBack2();

	// delete Function
	HildaBergBack2(const HildaBergBack2& _Other) = delete;
	HildaBergBack2(HildaBergBack2&& _Other) noexcept = delete;
	HildaBergBack2& operator=(const HildaBergBack2& _Other) = delete;
	HildaBergBack2& operator=(HildaBergBack2&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;


private:
	std::shared_ptr<class GameEngineSpriteRenderer> MainHill = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> SubHill = nullptr;
};

