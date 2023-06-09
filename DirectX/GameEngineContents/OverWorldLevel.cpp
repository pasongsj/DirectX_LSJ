#include "PrecompileHeader.h"
#include "OverWorldLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "LoadingLevel.h"

#include "OverWorldBack.h"
#include "OverWorldBush.h"
#include "PlayerOverWorldMode.h"
#include "OverWorldInteractObject.h"
//#include "OverWorldToHilda.h"


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
		}
		else
		{
			GameEngineTexture::ReLoad("Overworld_Map.png");
			GameEngineTexture::ReLoad("Overworld_ColMap.png");
			GameEngineTexture::ReLoad("Overworld_Bush_Left.png");
			GameEngineTexture::ReLoad("Overworld_Bush_Right.png");
			GameEngineTexture::ReLoad("interactionIcon.png");
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

			GameEngineSprite::ReLoad(Dir.GetPlusFileName("Diag_Up_Idle").GetFullPath(), "Diag_Up_Idle");
			GameEngineSprite::ReLoad(Dir.GetPlusFileName("Diag_Up_Move").GetFullPath(), "Diag_Up_Move");

			GameEngineSprite::ReLoad(Dir.GetPlusFileName("Down_Idle").GetFullPath(), "Down_Idle");
			GameEngineSprite::ReLoad(Dir.GetPlusFileName("Down_Move").GetFullPath(), "Down_Move");

			GameEngineSprite::ReLoad(Dir.GetPlusFileName("Side_Idle").GetFullPath(), "Side_Idle");
			GameEngineSprite::ReLoad(Dir.GetPlusFileName("Side_Move").GetFullPath(), "Side_Move");

			GameEngineSprite::ReLoad(Dir.GetPlusFileName("Up_Idle").GetFullPath(), "Up_Idle");
			GameEngineSprite::ReLoad(Dir.GetPlusFileName("Up_Move").GetFullPath(), "Up_Move");

			GameEngineSprite::ReLoad(Dir.GetPlusFileName("InterAction_Win").GetFullPath(), "InterAction_Win");
		}
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToDirectory("ContentResources");
			Dir.Move("ContentResources\\Texture\\stage1\\Overworld");
			GameEngineSprite::ReLoad(Dir.GetPlusFileName("blimp").GetFullPath(), "OverWorld_To_Hilda");
			GameEngineSprite::ReLoad(Dir.GetPlusFileName("Shmup_Tutorial").GetFullPath(), "OverWorld_To_Shmup_Tutorial");
			GameEngineSprite::ReLoad(Dir.GetPlusFileName("NPC\\Canteen").GetFullPath(), "OverWorld_NPC_Canteen");
		}
	}

}


void OverWorldLevel::Start()
{
	if (false == GameEngineInput::IsKey("KeyF_Interaction"))
	{
		GameEngineInput::CreateKey("KeyZ_Interaction", 'Z');
	}
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
}

void OverWorldLevel::LevelChangeStart()
{
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });
	MakeSprite();

	CreateActor<OverWorldBack>(CupHeadActorOrder::BackGround);
	CreateActor<OverWorldBush>(CupHeadActorOrder::BackGround);
	//CreateActor<OverWorldToHilda>(CupHeadActorOrder::BackGround);
	MakeInteractObject();

	CreateActor<PlayerOverWorldMode>(CupHeadActorOrder::Player);


	if (false == GameEngineInput::IsKey("ChangeLevel"))
	{
		GameEngineInput::CreateKey("ChangeLevel", VK_F4);
	}
	if (false == GameEngineInput::IsKey("DebugRender"))
	{
		GameEngineInput::CreateKey("DebugRender", VK_F3);
	}
}
void OverWorldLevel::LevelChangeEnd()
{
	if (nullptr != Player::MainPlayer)
	{
		Player::MainPlayer->Death();
		Player::MainPlayer = nullptr;
	}

	AllActorDestroy();

	GameEngineTexture::UnLoad("Overworld_Map.png");
	GameEngineTexture::UnLoad("Overworld_ColMap.png");
	GameEngineTexture::UnLoad("Overworld_Bush_Left.png");
	GameEngineTexture::UnLoad("Overworld_Bush_Right.png");



	GameEngineSprite::UnLoad("Diag_Down_Idle");
	GameEngineSprite::UnLoad("Diag_Down_Move");
					
	GameEngineSprite::UnLoad("Diag_Up_Idle");
	GameEngineSprite::UnLoad("Diag_Up_Move");
					
	GameEngineSprite::UnLoad("Down_Idle");
	GameEngineSprite::UnLoad("Down_Move");
				
	GameEngineSprite::UnLoad("Side_Idle");
	GameEngineSprite::UnLoad("Side_Move");
			
	GameEngineSprite::UnLoad("Up_Idle");
	GameEngineSprite::UnLoad("Up_Move");
				
	GameEngineSprite::UnLoad("InterAction_Win");
	GameEngineSprite::UnLoad("OverWorld_To_Hilda");

	GameEngineSprite::UnLoad("OverWorld_To_Shmup_Tutorial");
	GameEngineSprite::UnLoad("OverWorld_NPC_Canteen");
}


void OverWorldLevel::MakeInteractObject() // 오버월드에 존재하는 대화 상호작용 NPC
{
	std::shared_ptr<OverWorldInteractObject> ToHilda = CreateActor<OverWorldInteractObject>(CupHeadActorOrder::BackGround);
	ToHilda->InteractRender->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "OverWorld_To_Hilda",.FrameInter = 0.1f, .Loop = true, .ScaleToTexture = true });
	ToHilda->InteractRender->ChangeAnimation("Idle");
	ToHilda->GetTransform()->SetLocalPosition(float4{ 3325,-300,500 });
	ToHilda->InteractFucntion = []{
			if (true == GameEngineInput::IsDown("KeyZ_Interaction"))
			{
				LoadingLevel::SetLevel(CupheadLevel::HILDA);
				GameEngineCore::ChangeLevel("LoadingLevel");
				return;
			}};	
	
	std::shared_ptr<OverWorldInteractObject> Canteen = CreateActor<OverWorldInteractObject>(CupHeadActorOrder::BackGround);
	Canteen->InteractRender->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "OverWorld_NPC_Canteen",.FrameInter = 0.1f, .Loop = true, .ScaleToTexture = true });
	Canteen->InteractRender->ChangeAnimation("Idle");
	Canteen->GetTransform()->SetLocalPosition(float4{ 2620,-275,500 });
	//Canteen->InteractFucntion = []{};

	std::shared_ptr<OverWorldInteractObject> Tutorial = CreateActor<OverWorldInteractObject>(CupHeadActorOrder::BackGround);
	Tutorial->InteractRender->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "OverWorld_To_Shmup_Tutorial",.FrameInter = 0.1f, .Loop = true, .ScaleToTexture = true });
	Tutorial->InteractRender->ChangeAnimation("Idle");
	Tutorial->GetTransform()->SetLocalPosition(float4{ 2850,-230,500 });
	Tutorial->InteractFucntion = []{
		if (true == GameEngineInput::IsDown("KeyZ_Interaction"))
		{
			GameEngineCore::ChangeLevel("TutorialLevel");
			return;
		}};

}
