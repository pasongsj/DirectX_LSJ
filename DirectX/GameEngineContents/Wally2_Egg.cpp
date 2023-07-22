#include "PrecompileHeader.h"
#include "Wally2_Egg.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

Wally2_Egg::Wally2_Egg()
{
}

Wally2_Egg::~Wally2_Egg()
{
}

void Wally2_Egg::MakeSprite()
{
	if (nullptr == GameEngineSprite::Find("Wally2_Egg_Rotate"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources\\Texture\\stage2\\Boss\\Wally\\Phase 2\\Egg");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Rotate").GetFullPath(), "Wally2_Egg_Rotate");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Death").GetFullPath(), "Wally2_Egg_Death");
	}
}


void Wally2_Egg::Start()
{
	//MakeSprite();
	EggRender = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::EnemyWeapon);
	EggRender->CreateAnimation({ .AnimationName = "Idle",.SpriteName = "Wally2_Egg_Rotate", .FrameInter = 0.05f,.Loop = true, .ScaleToTexture = true });
	EggRender->CreateAnimation({ .AnimationName = "Death",.SpriteName = "Wally2_Egg_Death", .FrameInter = 0.05f,.Loop = false, .ScaleToTexture = true });
	EggRender->ChangeAnimation("Idle");


	EggCollision = CreateComponent< GameEngineCollision>(CupHeadCollisionOrder::EnemyWeapon);
	EggCollision->SetColType(ColType::SPHERE2D);
	EggCollision->GetTransform()->SetLocalScale(float4(80, 0));
	//EggCollision->GetTransform()->SetLocalPosition(float4(-30, 40));
}

void Wally2_Egg::Update(float _DeltaTime)
{
	if (true == isDeathAnimation && true == EggRender->IsAnimationEnd())
	{
		Death();
		return;
	}
	CollisionPlayer(EggCollision);

}


void Wally2_Egg::MakeDeath()
{
	EggRender->ChangeAnimation("Death");
	isDeathAnimation = true;
}
