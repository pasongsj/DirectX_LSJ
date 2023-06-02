#include "PrecompileHeader.h"
#include "PeaShooter.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "GameEnermy.h"
#include "PeashotFX.h"
PeaShooter::PeaShooter() 
{
}

PeaShooter::~PeaShooter() 
{
}

void PeaShooter::MakeSprite()
{
	if (nullptr == GameEngineSprite::Find("Cuphead_AirPlane_Bullet"))
	{

		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Cuphead_AirPlane\\bullet");



		// Origin
		// idle

		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Bullet", NewDir.GetPlusFileName("peashot").GetFullPath());
	}
}

void PeaShooter::Start()
{

	MakeSprite();

	Bullet = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::PlayerEffect);
	Bullet->CreateAnimation({ .AnimationName = "Origin",  .SpriteName = "Cuphead_AirPlane_Bullet", .FrameInter = 0.1f, .Loop = true, .ScaleToTexture = true });

	Bullet->ChangeAnimation("Origin");

	BulletCollision = CreateComponent<GameEngineCollision>(CupHeadCollisionOrder::PlayerWepaon);
	BulletCollision->GetTransform()->SetLocalScale(Bullet->GetTransform()->GetLocalScale().half());
	BulletCollision->SetColType(ColType::AABBBOX2D);

}

void PeaShooter::Update(float _DeltaTime)
{
	//BulletCollision->GetTransform()->SetLocalScale(Bullet->GetTransform()->GetLocalScale());
	BulletCollision->SetRenderScaleToCollision(Bullet);

	GetTransform()->AddLocalPosition(float4(ShootSpeed * _DeltaTime, 0));
	GetTransform()->GetLocalPosition();

	std::shared_ptr<GameEngineCollision> Col = nullptr;
	if (GameEngineWindow::GameEngineWindow().GetScreenSize().x < GetTransform()->GetLocalPosition().x)
	{
		Death();
	}
	else if (nullptr != (Col = BulletCollision->Collision(CupHeadCollisionOrder::Enemy)))
	{
		if (nullptr != Col && false == Col->IsDeath())
		{
			std::shared_ptr<GameEnermy> ColActor = Col->GetActor()->DynamicThis<GameEnermy>();
			if (nullptr != ColActor)
			{
				ColActor->Attack(Dmg);
				std::shared_ptr<PeashotFX> FX = GetLevel()->CreateActor<PeashotFX>(CupHeadActorOrder::PlayerEffect);
				FX->GetTransform()->SetLocalPosition(GetTransform()->GetWorldPosition());
				Death();
				return;
			}

		}
	}
}