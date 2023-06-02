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
	}
}

void HildaDashBackExplodeFX::Start()
{
	MakeSprite();
	ExplodeFX = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::EnemyEffect);
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