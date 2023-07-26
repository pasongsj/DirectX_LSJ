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
#include "YouDieUI.h"
#include "Result_DeathUI.h"

//Effect
#include "FadeEffect.h"
#include "OldFilmEffect.h"

HildaBergLevel::HildaBergLevel()
{
}

HildaBergLevel::~HildaBergLevel()
{

}

void HildaBergLevel::Start()
{
	GetLastTarget()->CreateEffect<OldFilmEffect>();

}

void HildaBergLevel::SponeEnemy(float _DeltaTime)
{
	// 잔챙이 소환
	if (GetLiveTime() > NextSponeTime)
	{
		if (Phase < 7)
		{
			CreateActor<Zeppling>(CupHeadActorOrder::Enemy);
		}
		else
		{
			CreateActor<HIldaMoonUFO>(CupHeadActorOrder::Enemy);
		}
		NextSponeTime += GameEngineRandom::MainRandom.RandomFloat(1.0f, 5.0f);
	}
}

void HildaBergLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("DebugRender"))
	{
		GameEngineLevel::IsDebugSwitch();
	}
	if (true == GameEngineInput::IsDown("ChangeLevel"))
	{
		LoadingLevel::SetLevel(CupheadLevel::RESULT);
		GameEngineCore::ChangeLevel("LoadingLevel");
		return;
	}


	EndCheck();
	SponeEnemy(_DeltaTime);
	BossSetting();

}

void HildaBergLevel::EndCheck()
{
	// LevelEnd 체크
	if (0 != EndTimer && EndTimer < GetLiveTime())
	{
		if (true == isEffectOn && true == FEffect->IsEnd())
		{
			LoadingLevel::SetLevel(CupheadLevel::RESULT);
			GameEngineCore::ChangeLevel("LoadingLevel");
			EndTimer = 0.0f;

		}
		if (true == DeathCard)
		{
			std::shared_ptr< Result_DeathUI> DeahtUI = CreateActor< Result_DeathUI>(CupHeadActorOrder::UI);
			DeahtUI->SetCardUI("death_card_blimp.png");
			DeahtUI->SetReTryBtn([] {
				LoadingLevel::SetLevel(CupheadLevel::HILDA);
				GameEngineCore::ChangeLevel("LoadingLevel");
				});
			EndTimer = 0.0f;
		}
		return;

	}
	// 플레이어가 죽어서 끝남
	if (false == DeathCard && Player::MainPlayer->GetHP() <= 0)
	{
		EndTimer = GetLiveTime() + 3.0f;
		DeathCard = true;
		CreateActor<YouDieUI>(CupHeadActorOrder::UI);

		return;

	}
}


void HildaBergLevel::BossSetting()
{
	// Hilda Boss 체크
	if (nullptr != Boss)
	{
		if (true == Boss->IsDeath()) // Hilda가 죽은 상태인지 체크
		{
			LastBossPos = Boss->GetTransform()->GetWorldPosition();
			Boss = nullptr;
		}
		else if (false == isEffectOn && true == Boss->isHildaDeath) // 마지막 페이즈
		{
			CreateActor<KnockOutUI>(CupHeadActorOrder::UI);
			FEffect->SetTakesTime(5.0f);
			FEffect->FadeIn();
			isEffectOn = true;
			EndTimer = GetLiveTime() + 5.0f;
			ResultBoard::ResultTime = Player::MainPlayer->GetLiveTime();
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
			std::shared_ptr<Constellation> Constell = CreateActor<Constellation>(CupHeadActorOrder::UI);
			Constell->SetConstellation("Taurus");
			GameEngineSoundPlayer TransSound = GameEngineSound::Play("blimp_lady_constellation_transform.wav");
			TransSound.SetPosition(1.7f);
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
			std::shared_ptr<Constellation> Constell = CreateActor<Constellation>(CupHeadActorOrder::UI);
			GameEngineSoundPlayer TransSound = GameEngineSound::Play("blimp_lady_constellation_transform.wav");
			TransSound.SetPosition(1.7f);
			int RandomNum = GameEngineRandom::MainRandom.RandomInt(0, 1);
			IsGemini = static_cast<bool>(RandomNum);
			if (true == IsGemini)
			{
				Constell->SetConstellation("Gemini");
				Boss = CreateActor<Gemini>(CupHeadActorOrder::Boss);
			}
			else
			{
				Constell->SetConstellation("Sagittarius");
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
		++Phase;
	}
}


void HildaBergLevel::LevelChangeStart()
{
	ResetLiveTime();
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });
	GetMainCamera()->SetSortType(CupHeadRendererOrder::Boss, SortType::ZSort);

	std::shared_ptr<GameEngineCamera> Camera = GetLevel()->GetCamera(100);
	Camera->SetProjectionType(CameraType::Orthogonal);
	Camera->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });

	Phase = 1;
	IsConstell = false;
	IsGemini = false;
	isEffectOn = false;
	LastBossPos = float4::Zero;
	DeathCard = false;


	// effect
	if (nullptr == FEffect)
	{
		FEffect = GetLastTarget()->CreateEffect<FadeEffect>();
	}

	// -- key
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

	std::shared_ptr<PlayerAirPlaneMode> NewPlayer = CreateActor<PlayerAirPlaneMode>(CupHeadActorOrder::Player);
	std::shared_ptr<PlayerUI> UI = CreateActor<PlayerUI>(CupHeadActorOrder::UI);
	CreateActor<GetReadyUI>(CupHeadActorOrder::UI);

	GameEngineSound::Play("blimp_intro_start.wav");
	BackrGroundSound = GameEngineSound::Play("bgm_level_flying_blimp.wav");
	BackrGroundSound.SetLoop(-1);
	ResultBoard::ResultTime = 0.0f;
}

