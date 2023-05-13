#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� :
class HildaBergBack : public GameEngineActor
{
public:
	// constrcuter destructer
	HildaBergBack();
	~HildaBergBack();

	// delete Function
	HildaBergBack(const HildaBergBack& _Other) = delete;
	HildaBergBack(HildaBergBack&& _Other) noexcept = delete;
	HildaBergBack& operator=(const HildaBergBack& _Other) = delete;
	HildaBergBack& operator=(HildaBergBack&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Update(float _DeltaTime) override;


private:

	std::shared_ptr<class GameEngineSpriteRenderer> MainBG = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> SubBG = nullptr;
	int BGRange = 0;
	int BGLimit = 0;


	std::shared_ptr<class GameEngineSpriteRenderer> MainHill = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> SubHill = nullptr;
	int HillRange = 0;
	int HillLimit = 0;


	void MakeSprite();
};

