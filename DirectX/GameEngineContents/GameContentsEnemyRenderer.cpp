#include "PrecompileHeader.h"
#include "GameContentsEnemyRenderer.h"

GameContentsEnemyRenderer::GameContentsEnemyRenderer() 
{
}

GameContentsEnemyRenderer::~GameContentsEnemyRenderer() 
{
}

void GameContentsEnemyRenderer::Start()
{
	GameEngineRenderer::Start();

	SetMesh("Rect");
	SetPipeLine("BrightShader");

	AtlasData.x = 0.0f;
	AtlasData.y = 0.0f;
	AtlasData.z = 1.0f;
	AtlasData.w = 1.0f;


	BrightOptionValue.x = 0.0f;

	GetShaderResHelper().SetConstantBufferLink("AtlasData", AtlasData);
	GetShaderResHelper().SetConstantBufferLink("BrightOption", BrightOptionValue);

}


void GameContentsEnemyRenderer::Update(float _Delta)
{
	BrightInterval -= _Delta;
	if (BrightInterval < 0.0f)
	{
		BrightOptionValue.x = 0.0f;
	}
	else
	{
		BrightOptionValue.x = 1.0f;
	}
	GameEngineSpriteRenderer::Update(_Delta);
}
