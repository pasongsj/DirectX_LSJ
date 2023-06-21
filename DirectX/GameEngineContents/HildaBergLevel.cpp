#include "PrecompileHeader.h"
#include "HildaBergLevel.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineSprite.h>


#include "LoadingLevel.h"
// BackGround
#include "HildaBergBack.h"
#include "HildaBergBack0.h"
#include "HildaBergBack1.h"
#include "HildaBergBack2.h"
#include "HildaBergBack3.h"
#include "HildaBergBack4.h"
#include "HildaBergBack5.h"

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
#include "Constellation.h"

// Test
#include "HIldaMoonUFO.h"
#include "ZepplingBullet.h"
#include "PlayerAirPlaneSmokeEffect.h"
#include "ZepplingBroken.h"
#include "MoonStar.h"

// UI
#include "PlayerUI.h"
#include "GetReadyUI.h"
#include "KnockOutUI.h"

//Effect
#include "FadeEffect.h"

HildaBergLevel::HildaBergLevel() 
{
}

HildaBergLevel::~HildaBergLevel() 
{

}

void HildaBergLevel::Start()
{

}

void HildaBergLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("DebugRender"))
	{
		GameEngineLevel::IsDebugSwitch();
	}

	// ÀÜÃ¬ÀÌ ¼ÒÈ¯
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

	if (nullptr != Boss)
	{
		if (true == Boss->IsDeath())
		{
			LastBossPos = Boss->GetTransform()->GetWorldPosition();
			IsConstell = false;
			Boss = nullptr;
			++Phase;
		}
		else if (false == IsConstell && (Boss->GetHP() <= 0 || true == GameEngineInput::IsDown("NextBoss")))
		{
			Boss->HildaDeath();
			if (Phase == 1)
			{
				std::shared_ptr<Constellation> Constell = CreateActor<Constellation>(CupHeadActorOrder::UI);
				Constell->SetConstellation("Taurus");
			}
			else if(Phase == 3)
			{
				std::shared_ptr<Constellation> Constell = CreateActor<Constellation>(CupHeadActorOrder::UI);

				int RandomNum = GameEngineRandom::MainRandom.RandomInt(0, 1);
				IsGemini = static_cast<bool>(RandomNum);
				if (true == IsGemini)
				{
					Constell->SetConstellation("Gemini");
				}
				else
				{																	
					Constell->SetConstellation("Sagittarius");						
				}																	
			}
			else if (Phase == 6)
			{
				CreateActor<KnockOutUI>(CupHeadActorOrder::UI);
				EndTime = GetLiveTime() + 5.0f;
			}
			IsConstell = true;
		}

	}

	if (0.0f < EndTime && EndTime < GetLiveTime())
	{
		FEffect->SetTakesTime(3.0f);
		FEffect->FadeIn();
		EndTime = -1;
	}
	else if (EndTime < 0.0f && true == FEffect->IsEnd() || true == GameEngineInput::IsDown("ChangeLevel"))
	{
		GameEngineCore::ChangeLevel("OverWorldLevel");
		return;
	}

	BossSetting();

}
void HildaBergLevel::BossSetting()
{
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
			if (true == IsGemini)
			{
				Boss = CreateActor<Gemini>(CupHeadActorOrder::Boss);
			}
			else
			{
				Boss = CreateActor<Sagittarius>(CupHeadActorOrder::Boss);
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
	Phase = 1;
	IsConstell = false;
	IsGemini = false;

	//ReLoadSprite();
	if (nullptr == FEffect)
	{
		FEffect = GetLastTarget()->CreateEffect<FadeEffect>();
	}


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
	if (false == GameEngineInput::IsKey("ChangeLevel"))
	{
		GameEngineInput::CreateKey("ChangeLevel", VK_F4);
	}

	std::shared_ptr<HildaBergBack> BG0 = CreateActor<HildaBergBack0>(CupHeadActorOrder::BackGround);
	HildaBG.push_back(BG0);
	std::shared_ptr<HildaBergBack> BG1 = CreateActor<HildaBergBack1>(CupHeadActorOrder::BackGround);
	HildaBG.push_back(BG1);
	std::shared_ptr<HildaBergBack> BG2 = CreateActor<HildaBergBack2>(CupHeadActorOrder::BackGround);
	HildaBG.push_back(BG2);
	std::shared_ptr<HildaBergBack> BG3 = CreateActor<HildaBergBack3>(CupHeadActorOrder::BackGround);
	HildaBG.push_back(BG3);
	std::shared_ptr<HildaBergBack> BG4 = CreateActor<HildaBergBack4>(CupHeadActorOrder::BackGround);
	HildaBG.push_back(BG4);
	std::shared_ptr<HildaBergBack> BG5 = CreateActor<HildaBergBack5>(CupHeadActorOrder::BackGround);
	HildaBG.push_back(BG5);

	std::shared_ptr<PlayerAirPlaneMode> NewPlayer7 = CreateActor<PlayerAirPlaneMode>(CupHeadActorOrder::Player);
	std::shared_ptr<PlayerUI> UI = CreateActor<PlayerUI>(CupHeadActorOrder::UI);
	CreateActor<GetReadyUI>(CupHeadActorOrder::UI);
}

void HildaBergLevel::LevelChangeEnd()
{
	UnLoadSprite();
	if(nullptr != Player::MainPlayer)
	{
		Player::MainPlayer->Death();
		Player::MainPlayer = nullptr;
	}
	Boss->Death();
	Boss = nullptr;
	for (std::shared_ptr<HildaBergBack> _BG : HildaBG)
	{
		_BG->Death();
	}
	HildaBG.clear();
	AllActorDestroy();
}

void HildaBergLevel::UnLoadSprite()
{
		GameEngineSprite::UnLoad("Hilda_Intro");
		GameEngineSprite::UnLoad("Hilda_Idle");
		GameEngineSprite::UnLoad("Hilda_Shoot");
		GameEngineSprite::UnLoad("Hilda_Ha");
		GameEngineSprite::UnLoad("Hilda_Dash");
		GameEngineSprite::UnLoad("Hilda_DashBack");
		GameEngineSprite::UnLoad("Hilda_Summon");
		GameEngineSprite::UnLoad("Hilda_Tornado");
		GameEngineSprite::UnLoad("Hilda_Tornado_Attack");
		GameEngineSprite::UnLoad("Hilda_Tornado_Intro");
		GameEngineSprite::UnLoad("Taurus_Idle");
		GameEngineSprite::UnLoad("Taurus_Charge");
		GameEngineSprite::UnLoad("Taurus_Attack");
		GameEngineSprite::UnLoad("Taurus_Constellation");
		GameEngineSprite::UnLoad("Sagittarius_Lower_Idle");
		GameEngineSprite::UnLoad("Sagittarius_Upper_Idle");
		GameEngineSprite::UnLoad("Sagittarius_Upper_Attack");
		GameEngineSprite::UnLoad("Sagittarius_Arrow");
		GameEngineSprite::UnLoad("Sagittarius_AppearFX");
		GameEngineSprite::UnLoad("Sagittarius_Constellation");
		GameEngineSprite::UnLoad("Gemini_Idle");
		GameEngineSprite::UnLoad("Gemini_AttackA");
		GameEngineSprite::UnLoad("Gemini_AttackB");
		GameEngineSprite::UnLoad("Gemini_Constellation");
		GameEngineSprite::UnLoad("Orb_Idle_Intro");
		GameEngineSprite::UnLoad("Orb_Idle_Loop");
		GameEngineSprite::UnLoad("Orb_Idle_Leave");
		GameEngineSprite::UnLoad("Orb_Attack_Intro");
		GameEngineSprite::UnLoad("Orb_Attack_Loop");
		GameEngineSprite::UnLoad("Orb_Attack_Leave");
		GameEngineSprite::UnLoad("Orb_Attack_Scatter");
		GameEngineSprite::UnLoad("Orb_Bullet");
		GameEngineSprite::UnLoad("Moon_Intro0");
		GameEngineSprite::UnLoad("Moon_Intro1");
		GameEngineSprite::UnLoad("Moon_Intro2");
		GameEngineSprite::UnLoad("Moon_Intro3");
		GameEngineSprite::UnLoad("Moon_Intro4");
		GameEngineSprite::UnLoad("Moon_Idle");
		GameEngineSprite::UnLoad("Moon_Attack_Intro");
		GameEngineSprite::UnLoad("Moon_Attack");
		GameEngineSprite::UnLoad("Moon_Attack_Outtro");
		GameEngineSprite::UnLoad("Moon_Death");
		GameEngineSprite::UnLoad("Hilda_UFO_Red");
		GameEngineSprite::UnLoad("Hilda_UFO_Bronze");
		GameEngineSprite::UnLoad("Hilda_UFO_Beam");
		GameEngineSprite::UnLoad("Cuphead_AirPlane_Origin_Idle");
		GameEngineSprite::UnLoad("Cuphead_AirPlane_Origin_Idleup");
		GameEngineSprite::UnLoad("Cuphead_AirPlane_Origin_Idledown");
		GameEngineSprite::UnLoad("Cuphead_AirPlane_Origin_intro");
		GameEngineSprite::UnLoad("Cuphead_AirPlane_Origin_transup");
		GameEngineSprite::UnLoad("Cuphead_AirPlane_Origin_transdown");
		GameEngineSprite::UnLoad("Cuphead_AirPlane_Super_Idle");
		GameEngineSprite::UnLoad("Cuphead_AirPlane_Super_Idleup");
		GameEngineSprite::UnLoad("Cuphead_AirPlane_Super_Idledown");
		GameEngineSprite::UnLoad("Cuphead_AirPlane_Super_intro");
		GameEngineSprite::UnLoad("Cuphead_AirPlane_Super_transup");
		GameEngineSprite::UnLoad("Cuphead_AirPlane_Super_transdown");
		GameEngineSprite::UnLoad("Cuphead_AirPlane_Shrink_Idle");
		GameEngineSprite::UnLoad("Cuphead_AirPlane_Shrink_Idleup");
		GameEngineSprite::UnLoad("Cuphead_AirPlane_Shrink_Idledown");
		GameEngineSprite::UnLoad("Cuphead_AirPlane_Shrink_intro");
		GameEngineSprite::UnLoad("Cuphead_AirPlane_Shrink_transup");
		GameEngineSprite::UnLoad("Cuphead_AirPlane_Shrink_transdown");
		GameEngineSprite::UnLoad("Cuphead_AirPlane_Parry");
		GameEngineSprite::UnLoad("Cuphead_AirPlane_Spark");
		GameEngineSprite::UnLoad("BlimpEnemy_PurPle_Idle");
		GameEngineSprite::UnLoad("BlimpEnemy_Green_Idle");
		GameEngineSprite::UnLoad("BlimpEnemy_Purple_Attack");
		GameEngineSprite::UnLoad("BlimpEnemy_Green_Attack");
		GameEngineSprite::UnLoad("BlimpEnemy_Purple_Turn");
		GameEngineSprite::UnLoad("BlimpEnemy_Green_Turn");
		GameEngineSprite::UnLoad("BlimpEnemy_Green_Death_A");
		GameEngineSprite::UnLoad("BlimpEnemy_Green_Death_B");
		GameEngineSprite::UnLoad("BlimpEnemy_Green_Death_C");
		GameEngineSprite::UnLoad("BlimpEnemy_Green_Death_D");
		GameEngineSprite::UnLoad("BlimpEnemy_Green_Death_E");
		GameEngineSprite::UnLoad("BlimpEnemy_Green_Death_F");
		GameEngineSprite::UnLoad("BlimpEnemy_Purple_Death_A");
		GameEngineSprite::UnLoad("BlimpEnemy_Purple_Death_B");
		GameEngineSprite::UnLoad("BlimpEnemy_Purple_Death_C");
		GameEngineSprite::UnLoad("BlimpEnemy_Purple_Death_D");
		GameEngineSprite::UnLoad("BlimpEnemy_Purple_Death_E");
		GameEngineSprite::UnLoad("BlimpEnemy_Purple_Death_F");
		GameEngineSprite::UnLoad("BlimpEnemy_Explode");
		GameEngineSprite::UnLoad("BlimpEnemy_Spark");
		GameEngineSprite::UnLoad("Sagittarius_Star_Idle");
		GameEngineSprite::UnLoad("Sagittarius_Star_Trail");
		GameEngineSprite::UnLoad("Sagittarius_Star_Death");
		GameEngineSprite::UnLoad("Moon_Star_A");
		GameEngineSprite::UnLoad("Moon_Star_B");
		GameEngineSprite::UnLoad("Moon_Star_C");
		GameEngineSprite::UnLoad("Moon_Star_Pink");
		GameEngineSprite::UnLoad("Moon_Star_IdleFX");
		GameEngineSprite::UnLoad("Moon_Star_PinkFX");
		GameEngineSprite::UnLoad("Hilda_ChangeBack");
		GameEngineSprite::UnLoad("HildaChangePhaseDashSmoke");
		GameEngineSprite::UnLoad("peashotFX");
		GameEngineSprite::UnLoad("HildaChangePhaseDashBackExplode");
		GameEngineSprite::UnLoad("HildaChangePhaseDashExplode");
		GameEngineSprite::UnLoad("HildaChangeFX"); 
		if (nullptr != GameEngineTexture::Find("blimp_clouds_0001.png"))
		{
			GameEngineDirectory NewDir;
			NewDir.MoveParentToDirectory("ContentResources");
			NewDir.Move("ContentResources\\Texture\\stage1\\Boss\\Hilda\\Level");
			std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });
			for (size_t i = 0; i < File.size(); i++)
			{
				GameEngineTexture::UnLoad(File[i].GetFileName());
			}
		}
		if (nullptr != GameEngineTexture::Find("hud_hp_1.png"))
		{
			GameEngineDirectory NewDir;
			NewDir.MoveParentToDirectory("ContentResources");
			NewDir.Move("ContentResources\\Texture\\PlayerUI\\HPBar");

			std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });
			for (size_t i = 0; i < File.size(); i++)
			{
				GameEngineTexture::UnLoad(File[i].GetFileName());
			}
		}
		GameEngineSprite::UnLoad("BlimpEnemy_BulletA");
		GameEngineSprite::UnLoad("BlimpEnemy_BulletB");
		GameEngineSprite::UnLoad("BlimpEnemy_BulletC");
		GameEngineSprite::UnLoad("BlimpEnemy_BulletPinkA");
		GameEngineSprite::UnLoad("BlimpEnemy_BulletPinkB");
		GameEngineSprite::UnLoad("shmup_super_boom");
		GameEngineSprite::UnLoad("shmup_super_explode");
		GameEngineSprite::UnLoad("Super_FX");
		GameEngineSprite::UnLoad("Cuphead_AirPlane_Smoke_Idle");
		GameEngineSprite::UnLoad("Cuphead_AirPlane_Bullet");
		if (nullptr != GameEngineTexture::Find("BlackBack.png"))
		{
			GameEngineTexture::UnLoad("BlackBack.png");
		}
}
