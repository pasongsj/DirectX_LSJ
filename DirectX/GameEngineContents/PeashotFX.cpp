#include "PrecompileHeader.h"
#include "PeashotFX.h"
#include <GameEngineCore\GameEngineSprite.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

PeashotFX::PeashotFX() 
{
}

PeashotFX::~PeashotFX() 
{
}


void PeashotFX::MakeSprite()
{
	if (nullptr == GameEngineSprite::Find("peashotFX"))
	{

		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources\\Texture\\Cuphead_AirPlane\\bullet");

		GameEngineSprite::LoadFolder("peashotFX", NewDir.GetPlusFileName("peashotFX").GetFullPath());
	}
}

void PeashotFX::Start()
{
	MakeSprite();
	ExplodeFX = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::PlayerEffect);
	ExplodeFX->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "peashotFX", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	ExplodeFX->ChangeAnimation("Idle");
}

void PeashotFX::Update(float _DeltaTime)
{
	if (true == ExplodeFX->IsAnimationEnd())
	{
		Death();
		return;
	}
}