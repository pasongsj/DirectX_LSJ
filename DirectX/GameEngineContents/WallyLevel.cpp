#include "PrecompileHeader.h"
#include "WallyLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>

//Effect
#include "OldFilmEffect.h"
#include "FadeEffect.h"


// Player
#include "PlayerAirPlaneMode.h"

//Boss 
#include "Wally1.h"
#include "Wally2.h"
#include "Wally3.h"

// BackGround
#include "WallyBack.h"
#include "WallyFore.h"

// UI
#include "PlayerUI.h"
#include "GetReadyUI.h"
#include "KnockOutUI.h"
#include "YouDieUI.h"
#include "Result_DeathUI.h"

// Effect
#include "OldFilmEffect.h"

#include "LoadingLevel.h"

WallyLevel::WallyLevel()
{
}

WallyLevel::~WallyLevel()
{
}
void WallyLevel::Start()
{
	GetLastTarget()->CreateEffect<OldFilmEffect>();

}

void WallyLevel::Update(float _DeltaTime)
{
	if (false == FirstSoundDone && true == AnnouncerSound.IsValid())
	{
		bool tmpCheck;
		AnnouncerSound.isPlaying(&tmpCheck);
		if (false == tmpCheck)
		{
			AnnouncerSound = GameEngineSound::Play("announcer_0002_e.wav");
			FirstSoundDone = true;
		}
	}
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
	if (true == GameEngineInput::IsDown("Key_K"))
	{
		if (nullptr != Boss)
		{
			Boss->Attack(100);
		}
	}
	if (true == GetMainCamera()->IsFreeCamera())
	{
		return;
	}
	EndCheck();
	BossSetting();

}
void WallyLevel::EndCheck()
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
			DeahtUI->SetCardUI("death_card_wally .png");
			DeahtUI->SetReTryBtn([] {
				LoadingLevel::SetLevel(CupheadLevel::WALLY);
				GameEngineCore::ChangeLevel("LoadingLevel");
				});
			DeahtUI->SetPhase(BossType::WALLY, Phase);
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
		AnnouncerSound = GameEngineSound::Play("vo_maus_fail_001.wav");
		return;

	}
}


void WallyLevel::LevelChangeStart()
{
	ResetLiveTime();
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });

	std::shared_ptr<GameEngineCamera> Camera = GetLevel()->GetCamera(100);
	Camera->SetProjectionType(CameraType::Orthogonal);
	Camera->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });

	Phase = 1;
	LastBossPos = float4::Zero;
	isEffectOn = false;
	DeathCard = false;
	EndTimer = 0.0f;



	if (nullptr == FEffect)
	{
		FEffect = GetLastTarget()->CreateEffect<FadeEffect>();
	}

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
	if (false == GameEngineInput::IsKey("Key_K"))
	{
		GameEngineInput::CreateKey("Key_K", 'K');
	}

	if (nullptr == GameEngineTexture::Find("birdhouse_bg_0006.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources\\Texture\\stage2\\Boss\\Wally\\Level");
		std::vector<GameEngineFile> AllLoadFile = Dir.GetAllFile({ ".png" });
		for (size_t i = 0; i < AllLoadFile.size(); i++)
		{
			GameEngineTexture::Load(AllLoadFile[i].GetFullPath());
		}
	}



	BackGroundSetting();
	CreateActor<PlayerAirPlaneMode>(CupHeadActorOrder::Player);
	CreateActor<PlayerUI>(CupHeadActorOrder::UI);

	CreateActor<GetReadyUI>(CupHeadActorOrder::UI);

	//GetLastTarget()->CreateEffect<OldFilmEffect>();

	BackGroundSound = GameEngineSound::Play("MUS_AviaryAction.wav");
	BackGroundSound.SetLoop(-1);
	ResultBoard::ResultTime = 0.0f;
	FirstSoundDone = false;
	AnnouncerSound = GameEngineSound::Play("announcer_0001_d.wav");
}

