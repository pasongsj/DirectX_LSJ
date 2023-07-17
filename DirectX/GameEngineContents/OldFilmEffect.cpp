#include "PrecompileHeader.h"
#include "OldFilmEffect.h"

OldFilmEffect::OldFilmEffect()
{
}

OldFilmEffect::~OldFilmEffect()
{
}

//
void OldFilmEffect::Start(GameEngineRenderTarget* _Target)
{
	// 리소스 로드
	if (nullptr == GameEngineSprite::Find("OldFilmEffect"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("OldFilmEffect").GetFullPath());
	}

	OldUnit = std::make_shared<GameEngineRenderUnit>();
	OldUnit->SetMesh("FullRect");
	OldUnit->SetPipeLine("OldFilmEffect");

	OldData.x = 4.0f;

	OldUnit->ShaderResHelper.SetConstantBufferLink("OldFilmEffectData", OldData);


	ResultTarget = GameEngineRenderTarget::Create(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, GameEngineWindow::GetScreenSize(), float4::Null);
}

void OldFilmEffect::Effect(GameEngineRenderTarget* _Target, float _DeltaTime)
{
	std::shared_ptr<GameEngineSprite> Sprite = GameEngineSprite::Find("OldFilmEffect");
	SpriteInfo Info = Sprite->GetSpriteInfo(Index);

	FilmTimer += _DeltaTime;
	if (FilmTimer > FilmInterval)
	{
		FilmTimer -= FilmInterval;
		if (Sprite->GetSpriteCount() <= ++Index)
		{
			Index = 0;
		}
	}


	OldUnit->ShaderResHelper.SetTexture("DiffuseTex", Info.Texture);

	ResultTarget->Clear();
	ResultTarget->Setting();
	OldUnit->Render(_DeltaTime);
	OldUnit->ShaderResHelper.AllResourcesReset();

	// _Target->Clear();
	_Target->Merge(ResultTarget);

}