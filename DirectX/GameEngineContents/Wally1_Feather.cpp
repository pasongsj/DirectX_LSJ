#include "PrecompileHeader.h"
#include "Wally1_Feather.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>

Wally1_Feather::Wally1_Feather()
{
}

Wally1_Feather::~Wally1_Feather()
{
}

void Wally1_Feather::MakeSprite()
{
	if (nullptr == GameEngineSprite::Find("Wally1_Feather_Blue"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources"); // ContentResources\Texture\stage2\Boss\Wally\Phase 1
		Dir.Move("ContentResources\\Texture\\stage2\\Boss\\Wally\\Phase 1\\FeatherAttack\\Feathers");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Blue").GetFullPath(), "Wally1_Feather_Blue");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Pink").GetFullPath(), "Wally1_Feather_Pink");
	}
	
}


void Wally1_Feather::Start()
{
	//MakeSprite();
	FeatherRender = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::EnemyWeapon);
	FeatherRender->CreateAnimation({ .AnimationName = "Blue",.SpriteName = "Wally1_Feather_Blue",.FrameInter = 0.05f,.Loop = true, .ScaleToTexture = true });
	FeatherRender->CreateAnimation({ .AnimationName = "Pink",.SpriteName = "Wally1_Feather_Pink",.FrameInter = 0.05f,.Loop = true, .ScaleToTexture = true });
	FeatherRender->ChangeAnimation("Blue");
	if (false == GameEngineRandom::MainRandom.RandomInt(0, 20))
	{
		FeatherRender->ChangeAnimation("Pink");
		SetPinkObject();
	}

	FeatherCollision = CreateComponent< GameEngineCollision>(CupHeadCollisionOrder::EnemyWeapon);
	FeatherCollision->SetColType(ColType::OBBBOX2D);
	FeatherCollision->GetTransform()->SetLocalScale(float4(100, 20));
	//EggCollision->GetTransform()->SetLocalPosition(float4(-25, 0));

}

void Wally1_Feather::Update(float _DeltaTime)
{
	GetTransform()->AddLocalPosition(Dir * _DeltaTime * MoveSpeed);
	if (false == GetLevel()->GetMainCamera()->IsView(GetTransform()->GetTransDataRef()))
	{
		Death();
		return;
	}
	CollisionPlayer(FeatherCollision);
}
