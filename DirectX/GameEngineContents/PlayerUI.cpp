#include "PrecompileHeader.h"
#include "PlayerUI.h"
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>

#include "PlayerAirPlaneMode.h"

PlayerUI::PlayerUI() 
{
}

PlayerUI::~PlayerUI() 
{
}


void PlayerUI::Start()
{

	if (nullptr == GameEngineTexture::Find("hud_ch_card_flip_0001.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources\\Texture\\PlayerUI");


		GameEngineSprite::LoadFolder("CharacterCardFlip", NewDir.GetPlusFileName("FlipCard").GetFullPath().c_str());
		GameEngineSprite::LoadFolder("Character1HPFlash", NewDir.GetPlusFileName("HpFlash").GetFullPath().c_str());

		NewDir.Move("HPBar");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });
		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}


	HPTexture[0] = GameEngineTexture::Find("hud_hp_dead");
	for (int i = 1; i <= 9; ++i)
	{
		std::string PNGName = "hud_hp_" + std::to_string(i)+".png";
		std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find(PNGName);
		HPTexture[i] = Texture;
	}

	std::shared_ptr<GameEngineCamera> Camera = GetLevel()->GetCamera(100);
	Camera->SetProjectionType(CameraType::Orthogonal);
	Camera->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });

	float4 ScreenSize = GameEngineWindow::GetScreenSize();

	{
		// HPBar
		HPRender = CreateComponent<GameEngineUIRenderer>(CupHeadRendererOrder::UI);
		HPRender->SetScaleToTexture("hud_hp_3.png");

		HPRender->GetTransform()->SetLocalPosition(-ScreenSize.half() + float4(20, 20) + HPRender->GetTransform()->GetLocalScale().half());
	}



}

void PlayerUI::Update(float _Delta)
{
	int Hp = PlayerAirPlaneMode::MainPlayer->GetHP();
	HPRender->SetScaleToTexture(HPTexture[Hp]);
}