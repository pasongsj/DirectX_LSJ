#include "PrecompileHeader.h"
#include "Wally1_Bullet.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>

Wally1_Bullet::Wally1_Bullet()
{
}

Wally1_Bullet::~Wally1_Bullet()
{
}
void Wally1_Bullet::MakeSprite()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentResources"); // ContentResources\Texture\stage2\Boss\Wally\Phase 1
	Dir.Move("ContentResources\\Texture\\stage2\\Boss\\Wally\\Phase 1\\Handgun\\Bullet");
	if (nullptr == GameEngineSprite::Find("Wally1_Bullet_Pre"))
	{
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Pre").GetFullPath(), "Wally1_Bullet_Pre");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Shoot").GetFullPath(), "Wally1_Bullet_Shoot");
	}
}

void Wally1_Bullet::Start()
{
	MakeSprite();
	BulletRender = CreateComponent< GameEngineSpriteRenderer>(CupHeadRendererOrder::EnemyWeapon);
	BulletRender->CreateAnimation({ .AnimationName = "Pre",.SpriteName = "Wally1_Bullet_Pre",.FrameInter = 0.05f,.Loop = false, .ScaleToTexture = true });
	BulletRender->CreateAnimation({ .AnimationName = "Shoot",.SpriteName = "Wally1_Bullet_Shoot",.FrameInter = 0.05f,.Loop = true, .ScaleToTexture = true });
	BulletRender->ChangeAnimation("Pre");

	BulletCollision = CreateComponent< GameEngineCollision>(CupHeadCollisionOrder::EnemyWeapon);
	BulletCollision->SetColType(ColType::OBBBOX2D);
	BulletCollision->GetTransform()->SetLocalScale(float4(80, 50));
	BulletCollision->GetTransform()->SetLocalPosition(float4(-25, 0));

	isShooted = false;

}

void Wally1_Bullet::Update(float _DeltaTime)
{
	if (false == isShooted && true == BulletRender->IsAnimationEnd())
	{
		isShooted = true;
		BulletRender->ChangeAnimation("Shoot");
	}
	else if (true == isShooted)
	{
		GetTransform()->AddLocalPosition(Dir * _DeltaTime * MoveSpeed);
	}
	if (false == GetLevel()->GetMainCamera()->IsView(GetTransform()->GetTransDataRef()))
	{
		Death();
		return;
	}
}
