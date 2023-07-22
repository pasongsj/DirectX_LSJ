#include "PrecompileHeader.h"
#include "TitleLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "LoadingLevel.h"

#include "GameContentsButton.h"
#include "OldFilmEffect.h"

TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::MakeSprite()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentResources");
	Dir.Move("ContentResources\\Texture\\Title");
	if (nullptr == GameEngineTexture::Find("title_screen_background.png"))
	{
		GameEngineTexture::Load(Dir.GetPlusFileName("title_screen_background.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("cuphead_secondary_title_screen.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("PressAnyButton.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("Title_StartButton.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("Title_OptionButton.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("Title_ExitButton.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("Title_StartButton_Hover.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("Title_OptionButton_Hover.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("Title_ExitButton_Hover.png").GetFullPath());

	}
	else
	{
		GameEngineTexture::ReLoad("title_screen_background.png");
		GameEngineTexture::ReLoad("cuphead_secondary_title_screen.png");
		GameEngineTexture::ReLoad("PressAnyButton.png");
		GameEngineTexture::ReLoad("Title_StartButton.png");
		GameEngineTexture::ReLoad("Title_OptionButton.png");
		GameEngineTexture::ReLoad("Title_ExitButton.png");
		GameEngineTexture::ReLoad("Title_StartButton_Hover.png");
		GameEngineTexture::ReLoad("Title_OptionButton_Hover.png");
		GameEngineTexture::ReLoad("Title_ExitButton_Hover.png");

	}

	GameEngineSprite::ReLoad(Dir.GetPlusFileName("cuphead_title_screen").GetFullPath(), "cuphead_title_screen"); // path, name
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Title_Logo").GetFullPath(), "Title_Logo"); // path, name


}

void TitleLevel::Start()
{
	GetLastTarget()->CreateEffect<OldFilmEffect>();
}


void TitleLevel::Update(float _DeltaTime)
{
	if (false == isLogoDone && true == BackGround->IsAnimationEnd()) // Title_Logo
	{
		BackGround->SetScaleToTexture("title_screen_background.png");
		BackGround->GetTransform()->SetLocalPosition(float4(0, 0, 1000));
		BtnUI = CreateActor<GameEngineActor>(CupHeadActorOrder::UI);
		std::shared_ptr<GameEngineSpriteRenderer> Rend = BtnUI->CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::UI);
		Rend->SetScaleToTexture("PressAnyButton.png");
		Rend->GetTransform()->SetLocalPosition(float4(0, -300));
		isLogoDone = true;
	}
	if (true == isLogoDone && false == isPressAnyKey && true == GameEngineInput::IsAnyKey()) // Title Cuphead Animation
	{
		if (nullptr != CharUI)
		{
			CharUI->Death();
			BtnUI->Death();
			CharUI = nullptr;
			BtnUI = nullptr;
		}
		BackGround->SetScaleToTexture("cuphead_secondary_title_screen.png");
		isPressAnyKey = true;

		StartButton->On();
		OptionsButton->On();
		ExitButton->On();
	}
	if (true == isLogoDone && true == isPressAnyKey)
	{
		SetHoverButtion();

		if (true == GameEngineInput::IsDown("ChangeLevel"))
		{
			LoadingLevel::SetLevel(CupheadLevel::STORY);
			GameEngineCore::ChangeLevel("LoadingLevel");
		}
	}
}
// start
// options
// exit
void TitleLevel::SetHoverButtion()
{
	if (true == GameEngineInput::IsDown("Up_Buttion"))
	{
		if (nullptr == HoverButton)
		{
			HoverButton = StartButton;
			HoverButton->SetHover();
			return;
		}
		HoverButton->SetRelease();
		std::string_view NowBtn = HoverButton->GetName();
		if (NowBtn == "StartButton")
		{
			HoverButton = ExitButton;
		}
		else if (NowBtn == "OptionsButton")
		{
			HoverButton = StartButton;
		}
		else // NowBtn == "ExitButtion
		{
			HoverButton = OptionsButton;
		}
		HoverButton->SetHover();
	}
	if (true == GameEngineInput::IsDown("Down_Buttion"))
	{
		if (nullptr == HoverButton)
		{
			HoverButton = StartButton;
			HoverButton->SetHover();
			return;
		}
		HoverButton->SetRelease();
		std::string_view NowBtn = HoverButton->GetName();
		if (NowBtn == "StartButton")
		{
			HoverButton = OptionsButton;
		}
		else if (NowBtn == "OptionsButton")
		{
			HoverButton = ExitButton;
		}
		else // NowBtn == "ExitButtion
		{
			HoverButton = StartButton;
		}
		HoverButton->SetHover();

	}

}



void TitleLevel::LevelChangeStart()
{
	ResetLiveTime();
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });

	// button
	{
		if (false == GameEngineInput::IsKey("ChangeLevel"))
		{
			GameEngineInput::CreateKey("ChangeLevel", VK_F4);
		}
		if (false == GameEngineInput::IsKey("Up_Buttion"))
		{
			GameEngineInput::CreateKey("Up_Buttion", VK_UP);
		}
		if (false == GameEngineInput::IsKey("Down_Buttion"))
		{
			GameEngineInput::CreateKey("Down_Buttion", VK_DOWN);
		}
	}

	MakeSprite();
	isLogoDone = false;
	isPressAnyKey = false;

	//BG
	{
		std::shared_ptr<GameEngineActor> BG = CreateActor<GameEngineActor>(CupHeadRendererOrder::BackGround);
		BackGround = BG->CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::BackGround);
		BackGround->CreateAnimation({ .AnimationName = "Logo", .SpriteName = "Title_Logo", .FrameInter = 0.05f, .Loop = false });
		BackGround->GetTransform()->SetLocalScale(float4(1280, 720, 1));
		BackGround->ChangeAnimation("Logo");

	}
	// Char
	{
		CharUI = CreateActor<GameEngineActor>(CupHeadActorOrder::UI);
		std::shared_ptr<GameEngineSpriteRenderer> Render = CharUI->CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::UI);
		Render->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "cuphead_title_screen",.FrameInter = 0.05f,.ScaleToTexture = true });
		Render->ChangeAnimation("Idle");
		CharUI->GetTransform()->SetLocalPosition(float4(0, -54, 900));
	}


	// Buttion
	{
		StartButton = CreateActor<GameContentsButton>(CupHeadRendererOrder::UI);
		StartButton->SetAllButtionTexture({ "Title_StartButton.png" ,"Title_StartButton_Hover.png", "",true });
		StartButton->GetTransform()->SetLocalPosition(float4{ 0,100 });
		StartButton->SetName("StartButton");
		StartButton->SetEvent({[this]
			{
				LoadingLevel::SetLevel(CupheadLevel::STORY);
				GameEngineCore::ChangeLevel("LoadingLevel");
			}});
		StartButton->Off();

		OptionsButton = CreateActor<GameContentsButton>(CupHeadRendererOrder::UI);
		OptionsButton->SetAllButtionTexture({ "Title_OptionButton.png" ,"Title_OptionButton_Hover.png", "",true });
		OptionsButton->GetTransform()->SetLocalPosition(float4{ 0,50 });
		OptionsButton->SetName("OptionsButton");
		OptionsButton->Off();


		ExitButton = CreateActor<GameContentsButton>(CupHeadRendererOrder::UI);
		ExitButton->SetAllButtionTexture({ "Title_ExitButton.png" ,"Title_ExitButton_Hover.png", "",true });
		ExitButton->GetTransform()->SetLocalPosition(float4{ 0,0 });
		ExitButton->SetName("ExitButton");
		ExitButton->Off();
	}


}

void TitleLevel::LevelChangeEnd()
{
	if (nullptr != BackGround)
	{
		BackGround = nullptr;
	}
	if (nullptr != CharUI)
	{
		CharUI = nullptr;
	}
	if (nullptr != BtnUI)
	{
		BtnUI = nullptr;
	}
	AllActorDestroy();

	GameEngineTexture::UnLoad("title_screen_background.png");
	GameEngineTexture::UnLoad("cuphead_secondary_title_screen.png");
	GameEngineTexture::UnLoad("PressAnyButton.png");
	GameEngineTexture::UnLoad("Title_StartButton.png");
	GameEngineTexture::UnLoad("Title_OptionButton.png");
	GameEngineTexture::UnLoad("Title_ExitButton.png");
	GameEngineTexture::UnLoad("Title_StartButton_Hover.png");
	GameEngineTexture::UnLoad("Title_OptionButton_Hover.png");
	GameEngineTexture::UnLoad("Title_ExitButton_Hover.png");


	GameEngineSprite::UnLoad("cuphead_title_screen");
	GameEngineSprite::UnLoad("Title_Logo");
}