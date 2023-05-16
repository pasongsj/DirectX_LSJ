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
	ScatterRender = CreateComponent<GameEngineSpriteRenderer>();
	ScatterRender->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "Orb_Bullet", .FrameInter = 0.05f,.Loop = false,.ScaleToTexture = true });
	ScatterRender->ChangeAnimation("Idle");

	ScatterCollsion = CreateComponent<GameEngineCollision>(CupHeadCollisionOrder::Enemy);
}

void GeminiOrbScatter::Update(float _DeltaTime)
{
	GetTransform()->AddLocalPosition(Dir*ShootSpeed*_DeltaTime);

	if (true == ScatterRender->IsAnimationEnd())
	{
		Death();
	}
}


