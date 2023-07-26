#include "PrecompileHeader.h"
#include "ExBullet.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "GameEnemy.h"
#include "ItemEffect.h"

ExBullet::ExBullet()
{
}

ExBullet::~ExBullet()
{
}

void ExBullet::Start()
{
	MakeSprite();
	BulletRender = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::PlayerWepaon);
	BulletRender->CreateAnimation({ .AnimationName = "Idle",  .SpriteName = "Cuphead_AirPlane_ExBullet", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	BulletRender->ChangeAnimation("Idle");

	BulletCollision = CreateComponent<GameEngineCollision>(CupHeadCollisionOrder::PlayerWepaon);
	BulletCollision->GetTransform()->SetLocalScale(CollisionSize);
	BulletCollision->SetColType(ColType::AABBBOX2D);
}

void ExBullet::Update(float _DeltaTime)
{
	GetTransform()->AddLocalPosition(float4::Right * ShootSpeed * _DeltaTime);
	if (false == GetLevel()->GetMainCamera()->IsView(BulletRender->GetTransform()->GetTransDataRef()))
	{
		Death();
		return;
	}

	std::shared_ptr<GameEngineCollision> Col = nullptr;
	if (nullptr != (Col = BulletCollision->Collision(CupHeadCollisionOrder::Enemy)))
	{
		if (nullptr != Col && false == Col->IsDeath())
		{
			std::shared_ptr<GameEnemy> ColActor = Col->GetActor()->DynamicThis<GameEnemy>();
			if (nullptr != ColActor)
			{
				// 적에게 영향
				ColActor->Attack(static_cast<int>(Dmg * ItemEffect::DMGPERC));
				Death();
				return;
			}

		}
	}
}


void ExBullet::MakeSprite()
{
	if (nullptr == GameEngineSprite::Find("Cuphead_AirPlane_ExBullet"))
	{

		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources\\Texture\\Cuphead_AirPlane\\bullet");

		GameEngineSprite::LoadFolder("Cuphead_AirPlane_ExBullet", NewDir.GetPlusFileName("Ex_Bullet").GetFullPath());
	}
}