void WallyLevel::BackGroundSetting()
{
	// BackGround
	std::shared_ptr<WallyBack> BG0 = CreateActor<WallyBack>(CupHeadActorOrder::BackGround);
	BG0->Setting("birdhouse_bg_0008.png", 1000, 0.0f, 50.0f, WallyBackGroundSort::CENTER);

	std::shared_ptr<WallyBack> BG1 = CreateActor<WallyBack>(CupHeadActorOrder::BackGround);
	BG1->Setting("birdhouse_bg_0007.png", 950, 0.0f, 100.0f, WallyBackGroundSort::TOP);

	std::shared_ptr<WallyBack> BG2 = CreateActor<WallyBack>(CupHeadActorOrder::BackGround);
	BG2->Setting("birdhouse_bg_0006.png", 900, 0.0f, 150.0f, WallyBackGroundSort::BOT);

	std::shared_ptr<WallyBack> BG3 = CreateActor<WallyBack>(CupHeadActorOrder::BackGround);
	BG3->Setting("birdhouse_bg_0005.png", 850, 0.0f, 200.0f, WallyBackGroundSort::BOT);

	std::shared_ptr<WallyBack> BG4 = CreateActor<WallyBack>(CupHeadActorOrder::BackGround);
	BG4->Setting("birdhouse_bg_0004.png", 800, 0.0f, 250.0f, WallyBackGroundSort::BOT);

	std::shared_ptr<WallyFore> BG5 = CreateActor<WallyFore>(CupHeadActorOrder::BackGround);
	BG5->Setting("birdhouse_bg_0003.png", 300, 0.0f, 300.0f, WallyForeGroundSort::BOT);

	std::shared_ptr<WallyFore> BG6 = CreateActor<WallyFore>(CupHeadActorOrder::BackGround);
	BG6->Setting("birdhouse_bg_0002.png", 250, 0.0f, 350.0f, WallyForeGroundSort::BOT);

	std::shared_ptr<WallyFore> BG7 = CreateActor<WallyFore>(CupHeadActorOrder::BackGround);
	BG7->Setting("birdhouse_bg_0001.png", 200, 0.0f, 400.0f, WallyForeGroundSort::BOT);

}
void WallyLevel::BossSetting()
{
	// Hilda Boss 체크
	if (nullptr != Boss)
	{
		if (true == Boss->IsDeath()) // Hilda가 죽은 상태인지 체크
		{
			LastBossPos = Boss->GetTransform()->GetWorldPosition();
			Boss = nullptr;
		}
		else if (false == isEffectOn && true == Boss->isWallyDeath) // 마지막 페이즈
		{
			CreateActor<KnockOutUI>(CupHeadActorOrder::UI);
			FEffect->SetTakesTime(5.0f);
			FEffect->FadeIn();
			isEffectOn = true;
			ResultBoard::ResultTime = Player::MainPlayer->GetLiveTime();
			EndTimer = GetLiveTime() + 5.0f;
			AnnouncerSound = GameEngineSound::Play("announcer_knockout_0004.wav");
			BackGroundSound.SoundFadeOut(1.0f);
		}

	}

	if (nullptr == Boss)
	{
		switch (Phase)
		{
		case 1:
			Boss = CreateActor<Wally1>(CupHeadActorOrder::Boss);
			Boss->SetHP(300);
			++Phase;
			break;
		case 2:
			Boss = CreateActor<Wally2>(CupHeadActorOrder::Boss);
			Boss->SetHP(500);
			Boss->GetTransform()->SetLocalPosition(LastBossPos);
			++Phase;
			break;
		case 3:
			Boss = CreateActor<Wally3>(CupHeadActorOrder::Boss);
			Boss->SetHP(500);
			++Phase;
			break;
		default:
			break;
		}
	}
}
void WallyLevel::LevelChangeEnd()
{
	UnLoadSprite();
	if (0.0f == ResultBoard::ResultTime) 
	{
		ResultBoard::ResultTime = Player::MainPlayer->GetLiveTime();
	}
	if (nullptr != Player::MainPlayer)
	{
		Player::MainPlayer = nullptr;
	}
	Boss = nullptr;
	AllActorDestroy();
	BackGroundSound.Stop();
	AnnouncerSound.Stop();

}

