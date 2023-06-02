#include "PrecompileHeader.h"
#include "HildaDashBackExplodeFX.h"
#include <GameEngineCore\GameEngineSprite.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

HildaDashBackExplodeFX::HildaDashBackExplodeFX() 
{
}

HildaDashBackExplodeFX::~HildaDashBackExplodeFX() 
{
}

void HildaDashBackExplodeFX::MakeSprite()
{
	if (nullptr == GameEngineSprite::Find("HildaChangePhaseDashBackExplode"))
	{

		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources\\Texture\\stage1\\Boss\\Hilda\\HildaBerg\\Normal\\ChangePhase\\FX");

		GameEngineSprite::LoadFolder("HildaChangePhaseDashBackExplode", NewDir.GetPlusFileName("DashBackExplodeFX").GetFullPath());
		GameEngineSprite::LoadFolder("HildaChangeFX", NewDir.GetPlusFileName("HildaChangeFX").GetFullPath());
	}
}

void HildaDashBackExplodeFX::Start()
{
	MakeSprite();
	ExplodeFX = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::PlayerEffect);
	ExplodeFX->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "HildaChangePhaseDashBackExplode", .FrameInter = 0.1f, .Loop = false, .ScaleToTexture = true });
	ExplodeFX->CreateAnimation({ .AnimationName = "Last", .SpriteName = "HildaChangeFX", .FrameInter = 0.1f, .Loop = false, .ScaleToTexture = true });
	ExplodeFX->ChangeAnimation("Idle");
}

void HildaDashBackExplodeFX::Update(float _DeltaTime)
{
	if (true == ExplodeFX->IsAnimationEnd())
	{
		Death();
		return;
	}
}

void HildaDashBackExplodeFX::LasCloudtFX()
{
	ExplodeFX->ChangeAnimation("Last");
}