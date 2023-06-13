#include "PrecompileHeader.h"
#include "TutorialBackGround.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

TutorialBackGround::TutorialBackGround() 
{
}

TutorialBackGround::~TutorialBackGround() 
{
}
void TutorialBackGround::MakeSprite()
{
	if (nullptr == GameEngineSprite::Find("story1"))
	{

		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources\\Texture\\Tutorial");


		GameEngineSprite::LoadFolder("shmup_tutorial_BG", Dir.GetPlusFileName("shmup_tutorial_BG").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("shmup_tutorial_linework.png").GetFullPath());
	}
}


void TutorialBackGround::Start()
{
	MakeSprite();
	BackGround = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::BackGround);
	BackGround->CreateAnimation({.AnimationName = "BGIdle", .SpriteName = "shmup_tutorial_BG", .FrameInter = 0.05f, .Loop = false, . ScaleToTexture = true});
	BackGround->ChangeAnimation("BGIdle");
	BackGround->GetTransform()->SetLocalPosition(float4(0, 0, 1000));

}
void TutorialBackGround::Update(float _DeltaTime)
{
	if (false == isBGAnimationEnd && true == BackGround->IsAnimationEnd())
	{
		isBGAnimationEnd = true;
		std::shared_ptr<GameEngineSpriteRenderer> shmup_tutorial_linework = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::BackGround);
		shmup_tutorial_linework->SetScaleToTexture("shmup_tutorial_linework.png");
		shmup_tutorial_linework->GetTransform()->SetLocalPosition(float4(0, 0, 900));
	}
}
