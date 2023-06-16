#include "PrecompileHeader.h"
#include "TitleLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

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

	}
	else
	{
		GameEngineTexture::ReLoad("title_screen_background.png");
		GameEngineTexture::ReLoad("cuphead_secondary_title_screen.png");

	}

	GameEngineSprite::ReLoad(Dir.GetPlusFileName("cuphead_title_screen").GetFullPath(), "cuphead_title_screen"); // path, name


}

void TitleLevel::Update(float _DeltaTime)
{
	if (false == isPressAnyKey &&  true == GameEngineInput::IsAnyKey())
	{
		if (nullptr != CharUI)
		{
			CharUI->Death();
			CharUI = nullptr;
		}
		BackGround->SetScaleToTexture("cuphead_secondary_title_screen.png");
		isPressAnyKey = true;
	}
}



void TitleLevel::LevelChangeStart()
{
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });

	MakeSprite();
	isPressAnyKey = false;

	//BG
	{
		std::shared_ptr<GameEngineActor> BG = CreateActor<GameEngineActor>(CupHeadRendererOrder::BackGround);
		BackGround = BG -> CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::BackGround);
		BackGround->SetScaleToTexture("title_screen_background.png");
		BackGround->GetTransform()->SetLocalPosition(float4(0, 0, 1000));

	}
	// Char
	{
		CharUI = CreateActor<GameEngineActor>(CupHeadActorOrder::UI);
		std::shared_ptr<GameEngineSpriteRenderer> Render = CharUI->CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::UI);
		Render->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "cuphead_title_screen",.FrameInter = 0.05f,.ScaleToTexture = true });
		Render->ChangeAnimation("Idle");
		CharUI->GetTransform()->SetLocalPosition(float4(0, -54, 900));
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
	AllActorDestroy();

	GameEngineTexture::UnLoad("title_screen_background.png");
	GameEngineTexture::UnLoad("cuphead_secondary_title_screen.png");
	GameEngineSprite::UnLoad("cuphead_title_screen");
}