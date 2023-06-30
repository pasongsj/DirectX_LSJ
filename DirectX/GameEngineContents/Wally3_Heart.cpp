#include "PrecompileHeader.h"
#include "Wally3_Heart.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

Wally3_Heart::Wally3_Heart()
{
}

Wally3_Heart::~Wally3_Heart()
{
}

void Wally3_Heart::MakeSprite()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentResources");
	Dir.Move("ContentResources\\Texture\\stage2\\Boss\\Wally\\Phase 3");

	if (nullptr == GameEngineSprite::Find("Wally3_Heart"))
	{
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Regurgitate\\Hearts").GetFullPath(), "Wally3_Heart");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Regurgitate\\Mouse_Attack").GetFullPath(), "Wally3_Mouse_Attack");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Regurgitate\\Mouse_Idle").GetFullPath(), "Wally3_Mouse_Idle");
	}
}

void Wally3_Heart::Start()
{
	MakeSprite();
	HeartRender = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::EnemyWeapon);
	HeartRender->CreateAnimation({ .AnimationName = "Idle",.SpriteName = "Wally3_Mouse_Idle",.FrameInter = 0.05f, .Loop = true,.ScaleToTexture = true });
}

void Wally3_Heart::Update(float _DeltaTime)
{
}
