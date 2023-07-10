#include "PrecompileHeader.h"
#include "PlayerUI.h"
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineUIRenderer.h>

#include "GameContentsUIRenderer.h"

#include "Player.h"

PlayerUI::PlayerUI() 
{
}

PlayerUI::~PlayerUI() 
{
}
void PlayerUI::MakeSprite()
{
	if (nullptr == GameEngineSprite::Find("CharacterRotateCard"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources\\Texture\\PlayerUI");


		GameEngineSprite::LoadFolder("CharacterRotateCard", NewDir.GetPlusFileName("RotateCard").GetFullPath().c_str());
		GameEngineSprite::LoadFolder("CharacterBackCard", NewDir.GetPlusFileName("BackCard").GetFullPath().c_str());
		GameEngineSprite::LoadFolder("CharacterFrontCard", NewDir.GetPlusFileName("FrontCard").GetFullPath().c_str());
		GameEngineSprite::LoadFolder("CharacterFlipCard", NewDir.GetPlusFileName("FlipCard").GetFullPath().c_str());
		GameEngineSprite::LoadFolder("Character1HPFlash", NewDir.GetPlusFileName("HpFlash").GetFullPath().c_str());
	}
	if (nullptr == GameEngineTexture::Find("hud_hp_1.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources\\Texture\\PlayerUI\\HPBar");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });
		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}

}


void PlayerUI::Start()
{
	MakeSprite();
	// camera
	std::shared_ptr<GameEngineCamera> Camera = GetLevel()->GetCamera(100);
	Camera->SetProjectionType(CameraType::Orthogonal);
	Camera->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });
	float4 ScreenSize = GameEngineWindow::GetScreenSize();

	// hp Render
	std::shared_ptr<GameEngineTexture> hp0 = GameEngineTexture::Find("hud_hp_dead.png");
	if (nullptr == hp0)
	{
		MsgAssert("UI 텍스쳐가 로드되지 않았습니다.");
	}
	HPTexture.insert(std::make_pair(0, hp0));
	for (int i = 1; i <= 9; ++i)
	{
		std::string PNGName = "hud_hp_" + std::to_string(i)+".png";
		std::shared_ptr<GameEngineTexture> HpRender = GameEngineTexture::Find(PNGName);
		if (nullptr == HpRender)
		{
			MsgAssert("UI 텍스쳐가 로드되지 않았습니다.");
		}
		HPTexture.insert(std::make_pair(i, HpRender));
	}

	{
		// HPBar
		HPRender = CreateComponent<GameEngineUIRenderer>(CupHeadRendererOrder::UI);
		HPRender->SetScaleToTexture(HPTexture[3]);
		HPRender->GetTransform()->SetLocalPosition(-ScreenSize.half() + float4(20, 20) + HPRender->GetTransform()->GetLocalScale().half());
	}





	// card Render
	float4 UIPos = -ScreenSize.half();
	UIPos += float4(120, 20);
	for (int i = 0; i < 5; i++)
	{
		std::shared_ptr<GameContentsUIRenderer> tmp = CreateComponent< GameContentsUIRenderer>(CupHeadRendererOrder::UI);
		tmp->CreateAnimation({ .AnimationName = "RotateCard",  .SpriteName = "CharacterRotateCard", .FrameInter = 0.05f, .Loop = true , .ScaleToTexture = true });
		tmp->CreateAnimation({ .AnimationName = "BackCard",  .SpriteName = "CharacterBackCard" , .FrameInter = 0.05f, .Loop = true  , .ScaleToTexture = true });
		tmp->CreateAnimation({ .AnimationName = "FrontCard",  .SpriteName = "CharacterFrontCard", .FrameInter = 0.05f, .Loop = true , .ScaleToTexture = true });
		tmp->CreateAnimation({ .AnimationName = "FlipCard",  .SpriteName = "CharacterFlipCard" , .FrameInter = 0.05f, .Loop = true , .ScaleToTexture = true });

		tmp->Off();
		tmp->GetTransform()->SetLocalPosition(UIPos + float4(0, 15));

		CardPos.push_back(UIPos);
		SuperModeCard.push_back(tmp);
		UIPos.x += 20;

	}

}

void PlayerUI::Update(float _Delta)
{
	{
		int Hp = Player::MainPlayer->GetHP();
		if (Hp < 0)
		{
			Hp = 0;
		}
		HPRender->SetScaleToTexture(HPTexture[Hp]);
	}
	CardUIUpdate();
}

void PlayerUI::CardUIUpdate()
{
	int Energy = Player::MainPlayer->GetSuperModeEnergy();
	Energy = (500 < Energy ? 500 : Energy);

	if (LastInputEnergy != Energy) // 증가했다면
	{
		int FullCardCount = Energy / 100;
		float LastEnergy = static_cast<float>(Energy % 100) * 0.01f;
		int index = 0;

		for (int i = 0; i < 5; i++)
		{
			if (500 == Energy)
			{
				SuperModeCard[i]->ChangeAnimation("RotateCard");
				SuperModeCard[i]->SetAtlasData(0, 0, 1, 1);
				SuperModeCard[i]->GetTransform()->SetLocalPosition(CardPos[i] + CardYSize.half());
				SuperModeCard[i]->On();
				continue;
			}
			if (i < FullCardCount)
			{
				SuperModeCard[i]->ChangeAnimation("FrontCard");
				SuperModeCard[i]->SetAtlasData(0, 0, 1, 1);
				SuperModeCard[i]->GetTransform()->SetLocalPosition(CardPos[i] + CardYSize.half());
				SuperModeCard[i]->On();
			}
			else if (i == FullCardCount && LastEnergy > 0)
			{
				SuperModeCard[i]->ChangeAnimation("BackCard");
				SuperModeCard[i]->SetAtlasData(0, 0, 1, LastEnergy);
				SuperModeCard[i]->GetTransform()->SetLocalPosition(CardPos[i] + CardYSize.half() * LastEnergy);
				SuperModeCard[i]->On();
			}
			else
			{
				SuperModeCard[i]->Off();
			}
		}
		LastInputEnergy = Energy;
	}



}
