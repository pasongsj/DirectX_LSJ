#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� :
class HildaHA : public GameEngineActor
{
public:
	// constrcuter destructer
	HildaHA();
	~HildaHA();

	// delete Function
	HildaHA(const HildaHA& _Other) = delete;
	HildaHA(HildaHA&& _Other) noexcept = delete;
	HildaHA& operator=(const HildaHA& _Other) = delete;
	HildaHA& operator=(HildaHA&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> HaRender = nullptr;
	void MakeSprite();
};

