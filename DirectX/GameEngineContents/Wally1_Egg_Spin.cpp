#include "PrecompileHeader.h"
#include "Wally1_Egg_Spin.h"
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "Wally1_Egg_Pieces.h"
Wally1_Egg_Spin::Wally1_Egg_Spin()
{
}

Wally1_Egg_Spin::~Wally1_Egg_Spin()
{
}
void Wally1_Egg_Spin::MakeSprite()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentResources"); // ContentResources\Texture\stage2\Boss\Wally\Phase 1
	Dir.Move("ContentResources\\Texture\\stage2\\Boss\\Wally\\Phase 1");
	if (nullptr == GameEngineSprite::Find("Wally_Egg_Spin"))
	{
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Egg\\Spin").GetFullPath(), "Wally_Egg_Spin");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Egg\\Dead").GetFullPath(), "Wally_Egg_Dead");
	}
}


void Wally1_Egg_Spin::Start()
{
	MakeSprite();
	EggRender = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::EnemyWeapon);
	EggRender->CreateAnimation({ .AnimationName = "Idle",.SpriteName = "Wally_Egg_Spin",.FrameInter = 0.05f,.Loop = true, .ScaleToTexture = true });
	EggRender->CreateAnimation({ .AnimationName = "Dead",.SpriteName = "Wally_Egg_Dead",.FrameInter = 0.05f,.Loop = false, .ScaleToTexture = true });
	EggRender->ChangeAnimation("Idle");
	ScreenSize = GameEngineWindow::GetScreenSize();
	isDeadAnimation = false;
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
			isDeadAnimation = true;
			EggRender->ChangeAnimation("Dead");

			std::shared_ptr< Wally1_Egg_Pieces> Piece1 = GetLevel()->CreateActor< Wally1_Egg_Pieces>(CupHeadActorOrder::EnemyWeapon);
			Piece1->GetTransform()->SetLocalPosition(GetTransform()->GetWorldPosition());
			Piece1->SetDir(EggPiecesPos::Top);

			std::shared_ptr< Wally1_Egg_Pieces> Piece2 = GetLevel()->CreateActor< Wally1_Egg_Pieces>(CupHeadActorOrder::EnemyWeapon);
			Piece2->GetTransform()->SetLocalPosition(GetTransform()->GetWorldPosition());
			Piece2->SetDir(EggPiecesPos::Mid);

			std::shared_ptr< Wally1_Egg_Pieces> Piece3 = GetLevel()->CreateActor< Wally1_Egg_Pieces>(CupHeadActorOrder::EnemyWeapon);
			Piece3->GetTransform()->SetLocalPosition(GetTransform()->GetWorldPosition());
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
}