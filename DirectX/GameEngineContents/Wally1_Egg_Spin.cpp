#include "PrecompileHeader.h"
#include "Wally1_Egg_Spin.h"
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Wally1_Egg_Pieces.h"
Wally1_Egg_Spin::Wally1_Egg_Spin()
{
}

Wally1_Egg_Spin::~Wally1_Egg_Spin()
{
}
void Wally1_Egg_Spin::MakeSprite()
{
	if (nullptr == GameEngineSprite::Find("Wally_Egg_Spin"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources"); // ContentResources\Texture\stage2\Boss\Wally\Phase 1
		Dir.Move("ContentResources\\Texture\\stage2\\Boss\\Wally\\Phase 1");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Egg\\Spin").GetFullPath(), "Wally_Egg_Spin");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Egg\\Dead").GetFullPath(), "Wally_Egg_Dead");
	}
}


void Wally1_Egg_Spin::Start()
{
	//MakeSprite();
	EggRender = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::EnemyWeapon);
	EggRender->CreateAnimation({ .AnimationName = "Idle",.SpriteName = "Wally_Egg_Spin",.FrameInter = 0.05f,.Loop = true, .ScaleToTexture = true });
	EggRender->CreateAnimation({ .AnimationName = "Dead",.SpriteName = "Wally_Egg_Dead",.FrameInter = 0.05f,.Loop = false, .ScaleToTexture = true });
	EggRender->ChangeAnimation("Idle");
	ScreenSize = GameEngineWindow::GetScreenSize();
	isDeadAnimation = false;

	EggCollision = CreateComponent< GameEngineCollision>(CupHeadCollisionOrder::EnemyWeapon);
	EggCollision->SetColType(ColType::SPHERE2D);
	EggCollision->GetTransform()->SetLocalScale(float4(120, 0));
	//EggCollision->GetTransform()->SetLocalPosition(float4(-25, 0));
}

void Wally1_Egg_Spin::Update(float _DeltaTime)
{
	if (nullptr == EggRender)
	{
		Death();
		return;
	}
	if (false == isDeadAnimation)
	{
		if (ScreenSize.hx() - 5 < abs(GetLevel()->GetMainCamera()->GetTransform()->GetWorldPosition().x - GetTransform()->GetWorldPosition().x))
		{
			GameEngineSound::Play("flying_bird_egg_break_01.wav");
			EggCollision->Death();
			isDeadAnimation = true;
			EggRender->ChangeAnimation("Dead");
			float4 EggPos = GetTransform()->GetWorldPosition();
			EggPos.z = 540;

			std::shared_ptr< Wally1_Egg_Pieces> Piece1 = GetLevel()->CreateActor< Wally1_Egg_Pieces>(CupHeadActorOrder::EnemyWeapon);
			Piece1->GetTransform()->SetLocalPosition(EggPos);
			Piece1->SetDir(EggPiecesPos::Top);

			std::shared_ptr< Wally1_Egg_Pieces> Piece2 = GetLevel()->CreateActor< Wally1_Egg_Pieces>(CupHeadActorOrder::EnemyWeapon);
			Piece2->GetTransform()->SetLocalPosition(EggPos);
			Piece2->SetDir(EggPiecesPos::Mid);

			std::shared_ptr< Wally1_Egg_Pieces> Piece3 = GetLevel()->CreateActor< Wally1_Egg_Pieces>(CupHeadActorOrder::EnemyWeapon);
			Piece3->GetTransform()->SetLocalPosition(EggPos);
			Piece3->SetDir(EggPiecesPos::Bot);
		}
		else
		{
			GetTransform()->AddLocalPosition(float4::Left * _DeltaTime * MoveSpeed);
		}
	}
	else if (true == isDeadAnimation && true == EggRender->IsAnimationEnd())
	{
		Death();
		return;
	}
	CollisionPlayer(EggCollision);

}
