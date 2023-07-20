#include "PrecompileHeader.h"
#include "Shop_Pig.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

Shop_Pig::Shop_Pig() 
{
}

Shop_Pig::~Shop_Pig() 
{
}
void Shop_Pig::MakeSprite()
{
	if (nullptr == GameEngineSprite::Find("Pig_Clock"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources\\Texture\\Shop\\Pig");

		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Clock").GetFullPath(), "Shop_Pig_Clock");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("GoodBye").GetFullPath(), "Shop_Pig_GoodBye");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Idle").GetFullPath(), "Shop_Pig_Idle");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("nod").GetFullPath(), "Shop_Pig_nod");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Welcome").GetFullPath(), "Shop_Pig_Welcome");
	}
}

void Shop_Pig::Start()
{
	MakeSprite();
	PigRender = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::BackGround);
	PigRender->CreateAnimation({ .AnimationName = "Idle",.SpriteName = "Shop_Pig_Idle", .FrameInter = 0.05f,.Loop = true,.ScaleToTexture = true });
	PigRender->CreateAnimation({ .AnimationName = "Clock",.SpriteName = "Shop_Pig_Clock", .FrameInter = 0.05f,.Loop = false,.ScaleToTexture = true });
	PigRender->CreateAnimation({ .AnimationName = "GoodBye",.SpriteName = "Shop_Pig_GoodBye", .FrameInter = 0.05f,.Loop = false,.ScaleToTexture = true });
	PigRender->CreateAnimation({ .AnimationName = "nod",.SpriteName = "Shop_Pig_nod", .FrameInter = 0.05f,.Loop = false,.ScaleToTexture = true });
	PigRender->CreateAnimation({ .AnimationName = "Welcome",.SpriteName = "Shop_Pig_Welcome", .FrameInter = 0.05f,.Loop = false,.ScaleToTexture = true });
	PigRender->ChangeAnimation("Idle");
	const float4 PigPos = float4{ 0,130,1000 };
	GetTransform()->SetLocalPosition(PigPos);

}
