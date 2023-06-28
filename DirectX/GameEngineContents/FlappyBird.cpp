#include "PrecompileHeader.h"
#include "FlappyBird.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineLevel.h>

FlappyBird::FlappyBird()
{
}

FlappyBird::~FlappyBird()
{
}
void FlappyBird::MakeSprite()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentResources"); 
	Dir.Move("ContentResources\\Texture\\stage2\\Boss\\Wally\\Phase 1\\FlappyBirds\\Bullet");
	if (nullptr == GameEngineSprite::Find("FlapyBird_Pink_Idle"))
	{
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Yellow\\Fly").GetFullPath(), "FlapyBird_Yellow_Idle");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Yellow\\Death").GetFullPath(), "FlapyBird_Yellow_Death");		

		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Pink\\Fly").GetFullPath(), "FlapyBird_Pink_Idle");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Pink\\Death").GetFullPath(), "FlapyBird_Pink_Death");
	}
}

void FlappyBird::Start()
{
	MakeSprite();
	BirdRender = CreateComponent< GameEngineSpriteRenderer>(CupHeadRendererOrder::EnemyWeapon);
	BirdRender->CreateAnimation({ .AnimationName = "Yellow_Idle",.SpriteName = "FlapyBird_Yellow_Idle",.FrameInter = 0.05f,.Loop = true, .ScaleToTexture = true });
	BirdRender->CreateAnimation({ .AnimationName = "Yellow_Death",.SpriteName = "FlapyBird_Yellow_Death",.FrameInter = 0.05f,.Loop = false, .ScaleToTexture = true });	
	BirdRender->CreateAnimation({ .AnimationName = "Pink_Idle",.SpriteName = "FlapyBird_Pink_Idle",.FrameInter = 0.05f,.Loop = true, .ScaleToTexture = true });
	BirdRender->CreateAnimation({ .AnimationName = "Pink_Death",.SpriteName = "FlapyBird_Pink_Death",.FrameInter = 0.05f,.Loop = false, .ScaleToTexture = true });
	BirdRender->ChangeAnimation("Yellow_Idle");
}

void FlappyBird::Update(float _DeltaTime)
{
}
void FlappyBird::SetPink()
{
	BirdRender->ChangeAnimation("Pink_Idle");
	PinkObject = true;
}