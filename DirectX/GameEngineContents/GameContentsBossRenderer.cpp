#include "PrecompileHeader.h"
#include "GameContentsBossRenderer.h"

GameContentsBossRenderer::GameContentsBossRenderer() 
{
}

GameContentsBossRenderer::~GameContentsBossRenderer() 
{
}

void GameContentsBossRenderer::Start()
{
	GameEngineRenderer::Start();

	SetMesh("Rect");
	SetPipeLine("Glowshader");

	AtlasData.x = 0.0f;
	AtlasData.y = 0.0f;
	AtlasData.z = 1.0f;
	AtlasData.w = 1.0f;

	Perc.Percentage = 1.0f;
	Perc.Affect = true;


	GetShaderResHelper().SetConstantBufferLink("AtlasData", AtlasData);
	//GetShaderResHelper().SetConstantBufferLink("ColorOption", ColorOptionValue);
	GetShaderResHelper().SetConstantBufferLink("PercentData ", Perc);
}