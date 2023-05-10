#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
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

	std::shared_ptr<class GameEngineSpriteRenderer> MainBG;
	std::shared_ptr<class GameEngineSpriteRenderer> SubBG;
	int BGRange = 0;
	int BGLimit = 0;


	std::shared_ptr<class GameEngineSpriteRenderer> MainHill;
	std::shared_ptr<class GameEngineSpriteRenderer> SubHill;
	int HillRange = 0;
	int HillLimit = 0;


	void MakeSprite();
};

