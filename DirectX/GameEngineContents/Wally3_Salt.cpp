#include "PrecompileHeader.h"
#include "Wally3_Salt.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

Wally3_Salt::Wally3_Salt()
{
}

Wally3_Salt::~Wally3_Salt()
{
}
void Wally3_Salt::MakeSprtie()
{
	if (nullptr == GameEngineSprite::Find("Wally3_Salt_A"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources\\Texture\\stage2\\Boss\\Wally\\Phase 3");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Death\\Salt\\A").GetFullPath(), "Wally3_Salt_A");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Death\\Salt\\B").GetFullPath(), "Wally3_Salt_B");
	}
}


void Wally3_Salt::Start()
{
	//MakeSprtie();
	SaltRender = CreateComponent< GameEngineSpriteRenderer>(CupHeadRendererOrder::EnemyEffect);
	SaltRender->CreateAnimation({ .AnimationName = "0",.SpriteName = "Wally3_Salt_A",.FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	SaltRender->CreateAnimation({ .AnimationName = "1",.SpriteName = "Wally3_Salt_B",.FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	SaltRender->ChangeAnimation(std::to_string(GameEngineRandom::MainRandom.RandomInt(0, 1)));
}

void Wally3_Salt::Update(float _DeltaTime)
{
	GetTransform()->AddLocalPosition(float4(1, -1) * _DeltaTime * 200.0f);
	if (nullptr == SaltRender || true == SaltRender->IsAnimationEnd())
	{
		Death();
		return;
	}
}
