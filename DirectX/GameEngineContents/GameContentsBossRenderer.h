#pragma once
#include <GameEngineCore/GameEngineSpriteRenderer.h>


// ���� :
class GameContentsBossRenderer : public GameEngineSpriteRenderer
{

public:
	// constrcuter destructer
	GameContentsBossRenderer();
	~GameContentsBossRenderer();
	

	float4 BrightOptionValue;
protected:
	void Start() override;

};