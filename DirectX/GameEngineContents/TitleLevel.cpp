#include "PrecompileHeader.h"
#include "TitleLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "LoadingLevel.h"

#include "GameContentsButton.h"
#include "OldFilmEffect.h"
#include "CircleTransEffect.h"

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
		GameEngineTexture::ReLoad(Dir.GetPlusFileName("title_screen_background.png").GetFullPath());
		GameEngineTexture::ReLoad(Dir.GetPlusFileName("cuphead_secondary_title_screen.png").GetFullPath());
		GameEngineTexture::ReLoad(Dir.GetPlusFileName("PressAnyButton.png").GetFullPath());
		GameEngineTexture::ReLoad(Dir.GetPlusFileName("Title_StartButton.png").GetFullPath());
		GameEngineTexture::ReLoad(Dir.GetPlusFileName("Title_OptionButton.png").GetFullPath());
		GameEngineTexture::ReLoad(Dir.GetPlusFileName("Title_ExitButton.png").GetFullPath());
		GameEngineTexture::ReLoad(Dir.GetPlusFileName("Title_StartButton_Hover.png").GetFullPath());
		GameEngineTexture::ReLoad(Dir.GetPlusFileName("Title_OptionButton_Hover.png").GetFullPath());
		GameEngineTexture::ReLoad(Dir.GetPlusFileName("Title_ExitButton_Hover.png").GetFullPath());

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
	if (true == isChangeLevel && true == CircleFadeOut->IsEnd())
	{
		LoadingLevel::SetLevel(CupheadLevel::STORY);
		GameEngineCore::ChangeLevel("LoadingLevel");
		return;
	}
	if (true == TitleSound.IsValid())
	{
		bool isPlayingResult;
		TitleSound.isPlaying(&isPlayingResult);
		if (false == isChangeLevel && false == isPlayingResult && false == LoopSoundPlay)
		{
			TitleSound.Stop();
			GameEngineSound::Play("Don't Deal with the Devil (Instrumental).mp3").SetLoop(-1);
			LoopSoundPlay = true;
		}
	}
	if (true == isLogoDone && true == isPressAnyKey && true == isButtonTime)
	{
		SetHoverButtion();

		if (true == GameEngineInput::IsDown("ChangeLevel"))
		{
			if (true == TitleSound.IsValid())
			{
				TitleSound.Stop();
			}
			LoadingLevel::SetLevel(CupheadLevel::STORY);
			GameEngineCore::ChangeLevel("LoadingLevel");
		}
		return;
	}
	if (false == isLogoDone && true == BackGround->IsAnimationEnd()) // Title_Logo
	{
		BackGround->SetScaleToTexture("title_screen_background.png");
		BackGround->GetTransform()->SetLocalPosition(float4(0, 0, 1000));
		BtnUI = CreateActor<GameEngineActor>(CupHeadActorOrder::UI);
		std::shared_ptr<GameEngineSpriteRenderer> Rend = BtnUI->CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::UI);
		Rend->SetScaleToTexture("PressAnyButton.png");
		Rend->GetTransform()->SetLocalPosition(float4(0, -300));
		isLogoDone = true;
		TitleSound = GameEngineSound::Play("Don't Deal with the Devil.mp3");

	}
	if (true == isLogoDone && false == isPressAnyKey && true == GameEngineInput::IsAnyKey()) // Title Cuphead Animation
	{
		if (false == isPressAnyKey && true == GameEngineInput::IsAnyKey())
		{
			CircleFadeOut = GetLastTarget()->CreateEffect< CircleTransEffect>();
			CircleFadeOut->SetFade(CircleTransOption::FadeIn);
			isPressAnyKey = true;
		}
	}
	if (true == isPressAnyKey && true == CircleFadeOut->IsEnd())
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
		isButtonTime = true;
		GetLastTarget()->ReleaseEffect(CircleFadeOut);
		
	}
}

void TitleLevel::SetHoverButtion()
{
	if (true == GameEngineInput::IsDown("Up_Buttion"))
	{
		if (nullptr == HoverButton)
		{
			HoverButton = StartButton;
			HoverButton->SetHover();
			GameEngineSound::Play("Menu_Move.wav");
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
		GameEngineSound::Play("Menu_Move.wav");

	}
	if (true == GameEngineInput::IsDown("Down_Buttion"))
	{
		if (nullptr == HoverButton)
		{
			HoverButton = StartButton;
			HoverButton->SetHover();
			GameEngineSound::Play("Menu_Move.wav");

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
		GameEngineSound::Play("Menu_Move.wav");


	}

}



void TitleLevel::LevelChangeStart()
{
	ResetLiveTime();
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });

	{ // sound Loading
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources\\Sound\\Title");;
		std::vector<GameEngineFile> AllFiles = Dir.GetAllFile({ ".wav",".mp3" });
		for (GameEngineFile _File : AllFiles)
		{
			GameEngineSound::Load(_File.GetFullPath());
		}
	}

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
				if (true == TitleSound.IsValid())
				{
					TitleSound.Stop();
				}
				CircleFadeOut = GetLastTarget()->CreateEffect< CircleTransEffect>();
				CircleFadeOut->SetFade(CircleTransOption::FadeIn);
				isChangeLevel = true;
				GameEngineSound::Play("Menu_Category_Select.wav");
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
		ExitButton->SetEvent([]
			{
				GameEngineWindow::AppOff();
			});
		ExitButton->Off();
	}
	GameEngineSound::Play("MDHR_LOGO_STING.wav");

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
	if (nullptr != StartButton)
	{
		StartButton = nullptr;
		OptionsButton = nullptr;
		ExitButton = nullptr;
		HoverButton = nullptr;
	}
	CircleFadeOut = nullptr;
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
	TitleSound.Stop();
}