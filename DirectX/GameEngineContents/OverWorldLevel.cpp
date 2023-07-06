#include "PrecompileHeader.h"
#include "OverWorldLevel.h"

#include <GameEngineCore/GameEngineSprite.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include "LoadingLevel.h"

#include "OverWorldBack.h"
#include "OverWorldBush.h"
#include "PlayerOverWorldMode.h"


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
		}
		else
		{
			GameEngineTexture::ReLoad("Overworld_Map.png");
			GameEngineTexture::ReLoad("Overworld_ColMap.png");
			GameEngineTexture::ReLoad("Overworld_Bush_Left.png");
			GameEngineTexture::ReLoad("Overworld_Bush_Right.png");
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
			GameEngineSprite::ReLoad(Dir.GetPlusFileName("blimp").GetFullPath(), "To_Hilda_OverWorld");
		}
	}

}


void OverWorldLevel::Start()
{

}

void OverWorldLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("ChangeLevel"))
	{
		LoadingLevel::SetLevel(CupheadLevel::HILDA);
		GameEngineCore::ChangeLevel("LoadingLevel");
	}
}

void OverWorldLevel::LevelChangeStart()
{
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });
	MakeSprite();

	CreateActor<OverWorldBack>(CupHeadActorOrder::BackGround);
	CreateActor<OverWorldBush>(CupHeadActorOrder::BackGround);

	CreateActor<PlayerOverWorldMode>(CupHeadActorOrder::Player);


	if (false == GameEngineInput::IsKey("ChangeLevel"))
	{
		GameEngineInput::CreateKey("ChangeLevel", VK_F4);
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
	GameEngineSprite::UnLoad("To_Hilda_OverWorld");
}