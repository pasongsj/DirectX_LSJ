#pragma once
#include <GameEngineCore/GameEngineSpriteRenderer.h>


// Ό³Έν :
class GameContentsEnemyRenderer : public GameEngineSpriteRenderer
{

public:
	// constrcuter destructer
	GameContentsEnemyRenderer();
	~GameContentsEnemyRenderer();
	

	float4 BrightOptionValue;
	void MakeBright()
	{
		BrightInterval = 0.05f;
	}

protected:
	void Start() override;
	void Update(float _Delta) override;
	float BrightInterval = 0.0f;

};