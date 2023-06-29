#include "PrecompileHeader.h"
#include "Wally3_RightBird.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

Wally3_RightBird::Wally3_RightBird()
{
}

Wally3_RightBird::~Wally3_RightBird()
{
}
void Wally3_RightBird::MakeSprite()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentResources");
	Dir.Move("ContentResources\\Texture\\stage2\\Boss\\Wally\\Phase 3");


	if (nullptr == GameEngineSprite::Find("Wally3_RightBird_Idle"))
	{
		// Bird
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Birds\\Bird B\\Idle").GetFullPath(), "Wally3_RightBird_Idle");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Birds\\Bird B\\Attack").GetFullPath(), "Wally3_RightBird_Attack");
	}
}

void Wally3_RightBird::Start()
{
	MakeSprite();
	BirdRender = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::Enemy);
	BirdRender->CreateAnimation({ .AnimationName = "Idle",.SpriteName = "Wally3_RightBird_Idle",.FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
	BirdRender->CreateAnimation({ .AnimationName = "Attack",.SpriteName = "Wally3_RightBird_Attack",.FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	BirdRender->ChangeAnimation("Idle");
}

void Wally3_RightBird::Update(float _DeltaTime)
{
}
