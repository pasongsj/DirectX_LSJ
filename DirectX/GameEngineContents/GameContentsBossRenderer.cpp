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
	SetPipeLine("BrightShader");

	AtlasData.x = 0.0f;
	AtlasData.y = 0.0f;
	AtlasData.z = 1.0f;
	AtlasData.w = 1.0f;

	ColorOptionValue.MulColor = float4::One;
	ColorOptionValue.PlusColor = float4::Null;

	BrightOptionValue.x = 1;

	GetShaderResHelper().SetConstantBufferLink("AtlasData", AtlasData);
	GetShaderResHelper().SetConstantBufferLink("BrightOption", BrightOptionValue);

}
