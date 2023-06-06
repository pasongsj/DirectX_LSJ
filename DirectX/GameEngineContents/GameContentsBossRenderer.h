#pragma once
#include <GameEngineCore/GameEngineSpriteRenderer.h>

struct PercentData
{
	float Percentage;
	bool Affect;

};
// ���� :
class GameContentsBossRenderer : public GameEngineSpriteRenderer
{

public:
	// constrcuter destructer
	GameContentsBossRenderer();
	~GameContentsBossRenderer();

	void Start() override;

	PercentData Perc;
};

