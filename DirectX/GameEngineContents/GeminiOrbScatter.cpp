#include "PrecompileHeader.h"
#include "GeminiOrbScatter.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

GeminiOrbScatter::GeminiOrbScatter() 
{
}

GeminiOrbScatter::~GeminiOrbScatter() 
{
}

void GeminiOrbScatter::MakeSprite()
{
	if (nullptr == GameEngineSprite::Find("Orb_Bullet"))
	{

		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources\\Texture\\stage1\\Boss\\Hilda\\Gemini\\Orb\\Attack");

		GameEngineSprite::LoadFolder("Orb_Bullet", NewDir.GetPlusFileName("BulletStream").GetFullPath());
	}
}

void GeminiOrbScatter::Start()
{
	MakeSprite();
	ScatterRender = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::EnemyWeapon);
	ScatterRender->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "Orb_Bullet", .FrameInter = 0.03f,.Loop = false,.ScaleToTexture = true });
	ScatterRender->ChangeAnimation("Idle");

	ScatterCollsion = CreateComponent<GameEngineCollision>(CupHeadCollisionOrder::EnemyWeapon);
	ScatterCollsion->SetColType(ColType::OBBBOX2D);
}

void GeminiOrbScatter::Update(float _DeltaTime)
{
	ScatterCollsion->GetTransform()->SetLocalScale(ScatterRender->GetTransform()->GetLocalScale().half());
	GetTransform()->AddLocalPosition(Dir*ShootSpeed*_DeltaTime);

	if (true == ScatterRender->IsAnimationEnd())
	{
		Death();
	}

	std::shared_ptr<GameEngineCollision> Col = ScatterCollsion->Collision(CupHeadCollisionOrder::Player, ColType::OBBBOX2D, ColType::SPHERE2D);
	if (nullptr != Col) // 플레이어와 충돌 함
	{
		int a = 0;

	}

	CollisionPlayer(ScatterCollsion);
}


