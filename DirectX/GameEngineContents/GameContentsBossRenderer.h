#pragma once
#include <GameEngineCore/GameEngineSpriteRenderer.h>


// Ό³Έν :
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