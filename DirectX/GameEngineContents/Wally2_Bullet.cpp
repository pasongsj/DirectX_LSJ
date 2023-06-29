#include "PrecompileHeader.h"
#include "Wally2_Bullet.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "Player.h"
Wally2_Bullet::Wally2_Bullet()
{
}

Wally2_Bullet::~Wally2_Bullet()
{
}

void Wally2_Bullet::MakeSprite()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentResources"); // ContentResources\Texture\stage2\Boss\Wally\Phase 1
	Dir.Move("ContentResources\\Texture\\stage2\\Boss\\Wally\\Phase 2");
	if (nullptr == GameEngineSprite::Find("Wally2_Bullet"))
	{
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Bullet").GetFullPath(), "Wally2_Bullet");
	}
}
void Wally2_Bullet::Start()
{
	MakeSprite();
	BulletRender = CreateComponent< GameEngineSpriteRenderer>(CupHeadRendererOrder::EnemyWeapon);
	BulletRender->CreateAnimation({ .AnimationName = "Idle",.SpriteName = "Wally2_Bullet",.FrameInter = 0.05f,.Loop = true, .ScaleToTexture = true });
	BulletRender->ChangeAnimation("Idle");
}

void Wally2_Bullet::Update(float _DeltaTime)
{
	GetTransform()->AddLocalPosition(Dir * _DeltaTime * MoveSpeed);
	if (false == GetLevel()->GetMainCamera()->IsView(GetTransform()->GetTransDataRef()))
	{
		Death();
		return;
	}
}


void Wally2_Bullet::SetPos(const float4& _Pos)
{
	float4 PlayerPos = Player::MainPlayer->GetTransform()->GetWorldPosition();
	Dir = (PlayerPos - _Pos);
	Dir.z = 0;
	Dir.Normalize();
	GetTransform()->SetLocalPosition(_Pos);
	GetTransform()->SetLocalRotation(float4(0,0, GameEngineMath::PIE2 - (-Dir).GetAnagleDegZ()));
}