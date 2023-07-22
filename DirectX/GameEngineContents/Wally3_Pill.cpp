#include "PrecompileHeader.h"
#include "Wally3_Pill.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Wally3_Pill_Piece.h"

Wally3_Pill::Wally3_Pill()
{
}

Wally3_Pill::~Wally3_Pill()
{
}
void Wally3_Pill::MakeSprite()
{

	if (nullptr == GameEngineSprite::Find("Wally3_Pill_Blue"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources\\Texture\\stage2\\Boss\\Wally\\Phase 3");

		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Birds\\Pills\\Normal\\Whole").GetFullPath(), "Wally3_Pill_Blue");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Birds\\Pills\\Pink\\Whole").GetFullPath(), "Wally3_Pill_Pink");
	}
}

void Wally3_Pill::Start()
{
	//MakeSprite();
	PillRender = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::EnemyWeapon);
	PillRender->CreateAnimation({ .AnimationName = "Blue",.SpriteName = "Wally3_Pill_Blue",.FrameInter = 0.05f,.Loop = true, .ScaleToTexture = true });
	PillRender->CreateAnimation({ .AnimationName = "Pink",.SpriteName = "Wally3_Pill_Pink",.FrameInter = 0.05f,.Loop = true, .ScaleToTexture = true });
	if (true == static_cast<bool>(GameEngineRandom::MainRandom.RandomInt(0, 5)))
	{
		PillRender->ChangeAnimation("Blue");
	}
	else
	{
		PillRender->ChangeAnimation("Pink");
		SetPinkObject();
	}


	PillCollision = CreateComponent<GameEngineCollision>(CupHeadCollisionOrder::EnemyWeapon);
	PillCollision->SetColType(ColType::SPHERE2D);
	PillCollision->GetTransform()->SetLocalScale(float4(30, 30));
}

void Wally3_Pill::Update(float _DeltaTime)
{
	GetTransform()->AddLocalPosition(float4::Up * MoveSpeed * _DeltaTime);
	MoveSpeed -= _DeltaTime * 500;

	if (MoveSpeed < 0)
	{
		float RandomRot = GameEngineRandom::MainRandom.RandomFloat(0, 360);
		float4 PillRenderPos = PillRender->GetTransform()->GetWorldPosition();
		std::shared_ptr< Wally3_Pill_Piece> Piece1 = GetLevel()->CreateActor< Wally3_Pill_Piece>(CupHeadActorOrder::EnemyWeapon);
		Piece1->GetTransform()->SetLocalPosition(PillRenderPos);
		std::shared_ptr< Wally3_Pill_Piece> Piece2 = GetLevel()->CreateActor< Wally3_Pill_Piece>(CupHeadActorOrder::EnemyWeapon);
		Piece2->GetTransform()->SetLocalPosition(PillRenderPos);
		if (true == IsPink())
		{
			Piece1->Setting(RandomRot, 2);
			Piece2->Setting(RandomRot + 180.0f, 3);
		}
		else
		{
			Piece1->Setting(RandomRot, 0);
			Piece2->Setting(RandomRot + 180.0f, 1);
		}
		Death();
		return;
	}
	CollisionPlayer(PillCollision);
}
