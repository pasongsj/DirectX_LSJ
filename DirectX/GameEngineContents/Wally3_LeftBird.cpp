#include "PrecompileHeader.h"
#include "Wally3_LeftBird.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

Wally3_LeftBird::Wally3_LeftBird() 
{
}

Wally3_LeftBird::~Wally3_LeftBird() 
{
}

void Wally3_LeftBird::MakeSprite()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentResources");
	Dir.Move("ContentResources\\Texture\\stage2\\Boss\\Wally\\Phase 3");


	if (nullptr == GameEngineSprite::Find("Wally3_LeftBird_Idle"))
	{
		// Bird
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Birds\\Bird A\\Idle").GetFullPath(), "Wally3_LeftBird_Idle");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Birds\\Bird A\\Attack").GetFullPath(), "Wally3_LeftBird_Attack");
	}
}

void Wally3_LeftBird::Start()
{
	MakeSprite();
	BirdRender = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::Enemy);
	BirdRender->CreateAnimation({ .AnimationName = "Idle",.SpriteName = "Wally3_LeftBird_Idle",.FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
	BirdRender->CreateAnimation({ .AnimationName = "Attack",.SpriteName = "Wally3_LeftBird_Attack",.FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	BirdRender->ChangeAnimation("Idle");
}

void Wally3_LeftBird::Update(float _DeltaTime)
{
}
