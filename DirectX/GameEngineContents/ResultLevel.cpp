#include "PrecompileHeader.h"
#include "ResultLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "ResultBackGround.h"
#include "ResultBoard.h"
#include "LoadingLevel.h"

//effect
#include "CircleTransEffect.h"
#include "FadeEffect.h"

ResultLevel::ResultLevel() 
{
}

ResultLevel::~ResultLevel() 
{
}

void ResultLevel::MakeSprite()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentResources");
	Dir.Move("ContentResources\\Texture\\Result\\winscreen");
	if (nullptr == GameEngineTexture::Find("winscreen_bg.png"))
	{
		GameEngineTexture::Load(Dir.GetPlusFileName("winscreen_bg.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("winscreen_board.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("winscreen_board_letter.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("winscreen_grey_star_a.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("winscreen_main_star_a.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("winscreen_line.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("Rank\\A_Pluse.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("Rank\\A_Zero.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("Rank\\B_Pluse.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("Rank\\B_Zero.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("Rank\\S_Zero.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("Rank\\question.png").GetFullPath());
	}

	GameEngineSprite::ReLoad(Dir.GetPlusFileName("wincreen_result_title").GetFullPath(), "wincreen_result_title"); // path, name
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("winscreen_cuphead").GetFullPath(), "winscreen_cuphead"); // path, name
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("banner\\banner_NewRecord").GetFullPath(), "banner_NewRecord"); // path, name
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("winscreen_appear_star").GetFullPath(), "winscreen_appear_star"); // path, name
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("winscreen_circle").GetFullPath(), "winscreen_circle"); // path, name

}

void ResultLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("ChangeLevel"))
	{
		LoadingLevel::SetLevel(CupheadLevel::OVERWORLD);
		GameEngineCore::ChangeLevel("LoadingLevel");
	}

	if (0.0f != LevelChangeTimer && GetLiveTime() > LevelChangeTimer)
	{
		if (false == didFadein)
		{
			FadeInEffect->SetFade(CircleTransOption::FadeIn);
			didFadein = true;
		}
		else if (true == FadeInEffect->IsEnd())
		{
			LoadingLevel::SetLevel(CupheadLevel::OVERWORLD);
			GameEngineCore::ChangeLevel("LoadingLevel");
		}
	}
}

void ResultLevel::LevelChangeStart()
{
	ResetLiveTime();
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });

	std::shared_ptr<GameEngineCamera> Camera = GetLevel()->GetCamera(100);
	Camera->SetProjectionType(CameraType::Orthogonal);
	Camera->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });

	if (nullptr == FadeOutEffect)
	{
		FadeOutEffect = GetLastTarget()->CreateEffect< FadeEffect>();
	}
	FadeOutEffect->FadeOut();
	if (nullptr == FadeInEffect)
	{
		FadeInEffect = GetLastTarget()->CreateEffect< CircleTransEffect>();
	}
	//MakeSprite();
	// BG
	CreateActor<ResultBackGround>(CupHeadActorOrder::BackGround);

	// Title
	{
		std::shared_ptr<GameEngineActor> Title = CreateActor<GameEngineActor>(CupHeadActorOrder::UI);
		std::shared_ptr<GameEngineSpriteRenderer> Render = Title->CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::UI);
		Render->CreateAnimation({ .AnimationName = "Res", .SpriteName = "wincreen_result_title",.ScaleToTexture = true });
		Render->ChangeAnimation("Res");
		Title->GetTransform()->SetLocalPosition(float4(0, 280, 900));
	}
	// Cuphead_CH
	{
		std::shared_ptr<GameEngineActor> Character = CreateActor<GameEngineActor>(CupHeadActorOrder::UI);
		std::shared_ptr<GameEngineSpriteRenderer> Render = Character->CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::UI);
		Render->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "winscreen_cuphead",.FrameInter = 0.05f,.ScaleToTexture = true });
		Render->ChangeAnimation("Idle");
		Character->GetTransform()->SetLocalPosition(float4(-300, -50, 900));
	}
	// Board
	ResultBoardActor = CreateActor<ResultBoard>(CupHeadActorOrder::UI);

	if (false == GameEngineInput::IsKey("ChangeLevel"))
	{
		GameEngineInput::CreateKey("ChangeLevel", VK_F4);
	}
	BackGroundSound = GameEngineSound::Play("MUS_VictoryScreen.wav");
}

void ResultLevel::LevelChangeEnd()
{
	FadeInEffect = nullptr;
	FadeOutEffect = nullptr;
	ResultBoardActor->StopSound();
	ResultBoardActor = nullptr;

	LevelChangeTimer = 0.0f;
	didFadein = false;
	AllActorDestroy();

	GameEngineTexture::UnLoad("winscreen_bg.png");
	GameEngineTexture::UnLoad("winscreen_board.png");
	GameEngineTexture::UnLoad("winscreen_board_letter.png");
	GameEngineTexture::UnLoad("winscreen_grey_star_a.png");
	GameEngineTexture::UnLoad("winscreen_main_star_a.png");
	GameEngineTexture::UnLoad("winscreen_line.png");
	GameEngineTexture::UnLoad("A_Pluse.png");
	GameEngineTexture::UnLoad("A_Zero.png");
	GameEngineTexture::UnLoad("B_Pluse.png");
	GameEngineTexture::UnLoad("B_Zero.png");
	GameEngineTexture::UnLoad("S_Zero.png");
	GameEngineTexture::UnLoad("question.png");

	GameEngineSprite::UnLoad("wincreen_result_title");
	GameEngineSprite::UnLoad("winscreen_cuphead");
	GameEngineSprite::UnLoad("banner_NewRecord");
	GameEngineSprite::UnLoad("winscreen_appear_star");

	ResultBoard::ResultTime = 0.0f;
	ResultBoard::ResultHPCount = 3;
	ResultBoard::ResultParryCount = 0;
	ResultBoard::ResultSuperMeter = 0;
	ResultBoard::ResultSkillLevel = 3;

	GetLastTarget()->ReleaseEffect(FadeInEffect);
	GetLastTarget()->ReleaseEffect(FadeOutEffect);
	BackGroundSound.Stop();

}
