#include "PrecompileHeader.h"
#include "Wally3_LeftBird.h"
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "ContentsSortRenderer.h"
#include "Wally3_Pill.h"

Wally3_LeftBird::Wally3_LeftBird() 
{
}

Wally3_LeftBird::~Wally3_LeftBird() 
{
}

void Wally3_LeftBird::MakeSprite()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentResources");
	Dir.Move("ContentResources\\Texture\\stage2\\Boss\\Wally\\Phase 3");


	if (nullptr == GameEngineSprite::Find("Wally3_LeftBird_Idle"))
	{
		// Bird
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Birds\\Bird A\\Idle").GetFullPath(), "Wally3_LeftBird_Idle");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Birds\\Bird A\\Attack").GetFullPath(), "Wally3_LeftBird_Attack");
	}
}

void Wally3_LeftBird::Start()
{
	MakeSprite();
	BirdRender = CreateComponent<ContentsSortRenderer>(CupHeadRendererOrder::Enemy);
	BirdRender->CreateAnimation({ .AnimationName = "Idle",.SpriteName = "Wally3_LeftBird_Idle",.FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
	BirdRender->CreateAnimation({ .AnimationName = "Attack",.SpriteName = "Wally3_LeftBird_Attack",.FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	BirdRender->SetAnimationStartEvent("Attack", 16, [this]
		{
			std::shared_ptr<GameEngineActor>Pill = GetLevel()->CreateActor<Wally3_Pill>(CupHeadActorOrder::EnemyWeapon);
			Pill->GetTransform()->SetLocalPosition(GetTransform()->GetWorldPosition() + float4(0, 100));
		});
	BirdRender->ChangeAnimation("Idle");
	BirdRender->SetLocalSortPosition(float4(0,-100),SortRenderer::BOT);
}

void Wally3_LeftBird::Update(float _DeltaTime)
{
	AttackInterval -= _DeltaTime;
	if (AttackInterval < 0.0f)
	{
		BirdRender->ChangeAnimation("Attack");
		isAttackAnimation = true;
		AttackInterval = 5.0f;
	}
	if (true == isAttackAnimation && BirdRender->IsAnimationEnd())
	{
		BirdRender->ChangeAnimation("Idle");
		isAttackAnimation = false;
	}
}
