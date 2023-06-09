#include "PrecompileHeader.h"
#include "GameContentsUIRenderer.h"

GameContentsUIRenderer::GameContentsUIRenderer() 
{
}

GameContentsUIRenderer::~GameContentsUIRenderer() 
{
}
void GameContentsUIRenderer::SetAtlasData(float _StartX, float _StartY, float _SizeX, float _SizeY)
{
	AtlasData.x = _StartX;
	AtlasData.y = _StartY;
	AtlasData.z = _SizeX;
	AtlasData.w = _SizeY;
}




void GameContentsUIRenderer::SetCutTexture(const std::string_view& _Name, float _StartX, float _StartY, float _SizeX, float _SizeY)
{
	SetAtlasData(_StartX, _StartY, _SizeX, _SizeY);
	SetTexture(_Name);
	//AtlasData.x = _StartX;
	//AtlasData.y = _StartY;
	//AtlasData.z = _SizeX;
	//AtlasData.w = _SizeY;

}
void GameContentsUIRenderer::SetScaleToCutTexture(const std::string_view& _Name, float _StartX, float _StartY, float _SizeX, float _SizeY)
{
	SetCutTexture(_Name, _StartX, _StartY, _SizeX, _SizeY);
	std::shared_ptr<GameEngineTexture> FindTex = GameEngineTexture::Find(_Name);

	if (nullptr == FindTex)
	{
		MsgAssert("�������� �ʴ� �̹��� �Դϴ�.");
		return;
	}
	float4 scale = FindTex->GetScale();
	scale.x *= _SizeX;
	scale.y *= _SizeY;

	GetTransform()->SetLocalScale(scale);

}

void GameContentsUIRenderer::Update(float _DeltaTime)
{
	if (nullptr != CurAnimation)
	{
		CurAnimation->Update(_DeltaTime);

		const SpriteInfo& Info = CurAnimation->CurSpriteInfo();

		GetShaderResHelper().SetTexture("DiffuseTex", Info.Texture);

		if (true == CurAnimation->ScaleToTexture)
		{
			std::shared_ptr<GameEngineTexture> Texture = Info.Texture;

			float4 Scale = Texture->GetScale();

			Scale.x *= AtlasData.z;
			Scale.y *= AtlasData.w;
			Scale.z = 1.0f;

			Scale *= GetScaleRatio();

			GetTransform()->SetLocalScale(Scale);
		}
	}
}