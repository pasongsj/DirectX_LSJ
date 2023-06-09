#include "PrecompileHeader.h"
#include "SupermodeShadowEffect.h"
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

SupermodeShadowEffect::SupermodeShadowEffect() 
{
}

SupermodeShadowEffect::~SupermodeShadowEffect() 
{
}

void SupermodeShadowEffect::Start()
{
	if (nullptr == GameEngineTexture::Find("BlackBack.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources\\Texture\\Cuphead_AirPlane\\effect");
		GameEngineTexture::Load(NewDir.GetPlusFileName("BlackBack.png").GetFullPath());
	}
	ShadowRender = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::PlayerBackGround);
	ShadowRender->SetScaleToTexture("BlackBack.png");
	GetTransform()->SetLocalPosition(float4(0, 0, 410));
}

