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


void PlayerUI::Start()
{
	if (nullptr == GameEngineSprite::Find("CharacterCardFlip"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources\\Texture\\PlayerUI");


		GameEngineSprite::LoadFolder("CharacterCardFlip", NewDir.GetPlusFileName("FlipCard").GetFullPath().c_str());
		GameEngineSprite::LoadFolder("Character1HPFlash", NewDir.GetPlusFileName("HpFlash").GetFullPath().c_str());
	}

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

	std::shared_ptr<GameEngineCamera> Camera = GetLevel()->GetCamera(100);
	Camera->SetProjectionType(CameraType::Orthogonal);
	Camera->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });

	float4 ScreenSize = GameEngineWindow::GetScreenSize();

	{
		// HPBar
		HPRender = CreateComponent<GameEngineUIRenderer>(CupHeadRendererOrder::UI);
		HPRender->SetScaleToTexture(HPTexture[3]);

		HPRender->GetTransform()->SetLocalPosition(-ScreenSize.half() + float4(20, 20) + HPRender->GetTransform()->GetLocalScale().half());
	}




	float4 UIPos = -GameEngineWindow::GetScreenSize().half();
	UIPos += float4(120, 20);
	for (int i = 0; i < 5; i++)
	{
		std::shared_ptr<GameContentsUIRenderer> tmp = CreateComponent< GameContentsUIRenderer>();
		CardPos.push_back(UIPos);
		tmp->Off();
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

	{
		float Energy = Player::MainPlayer->GetSuperModeEnergy();

		int CardCount = static_cast<int>(Energy) / 100;
		if (0 < CardCount && CardCount <= 5)
		{
			SuperModeCard[CardCount - 1]->SetScaleToTexture("hud_ch_card_flip_0000.png");
			SuperModeCard[CardCount - 1]->GetTransform()->SetLocalPosition(CardPos[CardCount - 1] + CardYSize.half());
			SuperModeCard[CardCount - 1]->On();

		}
		float LastEnergy = (Energy - (100.0f * CardCount)) * 0.01f;
		if (CardCount < 5 && 0.01f < LastEnergy)
		{
			SuperModeCard[CardCount]->SetScaleToCutTexture("hud_ch_card_flip_0000.png", 0, 0, 1, LastEnergy);
			SuperModeCard[CardCount]->GetTransform()->SetLocalPosition(CardPos[CardCount] + CardYSize.half() * LastEnergy);
			SuperModeCard[CardCount]->On();
		}
	}

}