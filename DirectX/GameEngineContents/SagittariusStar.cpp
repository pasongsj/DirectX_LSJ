#include "PrecompileHeader.h"
#include "SagittariusStar.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineSprite.h>
#include "Player.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

SagittariusStar::SagittariusStar() 
{
}

SagittariusStar::~SagittariusStar() 
{
}

void SagittariusStar::Start()
{
	MakeSprite();

	StarRender = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::Enemy);
	StarCollision = CreateComponent<GameEngineCollision>(CupHeadCollisionOrder::EnemyWeapon);
	StarRender->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "Sagittarius_Star_Idle",.FrameInter = 0.05f,.Loop = true, .ScaleToTexture = true });
	StarRender->CreateAnimation({ .AnimationName = "Death", .SpriteName = "Sagittarius_Star_Death",.FrameInter = 0.05f,.Loop = false, .ScaleToTexture = true });
	StarRender->ChangeAnimation("Idle");

	StarCollision->SetColType(ColType::SPHERE2D);

	for (int i = 0; i < 3; i++)
	{
		std::shared_ptr<GameEngineSpriteRenderer> trailRender = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::EnemyEffect);
		trailRender->CreateAnimation({ .AnimationName = "trail", .SpriteName = "Sagittarius_Star_Trail",.FrameInter = 0.025f,.Loop = false, .ScaleToTexture = true });
		Trail.push(trailRender);
	}

	StarSpeed = GameEngineRandom::MainRandom.RandomFloat(300, 400);
}

void SagittariusStar::Update(float _DeltaTime)
{
	if (true == isStarDeath)
	{
		if (true == StarRender->IsAnimationEnd() || GetLiveTime() > 60.0f)
		{
			Death();

		}
		return;
	}
	if (true == CollisionPlayer(StarCollision))
	{
		StarCollision->Death();
		isStarDeath = true;
		StarRender->ChangeAnimation("Death");
		return;

	}
	TrailInterval -= _DeltaTime;
	if (TrailInterval < 0)
	{
		std::shared_ptr<GameEngineSpriteRenderer> traillast = Trail.front();
		Trail.pop();
		traillast->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition());
		traillast->ChangeAnimation("trail", true);
		Trail.push(traillast);
		TrailInterval = 0.3f;
	}

	// Collision Scale
	StarCollision->SetRenderScaleToCollision(StarRender);
	// 별의 방향 설정
	CheckDir();
	//이동
	GetTransform()->AddLocalPosition(Dir * StarSpeed * _DeltaTime);


}

void SagittariusStar::CheckDir()
{
	Dir = (Player::MainPlayer->GetTransform()->GetWorldPosition() - GetTransform()->GetWorldPosition()).NormalizeReturn();
}



void SagittariusStar::MakeSprite()
{
	if (nullptr == GameEngineSprite::Find("Sagittarius_Star_Idle"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources\\Texture\\stage1\\Boss\\Hilda\\Sagittarius\\Arrow\\Star");

		GameEngineSprite::LoadFolder("Sagittarius_Star_Idle", Dir.GetPlusFileName("Idle").GetFullPath());
		GameEngineSprite::LoadFolder("Sagittarius_Star_Trail", Dir.GetPlusFileName("Trail\\A").GetFullPath());
		GameEngineSprite::LoadFolder("Sagittarius_Star_Death", Dir.GetPlusFileName("Death").GetFullPath());

	}
}
