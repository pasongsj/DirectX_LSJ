#include "PrecompileHeader.h"
#include "HildaBergLevel.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>



// BackGround
#include "HildaBergBack.h"
#include "HildaBergBack0.h"
#include "HildaBergBack1.h"
#include "HildaBergBack2.h"
#include "HildaBergBack3.h"

// Player
#include "PlayerAirPlaneMode.h"

// Boss
#include "Hilda.h"
#include "Zeppling.h"
#include "Taurus.h"
#include "Sagittarius.h"
#include "Gemini.h"
#include "Moon.h"

#include "HildaBoss.h"

// Test
#include "HIldaMoonUFO.h"
#include "ZepplingBullet.h"
#include "PlayerAirPlaneSmokeEffect.h"
#include "ZepplingBroken.h"
#include "MoonStar.h"

// UI
#include "PlayerUI.h"

HildaBergLevel::HildaBergLevel() 
{
}

HildaBergLevel::~HildaBergLevel() 
{

}

void HildaBergLevel::Start()
{

	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	//GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });
	GetMainCamera()->SetSortType(CupHeadRendererOrder::Boss, SortType::ZSort);

	if (false == GameEngineInput::IsKey("NextBoss"))
	{
		GameEngineInput::CreateKey("NextBoss", VK_F2);
	}
	if (false == GameEngineInput::IsKey("DebugRender"))
	{
		GameEngineInput::CreateKey("DebugRender", VK_F3);
	}

}

void HildaBergLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("DebugRender"))
	{
		GameEngineLevel::IsDebugSwitch();
	}

	// ¿‹√¨¿Ã º“»Ø
	if (GetLiveTime() > NextSponeTime)
	{
		if (Phase < 6)
		{
			CreateActor<Zeppling>(CupHeadActorOrder::Enemy);
		}
		else
		{
			CreateActor<HIldaMoonUFO>(CupHeadActorOrder::Enemy);
		}
		NextSponeTime += 5.0f;
	}

	float4 LastBossPos = float4::Zero;
	if (nullptr != Boss)
	{
		if (true == Boss->IsDeath())
		{
			LastBossPos = Boss->GetTransform()->GetWorldPosition();
			Boss = nullptr;
			++Phase;
		}
		else if (Boss->GetHP() <= 0 || true == GameEngineInput::IsDown("NextBoss"))
		{
			Boss->HildaDeath();
		}

	}



	if (nullptr == Boss)
	{
		switch (Phase)
		{
		case 1:
		{
			Boss = CreateActor<Hilda>(CupHeadActorOrder::Boss);
			Boss->SetPhase(1);
			Boss->SetHP(130);
			break;
		}
		case 2:
		{
			Boss = CreateActor<Taurus>(CupHeadActorOrder::Boss);
			Boss->SetPhase(2);
			Boss->SetHP(468);
			break;
		}
		case 3:
		{
			Boss = CreateActor<Hilda>(CupHeadActorOrder::Boss);
			Boss->SetPhase(3);
			Boss->SetHP(338);
			break;
		}
		case 4:
		{
			int RandomNum = GameEngineRandom::MainRandom.RandomInt(0, 9);
			if (1 == (RandomNum & 1))
			{
				Boss = CreateActor<Sagittarius>(CupHeadActorOrder::Boss);
			}
			else
			{
				Boss = CreateActor<Gemini>(CupHeadActorOrder::Boss);
			}
			Boss->SetPhase(4);
			Boss->SetHP(468);
			break;
		}
		case 5:
		{
			Boss = CreateActor<Hilda>(CupHeadActorOrder::Boss);
			Boss->SetPhase(5);
			Boss->SetHP(312);
			break;
		}
		case 6:
		{
			Boss = CreateActor<Moon>(CupHeadActorOrder::Boss);
			Boss->SetPhase(6);
			Boss->SetHP(884);
			Boss->GetTransform()->SetLocalPosition(LastBossPos);
			for (size_t i = 0; i < HildaBG.size(); i++)
			{
				HildaBG[i]->ChangeNight();
			}
			break;
		}
		default:
			break;
		}
	}

}


void HildaBergLevel::LevelChangeStart()
{
	ResetLiveTime();

	// BackGround ¿ÃπÃ¡ˆ ∑ŒµÂ
	if (nullptr == GameEngineTexture::Find("blimp_clouds_0001.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources\\Texture\\stage1\\Boss\\Hilda\\Level");
		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });
		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}

	if (nullptr == GameEngineTexture::Find("hud_hp_1.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources\\Texture\\PlayerUI");

		NewDir.Move("HPBar");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });
		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}

	if (nullptr == GameEngineTexture::Find("hud_ch_card_flip_0000.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources\\Texture\\PlayerUI");

		NewDir.Move("OriginCard");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });
		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}

	std::shared_ptr<HildaBergBack> BG0 = CreateActor<HildaBergBack0>(CupHeadActorOrder::BackGround);
	HildaBG.push_back(BG0);
	std::shared_ptr<HildaBergBack> BG1 = CreateActor<HildaBergBack1>(CupHeadActorOrder::BackGround);
	HildaBG.push_back(BG1);
	std::shared_ptr<HildaBergBack> BG2 = CreateActor<HildaBergBack2>(CupHeadActorOrder::BackGround);
	HildaBG.push_back(BG2);
	std::shared_ptr<HildaBergBack> BG3 = CreateActor<HildaBergBack3>(CupHeadActorOrder::BackGround);
	HildaBG.push_back(BG3);

std::shared_ptr<PlayerAirPlaneMode> NewPlayer7 = CreateActor<PlayerAirPlaneMode>(CupHeadActorOrder::Player);
	std::shared_ptr<PlayerUI> UI = CreateActor<PlayerUI>(CupHeadActorOrder::UI);
}

void HildaBergLevel::LevelChangeEnd()
{
	
}