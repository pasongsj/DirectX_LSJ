#include "PrecompileHeader.h"
#include "ChangeSuperModeEffect.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>


ChangeSuperModeEffect::ChangeSuperModeEffect() 
{
}

ChangeSuperModeEffect::~ChangeSuperModeEffect() 
{
}


void ChangeSuperModeEffect::MakeSprite()
{
	if (nullptr == GameEngineSprite::Find("Super_FX"))
	{

		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources\\Texture\\Cuphead_AirPlane\\effect");

		GameEngineSprite::LoadFolder("Super_FX", NewDir.GetPlusFileName("Super_FX").GetFullPath());

	}
}

void ChangeSuperModeEffect::Start()
{
	MakeSprite();
	FX = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::PlayerBackGround);
	FX->CreateAnimation({ .AnimationName = "Idle",  .SpriteName = "Super_FX",.FrameInter = 0.02f, .Loop = false , .ScaleToTexture = true });
	FX->ChangeAnimation("Idle");

}

void ChangeSuperModeEffect::Update(float _DeltaTime)
{
	if (true == FX->IsAnimationEnd())
	{
		Death();
	}

}