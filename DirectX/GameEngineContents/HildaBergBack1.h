#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : BackGround dark hill
class HildaBergBack1 : public GameEngineActor
{
public:
	// constrcuter destructer
	HildaBergBack1();
	~HildaBergBack1();

	// delete Function
	HildaBergBack1(const HildaBergBack1& _Other) = delete;
	HildaBergBack1(HildaBergBack1&& _Other) noexcept = delete;
	HildaBergBack1& operator=(const HildaBergBack1& _Other) = delete;
	HildaBergBack1& operator=(HildaBergBack1&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Update(float _DeltaTime) override;


private:

	//std::shared_ptr<class GameEngineSpriteRenderer> MainBG = nullptr;
	//std::shared_ptr<class GameEngineSpriteRenderer> SubBG = nullptr;
	//int BGRange = 0;
	//int BGLimit = 0;


	std::shared_ptr<class GameEngineSpriteRenderer> MainHill = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> SubHill = nullptr;
	int HillRange = 0;
	int HillLimit = 0;


	//void MakeSprite();
};

