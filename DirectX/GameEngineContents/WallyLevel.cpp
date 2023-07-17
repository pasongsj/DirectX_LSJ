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

// Effect
#include "OldFilmEffect.h"

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

	if (true == GameEngineInput::IsDown("DebugRender"))
	{
		GameEngineLevel::IsDebugSwitch();
	}
	if (true == GameEngineInput::IsDown("ChangeLevel"))
	{
		GameEngineCore::ChangeLevel("ResultLevel");
		return;
	}
	

	EndCheck();
	BossSetting();

}
void WallyLevel::EndCheck()
{
	// LevelEnd 체크
	if (true == isEffectOn)
	{
		if (true == FEffect->IsEnd())
		{
			GameEngineCore::ChangeLevel("ResultLevel");
		}
		return;

	}

	// 플레이어가 죽어서 끝남
	if (false == isEffectOn && Player::MainPlayer->GetHP() <= 0)
	{
		CreateActor<YouDieUI>(CupHeadActorOrder::UI);
		FEffect->SetTakesTime(5.0f);
		FEffect->FadeIn();
		isEffectOn = true;
		return;

	}
}


void WallyLevel::LevelChangeStart()
{
	ResetLiveTime();
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });

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

	if(nullptr == GameEngineTexture::Find("birdhouse_bg_0006.png"))
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

}

void WallyLevel::BackGroundSetting()
{
	// BackGround
	std::shared_ptr<WallyBack> BG0 = CreateActor<WallyBack>(CupHeadActorOrder::BackGround);
	BG0->Setting("birdhouse_bg_0008.png", 1000,0.0f, 50.0f,WallyBackGroundSort::CENTER);

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
	AllActorDestroy();
	Player::MainPlayer = nullptr;

	UnLoadSprite();
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
	GameEngineSprite::UnLoad( "Wally3_Regurgitate_Outro");
	// wally3 garbage
	GameEngineSprite::UnLoad( "Wally3_Garbage_Apple");
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
	GameEngineSprite::UnLoad( "Wally3_Pill_Blue");
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
	GameEngineSprite::UnLoad("Wally3_Salt_B");
	GameEngineSprite::UnLoad("Wally3_Salt_A");


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
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources\\Texture\\stage2\\Boss\\Wally\\Level");
		std::vector<GameEngineFile> AllLoadFile = Dir.GetAllFile({ ".png" });
		if(nullptr != GameEngineTexture::Find("birdhouse_bg_0001.png"))
		{
			for (size_t i = 0; i < AllLoadFile.size(); i++)
			{
				GameEngineTexture::UnLoad(AllLoadFile[i].GetFileName());
			}
		}
	}
}
