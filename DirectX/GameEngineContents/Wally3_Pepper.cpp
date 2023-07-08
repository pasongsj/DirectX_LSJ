#include "PrecompileHeader.h"
#include "Wally3_Pepper.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
Wally3_Pepper::Wally3_Pepper()
{
}

Wally3_Pepper::~Wally3_Pepper()
{
}
void Wally3_Pepper::MakeSprite()
{

	if (nullptr == GameEngineSprite::Find("Wally3_Pepper_A"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources\\Texture\\stage2\\Boss\\Wally\\Phase 3");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Death\\Pepper\\A").GetFullPath(), "Wally3_Pepper_A");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Death\\Pepper\\B").GetFullPath(), "Wally3_Pepper_B");
	}
}

void Wally3_Pepper::Start()
{
	MakeSprite();
	PepperRender = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::EnemyEffect);
	PepperRender->CreateAnimation({ .AnimationName = "0",.SpriteName = "Wally3_Pepper_A",.FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	PepperRender->CreateAnimation({ .AnimationName = "1",.SpriteName = "Wally3_Pepper_B",.FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	PepperRender->ChangeAnimation(std::to_string(GameEngineRandom::MainRandom.RandomInt(0, 1)));
}

void Wally3_Pepper::Update(float _DeltaTime)
{
	GetTransform()->AddLocalPosition(float4(-1, -1) * _DeltaTime * 200.0f);
	if (nullptr == PepperRender || true == PepperRender->IsAnimationEnd())
	{
		Death();
		return;
	}
}
