#include "PrecompileHeader.h"
#include "TutorialBackGround.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
//#include <GameEngineCore/GameEngineButton.h>
#include "GameContentsButton.h"
#include "LoadingLevel.h"



TutorialBackGround::TutorialBackGround() 
{
}

TutorialBackGround::~TutorialBackGround() 
{
}
void TutorialBackGround::MakeSprite()
{
	if (nullptr == GameEngineSprite::Find("shmup_tutorial_BG"))
	{

		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources\\Texture\\Tutorial");


		GameEngineSprite::LoadFolder("shmup_tutorial_BG", Dir.GetPlusFileName("shmup_tutorial_BG").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("shmup_tutorial_linework.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("tutorial_pink_sphere_1.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("exit.png").GetFullPath());
	}
}


void TutorialBackGround::Start()
{
	//MakeSprite();
	BackGround = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::BackGround);
	BackGround->CreateAnimation({.AnimationName = "BGIdle", .SpriteName = "shmup_tutorial_BG", .FrameInter = 0.05f, .Loop = false, . ScaleToTexture = true});
	BackGround->ChangeAnimation("BGIdle");
	BackGround->GetTransform()->SetLocalPosition(float4(0, 0, 1000));

	if (false == GameEngineInput::IsKey("ESC_Buttion"))
	{
		GameEngineInput::CreateKey("ESC_Buttion", VK_ESCAPE);
	}

}

void TutorialBackGround::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("ESC_Buttion"))
	{
		LoadingLevel::SetLevel(CupheadLevel::OVERWORLD);
		GameEngineCore::ChangeLevel("LoadingLevel");
		return;
	}
	if (false == isBGAnimationEnd && true == BackGround->IsAnimationEnd())
	{
		isBGAnimationEnd = true;
		std::shared_ptr<GameContentsButton> ExitBtn = GetLevel()->CreateActor<GameContentsButton>(CupHeadActorOrder::UI);
		//ExitBtn->SetButtonRender("exit.png", true);
		ExitBtn->SetAllButtionTexture({ .Release = "exit.png" , .ScaleToTexture = true });
		ExitBtn->GetTransform()->SetLocalPosition(float4(438, -288));
		ExitBtn->SetEvent([]
			{
				LoadingLevel::SetLevel(CupheadLevel::OVERWORLD);
				GameEngineCore::ChangeLevel("LoadingLevel");
			});

		std::shared_ptr<GameEngineSpriteRenderer> shmup_tutorial_linework = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::BackGround);
		shmup_tutorial_linework->SetScaleToTexture("shmup_tutorial_linework.png");
		shmup_tutorial_linework->GetTransform()->SetLocalPosition(float4(0, 0, 900));

		std::shared_ptr<GameEngineSpriteRenderer> pink_shpere = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::BackGround);
		pink_shpere->SetScaleToTexture("tutorial_pink_sphere_1.png");
		pink_shpere->GetTransform()->SetLocalPosition(float4(386, -46, 890));


	}
}
