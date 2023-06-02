#include "PrecompileHeader.h"
#include "HIldaBigCloudFX.h"
#include <GameEngineCore\GameEngineSprite.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

HIldaBigCloudFX::HIldaBigCloudFX() 
{
}

HIldaBigCloudFX::~HIldaBigCloudFX() 
{
}


void HIldaBigCloudFX::MakeSprite()
{
	if (nullptr == GameEngineSprite::Find("HildaChangeFX"))
	{

		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources\\Texture\\stage1\\Boss\\Hilda\\HildaBerg\\Normal\\ChangePhase\\FX");

		GameEngineSprite::LoadFolder("HildaChangeFX", NewDir.GetPlusFileName("HildaChangeFX").GetFullPath());
	}
}

void HIldaBigCloudFX::Start()
{
	MakeSprite();
	ExplodeFX = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::EnemyEffect);
	ExplodeFX->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "HildaChangeFX", .FrameInter = 0.1f, .Loop = false, .ScaleToTexture = true });
	ExplodeFX->ChangeAnimation("Idle");
}

void HIldaBigCloudFX::Update(float _DeltaTime)
{
	GetTransform()->AddLocalPosition(float4::Up * 50 * _DeltaTime);
	if (true == ExplodeFX->IsAnimationEnd())
	{
		Death();
		return;
	}
}
