#include "PrecompileHeader.h"
#include "OverWorldLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineUIRenderer.h>

#include "LoadingLevel.h"

#include "OverWorldBack.h"
#include "OverWorldBush.h"
#include "PlayerOverWorldMode.h"
#include "OverWorldInteractObject.h"


#include "OldFilmEffect.h"
#include "CircleTransEffect.h"


OverWorldLevel::OverWorldLevel() 
{
}

OverWorldLevel::~OverWorldLevel() 
{
}

void OverWorldLevel::MakeSprite()
{
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources\\Texture\\stage1\\Overworld");

		// Texture
		if (nullptr == GameEngineTexture::Find("Overworld_Map.png"))
		{
			GameEngineTexture::Load(Dir.GetPlusFileName("Overworld_Map.png").GetFullPath());
			GameEngineTexture::Load(Dir.GetPlusFileName("Overworld_ColMap.png").GetFullPath());
			GameEngineTexture::Load(Dir.GetPlusFileName("Upper\\Bush\\Overworld_Bush_Left.png").GetFullPath());
			GameEngineTexture::Load(Dir.GetPlusFileName("Upper\\Bush\\Overworld_Bush_Right.png").GetFullPath());
			GameEngineTexture::Load(Dir.GetPlusFileName("interactionIcon.png").GetFullPath());
			GameEngineTexture::Load(Dir.GetPlusFileName("title_card_tutorial_background.png").GetFullPath());
			GameEngineTexture::Load(Dir.GetPlusFileName("title_card_blimp_background.png").GetFullPath());
			GameEngineTexture::Load(Dir.GetPlusFileName("title_card_wally_background.png").GetFullPath());
			GameEngineTexture::Load(Dir.GetPlusFileName("title_card_shop_background.png").GetFullPath());
		}
		else
		{
			GameEngineTexture::ReLoad("Overworld_Map.png");
			GameEngineTexture::ReLoad("Overworld_ColMap.png");
			GameEngineTexture::ReLoad("Overworld_Bush_Left.png");
			GameEngineTexture::ReLoad("Overworld_Bush_Right.png");
			GameEngineTexture::ReLoad("interactionIcon.png");
			GameEngineTexture::ReLoad("title_card_tutorial_background.png");
			GameEngineTexture::ReLoad("title_card_blimp_background.png");
			GameEngineTexture::ReLoad("title_card_wally_background.png");
			GameEngineTexture::ReLoad("title_card_shop_background.png");
		}

		// Sprite
	}
	{
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToDirectory("ContentResources");
			Dir.Move("ContentResources\\Texture\\Cuphead_Overworld");


			GameEngineSprite::ReLoad(Dir.GetPlusFileName("Diag_Down_Idle").GetFullPath(), "Diag_Down_Idle");
			GameEngineSprite::ReLoad(Dir.GetPlusFileName("Diag_Down_Move").GetFullPath(), "Diag_Down_Move");

			GameEngineSprite::ReLoad(Dir.GetPlusFileName("Diag_Down_Idle_Left").GetFullPath(), "Diag_Down_Idle_Left");
			GameEngineSprite::ReLoad(Dir.GetPlusFileName("Diag_Down_Move_Left").GetFullPath(), "Diag_Down_Move_Left");

			GameEngineSprite::ReLoad(Dir.GetPlusFileName("Diag_Up_Idle").GetFullPath(), "Diag_Up_Idle");
			GameEngineSprite::ReLoad(Dir.GetPlusFileName("Diag_Up_Move").GetFullPath(), "Diag_Up_Move");

			GameEngineSprite::ReLoad(Dir.GetPlusFileName("Down_Idle").GetFullPath(), "Down_Idle");
			GameEngineSprite::ReLoad(Dir.GetPlusFileName("Down_Move").GetFullPath(), "Down_Move");

			GameEngineSprite::ReLoad(Dir.GetPlusFileName("Side_Idle").GetFullPath(), "Side_Idle");
			GameEngineSprite::ReLoad(Dir.GetPlusFileName("Side_Move").GetFullPath(), "Side_Move");

			GameEngineSprite::ReLoad(Dir.GetPlusFileName("Up_Idle").GetFullPath(), "Up_Idle");
			GameEngineSprite::ReLoad(Dir.GetPlusFileName("Up_Move").GetFullPath(), "Up_Move");

			GameEngineSprite::ReLoad(Dir.GetPlusFileName("Diag_Up_Idle_Left").GetFullPath(), "Diag_Up_Idle_Left");
			GameEngineSprite::ReLoad(Dir.GetPlusFileName("Diag_Up_Move_Left").GetFullPath(), "Diag_Up_Move_Left");

			GameEngineSprite::ReLoad(Dir.GetPlusFileName("Side_Idle_Left").GetFullPath(), "Side_Idle_Left");
			GameEngineSprite::ReLoad(Dir.GetPlusFileName("Side_Move_Left").GetFullPath(), "Side_Move_Left");

			GameEngineSprite::ReLoad(Dir.GetPlusFileName("InterAction_Win").GetFullPath(), "InterAction_Win");
		}
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToDirectory("ContentResources");
			Dir.Move("ContentResources\\Texture\\stage1\\Overworld");
			GameEngineSprite::ReLoad(Dir.GetPlusFileName("blimp").GetFullPath(), "OverWorld_To_Hilda");
			GameEngineSprite::ReLoad(Dir.GetPlusFileName("birdhouse").GetFullPath(), "OverWorld_To_Wally");
			GameEngineSprite::ReLoad(Dir.GetPlusFileName("Shmup_Tutorial").GetFullPath(), "OverWorld_To_Shmup_Tutorial");
			GameEngineSprite::ReLoad(Dir.GetPlusFileName("Shop").GetFullPath(), "OverWorld_To_Shop");
			GameEngineSprite::ReLoad(Dir.GetPlusFileName("NPC\\Canteen").GetFullPath(), "OverWorld_NPC_Canteen");
		}
	}

}


