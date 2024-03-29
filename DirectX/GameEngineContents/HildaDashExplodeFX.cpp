#include "PrecompileHeader.h"
#include "HildaDashExplodeFX.h"
#include <GameEngineCore\GameEngineSprite.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

HildaDashExplodeFX::HildaDashExplodeFX() 
{
}

HildaDashExplodeFX::~HildaDashExplodeFX() 
{
}

void HildaDashExplodeFX::MakeSprite()
{
	if (nullptr == GameEngineSprite::Find("HildaChangePhaseDashExplode"))
	{

		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources\\Texture\\stage1\\Boss\\Hilda\\HildaBerg\\Normal\\ChangePhase\\FX");

		GameEngineSprite::LoadFolder("HildaChangePhaseDashExplode", NewDir.GetPlusFileName("DashExplodeFX").GetFullPath());
	}
}

void HildaDashExplodeFX::Start()
{
	//MakeSprite();
	ExplodeFX = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::EnemyEffect);
	ExplodeFX->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "HildaChangePhaseDashExplode", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	ExplodeFX->ChangeAnimation("Idle");
}

void HildaDashExplodeFX::Update(float _DeltaTime)
{
	float4 Pos = GetTransform()->GetWorldPosition();

	if (true == ExplodeFX->IsAnimationEnd())
	{
		Death();
		return;
	}
}