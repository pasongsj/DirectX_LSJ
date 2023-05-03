#include "PrecompileHeader.h"
#include "GameEngineSpriteRenderer.h"
#include "GameEngineTexture.h"

GameEngineSpriteRenderer::GameEngineSpriteRenderer()
{
}

GameEngineSpriteRenderer::~GameEngineSpriteRenderer()
{
}


void GameEngineSpriteRenderer::Start()
{
	GameEngineRenderer::Start();

	SetPipeLine("2DTexture");
}

void GameEngineSpriteRenderer::SetTexture(const std::string_view& _Name)
{
	GetShaderResHelper().SetTexture("DiffuseTex", _Name);
}

void GameEngineSpriteRenderer::SetScaleToTexture(const std::string_view& _Name)
{
	GetShaderResHelper().SetTexture("DiffuseTex", _Name);
	std::shared_ptr<GameEngineTexture> FindTex = GameEngineTexture::Find(_Name);
	float4 Scale = float4(FindTex->GetWidth(), FindTex->GetHeight(),1);
	GetTransform()->SetLocalScale(Scale);
}

void GameEngineSpriteRenderer::SetFlipX()
{
	float4 LocalScale = GetTransform()->GetLocalScale();
	LocalScale.x = -LocalScale.x;
	GetTransform()->SetLocalScale(LocalScale);
}

void GameEngineSpriteRenderer::SetFlipY()
{
	float4 LocalScale = GetTransform()->GetLocalScale();
	LocalScale.y = -LocalScale.y;
	GetTransform()->SetLocalScale(LocalScale);
}