void OverWorldLevel::Start()
{

	if (false == GameEngineInput::IsKey("key_u"))
	{
		GameEngineInput::CreateKey("key_u", 'U');
		GameEngineInput::CreateKey("key_Y", 'Y');
	}
	GetLastTarget()->CreateEffect<OldFilmEffect>();

}

void OverWorldLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("ChangeLevel"))
	{
		LoadingLevel::SetLevel(CupheadLevel::HILDA);
		GameEngineCore::ChangeLevel("LoadingLevel");
	}
	if (true == GameEngineInput::IsDown("DebugRender"))
	{
		GameEngineLevel::IsDebugSwitch();
	}
	
	if (true == GameEngineInput::IsDown("key_y"))
	{
		FadeEffect->SetFade(CircleTransOption::FadeIn);
	}
	if (true == GameEngineInput::IsDown("key_u"))
	{
		FadeEffect->SetFade(CircleTransOption::FadeOut);
	}
	if (true == GameEngineInput::IsDown("ExitGame"))
	{
		FadeEffect->SetFade(CircleTransOption::FadeIn);
		BackGroundSound.SoundFadeOut(1.0f);
		return;
	}
}

void OverWorldLevel::LevelChangeStart()
{
	ResetLiveTime();
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });

	std::shared_ptr<GameEngineCamera> Camera = GetLevel()->GetCamera(100);
	Camera->SetProjectionType(CameraType::Orthogonal);
	Camera->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });

	//MakeSprite();
	if(nullptr == FadeEffect)
	{ 
		FadeEffect = GetLastTarget()->CreateEffect<CircleTransEffect>();
	}
	FadeEffect->SetFade(CircleTransOption::FadeOut);

	CreateActor<OverWorldBack>(CupHeadActorOrder::BackGround);
	CreateActor<OverWorldBush>(CupHeadActorOrder::BackGround);
	//CreateActor<OverWorldToHilda>(CupHeadActorOrder::BackGround);
	MakeInteractObject();

	std::shared_ptr< PlayerOverWorldMode> NewPlayer = CreateActor<PlayerOverWorldMode>(CupHeadActorOrder::Player);
	if (false == LastPlayerPos.IsZero())
	{
		NewPlayer->GetTransform()->SetLocalPosition(LastPlayerPos);
		float4 CamPos = LastPlayerPos;
		CamPos.z = -1000;
		CamPos.y = CamPos.y > -375 ? -375 : CamPos.y;
		GetMainCamera()->GetTransform()->SetLocalPosition(CamPos);
	}

	if (false == GameEngineInput::IsKey("ChangeLevel"))
	{
		GameEngineInput::CreateKey("ChangeLevel", VK_F4);
	}
	if (false == GameEngineInput::IsKey("DebugRender"))
	{
		GameEngineInput::CreateKey("DebugRender", VK_F3);
	}
	if (false == GameEngineInput::IsKey("ExitGame"))
	{
		GameEngineInput::CreateKey("ExitGame", VK_F9);
	}
	BackGroundSound = GameEngineSound::Play("bgm_map_world_1.wav");
}
void OverWorldLevel::LevelChangeEnd()
{
	if (nullptr != Player::MainPlayer)
	{
		LastPlayerPos = Player::MainPlayer->GetTransform()->GetWorldPosition();
		Player::MainPlayer->Death();
		Player::MainPlayer = nullptr;
	}

	AllActorDestroy();

	GameEngineTexture::UnLoad("Overworld_Map.png");
	GameEngineTexture::UnLoad("Overworld_ColMap.png");
	GameEngineTexture::UnLoad("Overworld_Bush_Left.png");
	GameEngineTexture::UnLoad("Overworld_Bush_Right.png");
	GameEngineTexture::UnLoad("interactionIcon.png");



	GameEngineSprite::UnLoad("Diag_Down_Idle");
	GameEngineSprite::UnLoad("Diag_Down_Move");	

	GameEngineSprite::UnLoad("Diag_Down_Idle_Left");
	GameEngineSprite::UnLoad("Diag_Down_Move_Left");
					
	GameEngineSprite::UnLoad("Diag_Up_Idle");
	GameEngineSprite::UnLoad("Diag_Up_Move");	

	GameEngineSprite::UnLoad("Diag_Up_Idle_Left");
	GameEngineSprite::UnLoad("Diag_Up_Move_Left");
					
	GameEngineSprite::UnLoad("Down_Idle");
	GameEngineSprite::UnLoad("Down_Move");
				
	GameEngineSprite::UnLoad("Side_Idle");
	GameEngineSprite::UnLoad("Side_Move");

	GameEngineSprite::UnLoad("Side_Idle_Left");
	GameEngineSprite::UnLoad("Side_Move_Left");
			
	GameEngineSprite::UnLoad("Up_Idle");
	GameEngineSprite::UnLoad("Up_Move");
				
	GameEngineSprite::UnLoad("InterAction_Win");
	GameEngineSprite::UnLoad("OverWorldDust");

	GameEngineSprite::UnLoad("OverWorld_To_Hilda");
	GameEngineSprite::UnLoad("OverWorld_To_Wally");
	GameEngineSprite::UnLoad("OverWorld_To_Shop");

	GameEngineSprite::UnLoad("OverWorld_To_Shmup_Tutorial");
	GameEngineSprite::UnLoad("OverWorld_NPC_Canteen");

	//--
	GameEngineTexture::UnLoad("title_card_tutorial_background.png");
	GameEngineTexture::UnLoad("title_card_blimp_background.png");
	GameEngineTexture::UnLoad("title_card_wally_background.png");
	BackGroundSound.Stop();
	BackGroundSound.SetLoop(-1);
}

