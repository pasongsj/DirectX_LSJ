#include "PrecompileHeader.h"
#include "Wally1_Feather.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineLevel.h>

Wally1_Feather::Wally1_Feather()
{
}

Wally1_Feather::~Wally1_Feather()
{
}

void Wally1_Feather::MakeSprite()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentResources"); // ContentResources\Texture\stage2\Boss\Wally\Phase 1
	Dir.Move("ContentResources\\Texture\\stage2\\Boss\\Wally\\Phase 1\\FeatherAttack\\Feathers");
	if (nullptr == GameEngineSprite::Find("Wally1_Feather_Blue"))
	{
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Blue").GetFullPath(), "Wally1_Feather_Blue");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Pink").GetFullPath(), "Wally1_Feather_Pink");
	}
	
}


void Wally1_Feather::Start()
{
	MakeSprite();
	FeatherRender = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::EnemyWeapon);
	FeatherRender->CreateAnimation({ .AnimationName = "Blue",.SpriteName = "Wally1_Feather_Blue",.FrameInter = 0.05f,.Loop = true, .ScaleToTexture = true });
	FeatherRender->CreateAnimation({ .AnimationName = "Pink",.SpriteName = "Wally1_Feather_Pink",.FrameInter = 0.05f,.Loop = true, .ScaleToTexture = true });
	FeatherRender->ChangeAnimation("Blue");
	if (false == GameEngineRandom::MainRandom.RandomInt(0, 20))
	{
		FeatherRender->ChangeAnimation("Pink");
		PinkObject = true;
	}

}

void Wally1_Feather::Update(float _DeltaTime)
{
	GetTransform()->AddLocalPosition(Dir * _DeltaTime * MoveSpeed);
	if (false == GetLevel()->GetMainCamera()->IsView(GetTransform()->GetTransDataRef()))
	{
		Death();
		return;
	}
}
