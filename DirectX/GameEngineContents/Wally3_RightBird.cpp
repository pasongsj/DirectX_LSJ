#include "PrecompileHeader.h"
#include "Wally3_RightBird.h"
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "ContentsSortRenderer.h"
#include "Wally3_Pill.h"

Wally3_RightBird::Wally3_RightBird()
{
}

Wally3_RightBird::~Wally3_RightBird()
{
}
void Wally3_RightBird::MakeSprite()
{

	if (nullptr == GameEngineSprite::Find("Wally3_RightBird_Idle"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources\\Texture\\stage2\\Boss\\Wally\\Phase 3");

		// Bird
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Birds\\Bird B\\Idle").GetFullPath(), "Wally3_RightBird_Idle");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Birds\\Bird B\\Attack").GetFullPath(), "Wally3_RightBird_Attack");
	}
}

void Wally3_RightBird::Start()
{
	MakeSprite();
	BirdRender = CreateComponent<ContentsSortRenderer>(CupHeadRendererOrder::Enemy);
	BirdRender->CreateAnimation({ .AnimationName = "Idle",.SpriteName = "Wally3_RightBird_Idle",.FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
	BirdRender->CreateAnimation({ .AnimationName = "Attack",.SpriteName = "Wally3_RightBird_Attack",.FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	BirdRender->SetAnimationStartEvent("Attack", 16, [this]
		{
			float4 BirdPos = GetTransform()->GetWorldPosition();
			BirdPos.z = 500;
			std::shared_ptr<GameEngineActor>Pill = GetLevel()->CreateActor<Wally3_Pill>(CupHeadActorOrder::EnemyWeapon);
			Pill->GetTransform()->SetLocalPosition(BirdPos + float4(0, 100));
		});
	BirdRender->ChangeAnimation("Idle");
	BirdRender->SetLocalSortPosition(float4(0, -100), SortRenderer::BOT);

}

void Wally3_RightBird::Update(float _DeltaTime)
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