void WallyLevel::UnLoadSprite()
{
	GameEngineSprite::UnLoad("FlapyBird_Yellow_Idle");
	GameEngineSprite::UnLoad("FlapyBird_Yellow_Death");
	GameEngineSprite::UnLoad("FlapyBird_Pink_Idle");
	GameEngineSprite::UnLoad("FlapyBird_Pink_Death");
	//wally1
	GameEngineSprite::UnLoad("Wally1_House");
	GameEngineSprite::UnLoad("Wally1_Feet_Pendulum");
	GameEngineSprite::UnLoad("Wally1_Cuckoo");
	GameEngineSprite::UnLoad("Wally1_Head_Intro");
	GameEngineSprite::UnLoad("Wally1_Feet_Morph");
	GameEngineSprite::UnLoad("Wally1_Feet_Idle");
	GameEngineSprite::UnLoad("Wally1_Head_Idle");
	GameEngineSprite::UnLoad("Wally1_Feet_Barf");
	GameEngineSprite::UnLoad("Wally1_Head_Barf");
	GameEngineSprite::UnLoad("Wally1_Head_HandGun");
	GameEngineSprite::UnLoad("Wally1_Head_Steam");
	GameEngineSprite::UnLoad("Wally1_Flap_Intro");
	GameEngineSprite::UnLoad("Wally1_Flap_Loop");
	GameEngineSprite::UnLoad("Wally1_Flap_Outro");
	GameEngineSprite::UnLoad("Wally1_Head_Pant");
	GameEngineSprite::UnLoad("Wally1_Dead");
	//wally1 bullet
	GameEngineSprite::UnLoad("Wally1_Bullet_Pre");
	GameEngineSprite::UnLoad("Wally1_Bullet_Shoot");
	// wally1 egg pieces
	GameEngineSprite::UnLoad("Wally_Egg_Piece_A");
	GameEngineSprite::UnLoad("Wally_Egg_Piece_B");
	GameEngineSprite::UnLoad("Wally_Egg_Piece_C");
	// wally1 egg spin
	GameEngineSprite::UnLoad("Wally_Egg_Spin");
	GameEngineSprite::UnLoad("Wally_Egg_Dead");
	//wally1 feather
	GameEngineSprite::UnLoad("Wally1_Feather_Blue");
	GameEngineSprite::UnLoad("Wally1_Feather_Pink");
	//wally1 house
	GameEngineSprite::UnLoad("Wally1_House_Back");
	GameEngineSprite::UnLoad("Wally1_House_Bottom");
	GameEngineSprite::UnLoad("Wally1_House_Front");
	GameEngineSprite::UnLoad("Wally1_House_Left");
	GameEngineSprite::UnLoad("Wally1_House_Right");
	GameEngineSprite::UnLoad("Wally1_House_Top");
	// wally2
	GameEngineSprite::UnLoad("Wally2_Idle");
	GameEngineSprite::UnLoad("Wally2_Blink");
	GameEngineSprite::UnLoad("Wally2_Shoot");
	GameEngineSprite::UnLoad("Wally2_Death_Trans");
	GameEngineSprite::UnLoad("Wally2_Death_Loop");
	GameEngineSprite::UnLoad("Wally2_Turn_Right");
	GameEngineSprite::UnLoad("Wally2_Turn_Left");
	// wally2 bullet
	GameEngineSprite::UnLoad("Wally2_Bullet");
	// wally2 egg
	GameEngineSprite::UnLoad("Wally2_Egg_Rotate");
	GameEngineSprite::UnLoad("Wally2_Egg_Death");
	// wally3
	GameEngineSprite::UnLoad("Wally3_Garbage_Intro");
	GameEngineSprite::UnLoad("Wally3_Garbage_Loop");
	GameEngineSprite::UnLoad("Wally3_Garbage_Outro");
	GameEngineSprite::UnLoad("Wally3_Idle");
	GameEngineSprite::UnLoad("Wally3_Death");
	GameEngineSprite::UnLoad("Wally3_Regurgitate_Intro");
	GameEngineSprite::UnLoad("Wally3_Regurgitate_Loop");
	GameEngineSprite::UnLoad("Wally3_Regurgitate_Outro");
	// wally3 garbage
	GameEngineSprite::UnLoad("Wally3_Garbage_Apple");
	GameEngineSprite::UnLoad("Wally3_Garbage_Boot");
	GameEngineSprite::UnLoad("Wally3_Garbage_Fish");
	GameEngineSprite::UnLoad("Wally3_Garbage_Boot_Pink");
	// wally3 hearts
	GameEngineSprite::UnLoad("Wally3_Heart");
	GameEngineSprite::UnLoad("Wally3_Mouse_Attack");
	GameEngineSprite::UnLoad("Wally3_Mouse_Idle");
	// wally3 leftbird
	GameEngineSprite::UnLoad("Wally3_LeftBird_Idle");
	GameEngineSprite::UnLoad("Wally3_LeftBird_Attack");
	// wally3 pepper
	GameEngineSprite::UnLoad("Wally3_Pepper_A");
	GameEngineSprite::UnLoad("Wally3_Pepper_B");
	// wally3 pill
	GameEngineSprite::UnLoad("Wally3_Pill_Blue");
	GameEngineSprite::UnLoad("Wally3_Pill_Pink");
	// wally3 piil pieces
	GameEngineSprite::UnLoad("Wally3_Pill_Blue_Piece");
	GameEngineSprite::UnLoad("Wally3_Pill_Yellow_Piece");
	GameEngineSprite::UnLoad("Wally3_Pill_DPink_Piece");
	GameEngineSprite::UnLoad("Wally3_Pill_LPink_Piece");
	// wally3 rightbird
	GameEngineSprite::UnLoad("Wally3_RightBird_Idle");
	GameEngineSprite::UnLoad("Wally3_RightBird_Attack");
	// wally3 salt
	GameEngineSprite::UnLoad("Wally3_Salt_A");
	GameEngineSprite::UnLoad("Wally3_Salt_B");


	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources\\Texture\\stage2\\Boss\\Wally\\Level");
		std::vector<GameEngineFile> AllLoadFile = NewDir.GetAllFile({ ".png" });
		if (nullptr != GameEngineTexture::Find("birdhouse_bg_0006.png"))
		{
			for (size_t i = 0; i < AllLoadFile.size(); i++)
			{
				GameEngineTexture::UnLoad(AllLoadFile[i].GetFileName());
			}
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
	GameEngineSprite::UnLoad("BlimpEnemy_BulletA");
	GameEngineSprite::UnLoad("BlimpEnemy_BulletB");
	GameEngineSprite::UnLoad("BlimpEnemy_BulletC");
	GameEngineSprite::UnLoad("BlimpEnemy_BulletPinkA");
	GameEngineSprite::UnLoad("BlimpEnemy_BulletPinkB");

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

	GameEngineSprite::UnLoad("Wally3_Heart_spit");			
	GameEngineSprite::UnLoad("nurse_bird_spit");			

	GameEngineSprite::UnLoad("deathcard_ch_run");
	GameEngineTexture::UnLoad("death_card_wally .png");
	GameEngineTexture::UnLoad("Death_Result_BG.png");
	GameEngineTexture::UnLoad("ExitButton_hover.png");
	GameEngineTexture::UnLoad("ExitButton_release.png");
	GameEngineTexture::UnLoad("QuitButton_hover.png");
	GameEngineTexture::UnLoad("QuitButton_release.png");
	GameEngineTexture::UnLoad("RetryButton_hover.png");
	GameEngineTexture::UnLoad("RetryButton_release.png");
}
