#include "PrecompileHeader.h"
#include "Wally3_Heart.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ZepplingBullet.h"

Wally3_Heart::Wally3_Heart()
{
}

Wally3_Heart::~Wally3_Heart()
{
}

void Wally3_Heart::MakeSprite()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentResources");
	Dir.Move("ContentResources\\Texture\\stage2\\Boss\\Wally\\Phase 3");
	if (nullptr == GameEngineSprite::Find("Wally3_Heart"))
	{
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Regurgitate\\Heart\\Heart").GetFullPath(), "Wally3_Heart");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Regurgitate\\Heart\\Mouse_Attack").GetFullPath(), "Wally3_Mouse_Attack");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Regurgitate\\Heart\\Mouse_Idle").GetFullPath(), "Wally3_Mouse_Idle");
	}
}

void Wally3_Heart::Start()
{
	MakeSprite();
	HeartRender = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::EnemyWeapon);
	MouseRender = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::EnemyWeapon);
	
	HeartRender->CreateAnimation({ .AnimationName = "Idle",.SpriteName = "Wally3_Heart",.FrameInter = 0.05f, .Loop = true,.ScaleToTexture = true });
	MouseRender->CreateAnimation({ .AnimationName = "Attack",.SpriteName = "Wally3_Mouse_Attack",.FrameInter = 0.05f, .Loop = false,.ScaleToTexture = true });
	MouseRender->SetAnimationStartEvent("Attack", 6, [this]
		{
			float4 MousePos = GetTransform()->GetWorldPosition();
			MousePos.z = 500;
			std::shared_ptr< ZepplingBullet> Bullet0 = GetLevel()->CreateActor< ZepplingBullet>(CupHeadActorOrder::EnemyWeapon);
			Bullet0->GetTransform()->SetLocalPosition(MousePos + float4(-60, 0));
			Bullet0->SetBulletDir(float4::Left);
			std::shared_ptr< ZepplingBullet> Bullet1 = GetLevel()->CreateActor< ZepplingBullet>(CupHeadActorOrder::EnemyWeapon);
			Bullet1->GetTransform()->SetLocalPosition(MousePos + float4(-60, 0));
			Bullet1->SetBulletDir(float4(-3,1));
			std::shared_ptr< ZepplingBullet> Bullet2 = GetLevel()->CreateActor< ZepplingBullet>(CupHeadActorOrder::EnemyWeapon);
			Bullet2->GetTransform()->SetLocalPosition(MousePos + float4(-60, 0));
			Bullet2->SetBulletDir(float4(-3, -1));
		});
	MouseRender->CreateAnimation({ .AnimationName = "Idle",.SpriteName = "Wally3_Mouse_Idle",.FrameInter = 0.05f, .Loop = true,.ScaleToTexture = true });
	HeartRender->ChangeAnimation("Idle");
	MouseRender->ChangeAnimation("Idle");

	HeartCollision = CreateComponent<GameEngineCollision>(CupHeadCollisionOrder::EnemyWeapon);
	HeartCollision->SetColType(ColType::SPHERE2D);
	HeartCollision->GetTransform()->SetLocalScale(float4(130,1,1));
}

void Wally3_Heart::Update(float _DeltaTime)
{
	if (float4::Down == Dir && GetTransform()->GetLocalPosition().y <= StartPoint.y)
	{
		Death();
		return;
	}


	AttackInterval -= _DeltaTime;
	if (false == GetLevel()->GetMainCamera()->IsView(GetTransform()->GetTransDataRef()))
	{
		Dir = float4::Down;
	}
	GetTransform()->AddLocalPosition(Dir * _DeltaTime * MoveSpeed);
	ControlAnimation();
}

void Wally3_Heart::ControlAnimation()
{
	if (false == isAttack && AttackInterval < 0)
	{
		MouseRender->GetTransform()->SetLocalPosition(float4(-50, 0));
		MouseRender->ChangeAnimation("Attack");
		isAttack = true;
		AttackInterval = 1.0f;
	}
	else if (true == isAttack && true == MouseRender->IsAnimationEnd())
	{
		MouseRender->GetTransform()->SetLocalPosition(float4(-20, 0));
		MouseRender->ChangeAnimation("Idle");
		isAttack = false;
	}
}