void HildaBergLevel::LevelChangeEnd()
{
	UnLoadSprite();
	if (0.0f == ResultBoard::ResultTime)
	{
		ResultBoard::ResultTime = Player::MainPlayer->GetLiveTime();
	}
	if (nullptr != Player::MainPlayer)
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
	GetLastTarget()->ReleaseEffect(FEffect);
	FEffect = nullptr;
	GameEngineSound::ResourcesClear();
}

void HildaBergLevel::UnLoadSprite()
{

	//Fx
	GameEngineSprite::UnLoad("HildaChangeFX");
	GameEngineSprite::UnLoad("HildaChangePhaseDashBackExplode");
	GameEngineSprite::UnLoad("HildaChangePhaseDashExplode");
	// Hilda
	GameEngineSprite::UnLoad("Hilda_Intro");
	GameEngineSprite::UnLoad("Hilda_Idle");
	GameEngineSprite::UnLoad("Hilda_Shoot");
	GameEngineSprite::UnLoad("Hilda_Dash");
	GameEngineSprite::UnLoad("Hilda_DashBack");
	GameEngineSprite::UnLoad("Hilda_Summon");
	GameEngineSprite::UnLoad("Hilda_Tornado");
	GameEngineSprite::UnLoad("Hilda_ChangeBack");
	GameEngineSprite::UnLoad("HildaChangePhaseDashSmoke");
	GameEngineSprite::UnLoad("Hilda_Ha");
	GameEngineSprite::UnLoad("Hilda_Tornado_Attack");
	GameEngineSprite::UnLoad("Hilda_Tornado_Intro");
	//Taurus
	GameEngineSprite::UnLoad("Taurus_Idle");
	GameEngineSprite::UnLoad("Taurus_Charge");
	GameEngineSprite::UnLoad("Taurus_Attack");

	GameEngineSprite::UnLoad("Taurus_Constellation");
	//Sagittarius
	GameEngineSprite::UnLoad("Sagittarius_Lower_Idle");
	GameEngineSprite::UnLoad("Sagittarius_Upper_Idle");
	GameEngineSprite::UnLoad("Sagittarius_Upper_Attack");
	GameEngineSprite::UnLoad("Sagittarius_Arrow");
	GameEngineSprite::UnLoad("Sagittarius_AppearFX");
	GameEngineSprite::UnLoad("Sagittarius_Star_Idle");
	GameEngineSprite::UnLoad("Sagittarius_Star_Trail");
	GameEngineSprite::UnLoad("Sagittarius_Star_Death");

	GameEngineSprite::UnLoad("Sagittarius_Constellation");
	//Gemini
	GameEngineSprite::UnLoad("Gemini_Idle");
	GameEngineSprite::UnLoad("Gemini_AttackA");
	GameEngineSprite::UnLoad("Gemini_AttackB");
	GameEngineSprite::UnLoad("Orb_Idle_Intro");
	GameEngineSprite::UnLoad("Orb_Idle_Loop");
	GameEngineSprite::UnLoad("Orb_Idle_Leave");
	GameEngineSprite::UnLoad("Orb_Attack_Intro");
	GameEngineSprite::UnLoad("Orb_Attack_Loop");
	GameEngineSprite::UnLoad("Orb_Attack_Leave");
	GameEngineSprite::UnLoad("Orb_Attack_Scatter");
	GameEngineSprite::UnLoad("Orb_Bullet");

	GameEngineSprite::UnLoad("Gemini_Constellation");
	//Moon
	GameEngineSprite::UnLoad("Moon_Intro0");
	GameEngineSprite::UnLoad("Moon_Intro1");
	GameEngineSprite::UnLoad("Moon_Intro2");
	GameEngineSprite::UnLoad("Moon_Intro3");
	GameEngineSprite::UnLoad("Moon_Intro4");
	GameEngineSprite::UnLoad("Moon_Idle");
	GameEngineSprite::UnLoad("Moon_Attack_Intro");
	GameEngineSprite::UnLoad("Moon_Attack");
	GameEngineSprite::UnLoad("Moon_Attack_Outro");
	GameEngineSprite::UnLoad("Moon_Death");
	GameEngineSprite::UnLoad("Hilda_UFO_Red");
	GameEngineSprite::UnLoad("Hilda_UFO_Bronze");
	GameEngineSprite::UnLoad("Hilda_UFO_Beam");
	GameEngineSprite::UnLoad("Moon_Star_A");
	GameEngineSprite::UnLoad("Moon_Star_B");
	GameEngineSprite::UnLoad("Moon_Star_C");
	GameEngineSprite::UnLoad("Moon_Star_Pink");
	GameEngineSprite::UnLoad("Moon_Star_IdleFX");
	GameEngineSprite::UnLoad("Moon_Star_PinkFX");
	//Zeppling
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
	GameEngineSprite::UnLoad("BlimpEnemy_BulletA");
	GameEngineSprite::UnLoad("BlimpEnemy_BulletB");
	GameEngineSprite::UnLoad("BlimpEnemy_BulletC");
	GameEngineSprite::UnLoad("BlimpEnemy_BulletPinkA");
	GameEngineSprite::UnLoad("BlimpEnemy_BulletPinkB");


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
	// Player
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
	GameEngineSprite::UnLoad("Cuphead_AirPlane_Shoot_Up");
	GameEngineSprite::UnLoad("Cuphead_AirPlane_Shoot_Down");
	GameEngineSprite::UnLoad("Cuphead_AirPlane_Ghost");
	GameEngineSprite::UnLoad("Cuphead_AirPlane_Spark");
	GameEngineSprite::UnLoad("peashotFX");
	GameEngineSprite::UnLoad("Cuphead_AirPlane_Smoke_Idle");
	GameEngineSprite::UnLoad("Cuphead_AirPlane_Bullet");
	GameEngineSprite::UnLoad("shmup_super_boom");
	GameEngineSprite::UnLoad("shmup_super_explode");
	GameEngineSprite::UnLoad("Super_FX");
	GameEngineSprite::UnLoad("Cuphead_AirPlane_ExBullet");

	// playerUI
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources\\Texture\\PlayerUI\\HPBar");
		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });
		if (nullptr != GameEngineTexture::Find("hud_hp_1.png"))
		{
			for (size_t i = 0; i < File.size(); i++)
			{
				GameEngineTexture::UnLoad(File[i].GetFileName());
			}
		}
	}
	GameEngineTexture::UnLoad("BlackBack.png");
	GameEngineTexture::UnLoad("hud_ch_card_Back.png");
	GameEngineTexture::UnLoad("hud_ch_card_front.png");

	GameEngineSprite::UnLoad("Text_GetReady");
	GameEngineSprite::UnLoad("Text_YouDied");
	GameEngineSprite::UnLoad("Text_KO");
	GameEngineSprite::UnLoad("CharacterRotateCard");
	GameEngineSprite::UnLoad("CharacterFlipCard");


	GameEngineSprite::UnLoad("deathcard_ch_run");
	GameEngineTexture::UnLoad("death_card_blimp.png");
	GameEngineTexture::UnLoad("Death_Result_BG.png");
	GameEngineTexture::UnLoad("ExitButton_hover.png");
	GameEngineTexture::UnLoad("ExitButton_release.png");
	GameEngineTexture::UnLoad("QuitButton_hover.png");
	GameEngineTexture::UnLoad("QuitButton_release.png");	
	GameEngineTexture::UnLoad("RetryButton_hover.png");
	GameEngineTexture::UnLoad("RetryButton_release.png");
	BackrGroundSound.Stop();
}
