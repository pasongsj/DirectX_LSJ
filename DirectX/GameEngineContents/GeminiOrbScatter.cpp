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
	GetTransform()->SetLocalPosition(float4(0, 0, 600));
}

void GeminiOrbScatter::Start()
{
	//MakeSprite();
	ScatterRender = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::EnemyWeapon);
	ScatterRender->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "Orb_Bullet", .FrameInter = 0.03f,.Loop = false,.ScaleToTexture = true });
	ScatterRender->ChangeAnimation("Idle");

	ScatterCollsion = CreateComponent<GameEngineCollision>(CupHeadCollisionOrder::EnemyWeapon);
	ScatterCollsion->SetColType(ColType::OBBBOX2D);
}

void GeminiOrbScatter::Update(float _DeltaTime)
{
	if (true == ScatterRender->IsAnimationEnd())
	{
		Death();
		return;
	}
	ScatterCollsion->GetTransform()->SetTransformData(ScatterRender->GetTransform()->GetTransDataRef());
	GetTransform()->AddLocalPosition(Dir*ShootSpeed*_DeltaTime);
	// 플레이어와 충돌 함
	CollisionPlayer(ScatterCollsion);
}


