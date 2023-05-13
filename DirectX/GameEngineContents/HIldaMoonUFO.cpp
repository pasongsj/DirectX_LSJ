#include "PrecompileHeader.h"
#include "HIldaMoonUFO.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>


HIldaMoonUFO::HIldaMoonUFO() 
{
}

HIldaMoonUFO::~HIldaMoonUFO() 
{
}

void HIldaMoonUFO::MakeSprite()
{
	if (nullptr == GameEngineSprite::Find("Hilda_UFO_Red"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources");
		Dir.Move("Texture");
		Dir.Move("stage1\\Boss\\Hilda\\Moon\\Projectiles\\UFO");

		GameEngineSprite::LoadFolder("Hilda_UFO_Red", Dir.GetPlusFileName("Red").GetFullPath());
		GameEngineSprite::LoadFolder("Hilda_UFO_Bronze", Dir.GetPlusFileName("Bronze").GetFullPath());
		GameEngineSprite::LoadFolder("Hilda_UFO_Beam", Dir.GetPlusFileName("Beam").GetFullPath());
	}
}

void HIldaMoonUFO::Start()
{
	MakeSprite();
	UFORender = CreateComponent<GameEngineSpriteRenderer>();
	UFORender->CreateAnimation({.AnimationName = "Red", .SpriteName = "Hilda_UFO_Red", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true});
	UFORender->CreateAnimation({.AnimationName = "Bronze", .SpriteName = "Hilda_UFO_Bronze", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true});

	if (0 == (GameEngineRandom::MainRandom.RandomInt(0, 4) == 4))
	{
		UFORender->ChangeAnimation("Red");
	}
	else
	{
		UFORender->ChangeAnimation("Bronze");
	}
	
}

void HIldaMoonUFO::Update(float _DeltaTime)
{
	GetTransform()->AddLocalPosition(float4::Left * UFOSpeed * _DeltaTime);
}