void OverWorldLevel::MakeInteractObject() // 오버월드에 존재하는 대화 상호작용 NPC
{

	std::shared_ptr<OverWorldInteractObject> ToHilda = CreateActor<OverWorldInteractObject>(CupHeadActorOrder::BackGround);
	ToHilda->InteractRender->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "OverWorld_To_Hilda",.FrameInter = 0.1f, .Loop = true, .ScaleToTexture = true });
	ToHilda->InteractRender->ChangeAnimation("Idle");
	ToHilda->GetTransform()->SetLocalPosition(float4{ 3325,-300,500 });
	ToHilda->TitleCard->SetScaleToTexture("title_card_blimp_background.png");
	ToHilda->EnterFucntion = [] {
		LoadingLevel::SetLevel(CupheadLevel::HILDA);
		GameEngineCore::ChangeLevel("LoadingLevel");
	};

	std::shared_ptr<OverWorldInteractObject> Canteen = CreateActor<OverWorldInteractObject>(CupHeadActorOrder::BackGround);
	Canteen->InteractRender->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "OverWorld_NPC_Canteen",.FrameInter = 0.1f, .Loop = true, .ScaleToTexture = true });
	Canteen->InteractRender->ChangeAnimation("Idle");
	Canteen->GetTransform()->SetLocalPosition(float4{ 2620,-275,500 });

	std::shared_ptr<OverWorldInteractObject> Tutorial = CreateActor<OverWorldInteractObject>(CupHeadActorOrder::BackGround);
	Tutorial->InteractRender->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "OverWorld_To_Shmup_Tutorial",.FrameInter = 0.1f, .Loop = true, .ScaleToTexture = true });
	Tutorial->InteractRender->ChangeAnimation("Idle");
	Tutorial->GetTransform()->SetLocalPosition(float4{ 2850,-230,500 });
	Tutorial->TitleCard->SetScaleToTexture("title_card_tutorial_background.png");
	Tutorial->EnterFucntion = [] {
		LoadingLevel::SetLevel(CupheadLevel::TUTORIAL);
		GameEngineCore::ChangeLevel("LoadingLevel");
	};

	std::shared_ptr< OverWorldInteractObject> Shop = CreateActor< OverWorldInteractObject>(CupHeadActorOrder::BackGround);
	Shop->InteractRender->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "OverWorld_To_Shop",.FrameInter = 0.1f, .Loop = true, .ScaleToTexture = true });
	Shop->InteractRender->ChangeAnimation("Idle");
	Shop->GetTransform()->SetLocalPosition(float4{ 2275,-1075,500 });
	Shop->TitleCard->SetScaleToTexture("title_card_shop_background.png");

	Shop->EnterFucntion = [] {
		LoadingLevel::SetLevel(CupheadLevel::SHOP);
		GameEngineCore::ChangeLevel("LoadingLevel");
	};


	std::shared_ptr<OverWorldInteractObject> ToWally = CreateActor<OverWorldInteractObject>(CupHeadActorOrder::BackGround);
	ToWally->InteractRender->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "OverWorld_To_Wally",.FrameInter = 0.1f, .Loop = true, .ScaleToTexture = true });
	ToWally->InteractRender->ChangeAnimation("Idle");
	ToWally->GetTransform()->SetLocalPosition(float4{ 3055,-1180,500 });
	ToWally->TitleCard->SetScaleToTexture("title_card_wally_background.png");
	ToWally->EnterFucntion = [] {
		LoadingLevel::SetLevel(CupheadLevel::WALLY);
		GameEngineCore::ChangeLevel("LoadingLevel");
	};
}
