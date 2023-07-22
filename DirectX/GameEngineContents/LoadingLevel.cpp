#include "PrecompileHeader.h"
#include "LoadingLevel.h"
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineCore.h>

#include "LoadingBackGround.h"
#include "FadeEffect.h"


CupheadLevel LoadingLevel::NextLevel = CupheadLevel::HILDA;
std::atomic_bool isDone = false;


void LoadingPlayer()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentResources");
	Dir.Move("ContentResources\\Texture");

	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\Idle\\Idle").GetFullPath(), "Cuphead_AirPlane_Origin_Idle");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\Idle\\up").GetFullPath(), "Cuphead_AirPlane_Origin_Idleup");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\Idle\\down").GetFullPath(), "Cuphead_AirPlane_Origin_Idledown");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\Intros\\Regular").GetFullPath(), "Cuphead_AirPlane_Origin_intro");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\Transicion\\transup").GetFullPath(), "Cuphead_AirPlane_Origin_transup");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\Transicion\\transdown").GetFullPath(), "Cuphead_AirPlane_Origin_transdown");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\Super\\Idle\\Idle").GetFullPath(), "Cuphead_AirPlane_Super_Idle");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\Super\\Idle\\up").GetFullPath(), "Cuphead_AirPlane_Super_Idleup");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\Super\\Idle\\down").GetFullPath(), "Cuphead_AirPlane_Super_Idledown");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\Super\\intro").GetFullPath(), "Cuphead_AirPlane_Super_intro");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\Super\\trans\\up").GetFullPath(), "Cuphead_AirPlane_Super_transup");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\Super\\trans\\down").GetFullPath(), "Cuphead_AirPlane_Super_transdown");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\Shrink\\idle\\Idle").GetFullPath(), "Cuphead_AirPlane_Shrink_Idle");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\Shrink\\idle\\up").GetFullPath(), "Cuphead_AirPlane_Shrink_Idleup");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\Shrink\\idle\\down").GetFullPath(), "Cuphead_AirPlane_Shrink_Idledown");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\Shrink\\morph").GetFullPath(), "Cuphead_AirPlane_Shrink_intro");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\Shrink\\trans\\up").GetFullPath(), "Cuphead_AirPlane_Shrink_transup");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\Shrink\\trans\\down").GetFullPath(), "Cuphead_AirPlane_Shrink_transdown");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\Parry").GetFullPath(), "Cuphead_AirPlane_Parry");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\Shoot\\Up").GetFullPath(), "Cuphead_AirPlane_Shoot_Up");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\Shoot\\Down").GetFullPath(), "Cuphead_AirPlane_Shoot_Down");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\Ghost").GetFullPath(), "Cuphead_AirPlane_Ghost");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\effect\\Spark").GetFullPath(), "Cuphead_AirPlane_Spark");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\bullet\\peashotFX").GetFullPath(), "peashotFX");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\effect\\PlaneSmoke").GetFullPath(), "Cuphead_AirPlane_Smoke_Idle");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\bullet\\peashot").GetFullPath(), "Cuphead_AirPlane_Bullet");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\effect\\Boom").GetFullPath(), "shmup_super_boom");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\effect\\Explode").GetFullPath(), "shmup_super_explode");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\effect\\Super_FX").GetFullPath(), "Super_FX");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\bullet\\Ex_Bullet").GetFullPath(), "Cuphead_AirPlane_ExBullet");

	if (nullptr == GameEngineTexture::Find("BlackBack.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources\\Texture\\Cuphead_AirPlane\\effect");
		GameEngineTexture::Load(NewDir.GetPlusFileName("BlackBack.png").GetFullPath());
	}
	else
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources\\Texture\\Cuphead_AirPlane\\effect");
		GameEngineTexture::ReLoad(NewDir.GetPlusFileName("BlackBack.png").GetFileName());
	}
}

void LoadingPlayerUI()
{
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources\\Texture\\PlayerUI\\HPBar");

		if (nullptr == GameEngineTexture::Find("hud_hp_1.png"))
		{
			std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });
			for (size_t i = 0; i < File.size(); i++)
			{
				GameEngineTexture::Load(File[i].GetFullPath());
			}
		}
		else
		{
			std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });
			for (size_t i = 0; i < File.size(); i++)
			{
				GameEngineTexture::ReLoad(File[i].GetFileName());
			}
		}
	}

	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources\\Texture\\PlayerUI");
		if (nullptr == GameEngineTexture::Find("hud_ch_card_Back.png"))
		{
			GameEngineTexture::Load(NewDir.GetPlusFileName("BackCard\\hud_ch_card_Back.png").GetFullPath());
			GameEngineTexture::Load(NewDir.GetPlusFileName("FrontCard\\hud_ch_card_front.png").GetFullPath());
		}
		else
		{
			GameEngineTexture::ReLoad("hud_ch_card_Back.png");
			GameEngineTexture::ReLoad("hud_ch_card_front.png");
		}
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources\\Texture");

		GameEngineSprite::ReLoad(Dir.GetPlusFileName("TextUI\\Text_GetReady").GetFullPath(), "Text_GetReady");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("TextUI\\Text_YouDied").GetFullPath(), "Text_YouDied");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("TextUI\\Text_KO").GetFullPath(), "Text_KO");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("PlayerUI\\RotateCard").GetFullPath().c_str(), "CharacterRotateCard");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("PlayerUI\\FlipCard").GetFullPath().c_str(), "CharacterFlipCard");
	}
}


void LoadingWallyLevel(GameEngineThread* Thread)
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentResources");
	Dir.Move("ContentResources\\Texture");

	//flappyBird
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 1\\FlappyBirds\\Yellow\\Fly").GetFullPath(), "FlapyBird_Yellow_Idle");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 1\\FlappyBirds\\Yellow\\Death").GetFullPath(), "FlapyBird_Yellow_Death");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 1\\FlappyBirds\\Pink\\Fly").GetFullPath(), "FlapyBird_Pink_Idle");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 1\\FlappyBirds\\Pink\\Death").GetFullPath(), "FlapyBird_Pink_Death");
	//wally1
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 1\\House").GetFullPath(), "Wally1_House");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 1\\Intro\\Feet\\Pendulum").GetFullPath(), "Wally1_Feet_Pendulum");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 1\\Intro\\Cuckoo").GetFullPath(), "Wally1_Cuckoo");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 1\\Intro\\Head").GetFullPath(), "Wally1_Head_Intro");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 1\\Intro\\Feet\\Morph").GetFullPath(), "Wally1_Feet_Morph");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 1\\Feet").GetFullPath(), "Wally1_Feet_Idle");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 1\\Head\\Idle\\Idle").GetFullPath(), "Wally1_Head_Idle");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 1\\Barf\\bird_barf_feet").GetFullPath(), "Wally1_Feet_Barf");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 1\\Barf\\bird_barf_head").GetFullPath(), "Wally1_Head_Barf");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 1\\Handgun\\bird_handgun_head").GetFullPath(), "Wally1_Head_HandGun");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 1\\FeatherAttack\\Steam").GetFullPath(), "Wally1_Head_Steam");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 1\\FeatherAttack\\Flap\\Intro").GetFullPath(), "Wally1_Flap_Intro");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 1\\FeatherAttack\\Flap\\Loop").GetFullPath(), "Wally1_Flap_Loop");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 1\\FeatherAttack\\Flap\\Outro").GetFullPath(), "Wally1_Flap_Outro");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 1\\FeatherAttack\\Pant").GetFullPath(), "Wally1_Head_Pant");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 1\\Death\\bird_large_death").GetFullPath(), "Wally1_Dead");
	//wally1 bullet
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 1\\Handgun\\Bullet\\Pre").GetFullPath(), "Wally1_Bullet_Pre");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 1\\Handgun\\Bullet\\Shoot").GetFullPath(), "Wally1_Bullet_Shoot");
	// wally1 egg pieces
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 1\\Egg\\Piece\\A").GetFullPath(), "Wally_Egg_Piece_A");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 1\\Egg\\Piece\\B").GetFullPath(), "Wally_Egg_Piece_B");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 1\\Egg\\Piece\\C").GetFullPath(), "Wally_Egg_Piece_C");
	// wally1 egg spin
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 1\\Egg\\Spin").GetFullPath(), "Wally_Egg_Spin");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 1\\Egg\\Dead").GetFullPath(), "Wally_Egg_Dead");
	//wally1 feather
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 1\\FeatherAttack\\Feathers\\Blue").GetFullPath(), "Wally1_Feather_Blue");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 1\\FeatherAttack\\Feathers\\Pink").GetFullPath(), "Wally1_Feather_Pink");
	//wally1 house
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 1\\Death\\House\\Back").GetFullPath(), "Wally1_House_Back");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 1\\Death\\House\\Bottom").GetFullPath(), "Wally1_House_Bottom");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 1\\Death\\House\\Front").GetFullPath(), "Wally1_House_Front");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 1\\Death\\House\\Left").GetFullPath(), "Wally1_House_Left");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 1\\Death\\House\\Right").GetFullPath(), "Wally1_House_Right");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 1\\Death\\House\\Top").GetFullPath(), "Wally1_House_Top");
	// wally2
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 2\\Idle\\Idle").GetFullPath(), "Wally2_Idle");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 2\\Idle\\Blink").GetFullPath(), "Wally2_Blink");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 2\\Shoot").GetFullPath(), "Wally2_Shoot");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 2\\Death\\Transition").GetFullPath(), "Wally2_Death_Trans");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 2\\Death\\Loop").GetFullPath(), "Wally2_Death_Loop");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 2\\Turn\\Turn_Right").GetFullPath(), "Wally2_Turn_Right");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 2\\Turn\\Turn_Left").GetFullPath(), "Wally2_Turn_Left");
	// wally2 bullet
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 2\\Bullet").GetFullPath(), "Wally2_Bullet");
	// wally2 egg
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 2\\Egg\\Rotate").GetFullPath(), "Wally2_Egg_Rotate");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 2\\Egg\\Death").GetFullPath(), "Wally2_Egg_Death");
	// wally3
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 3\\Garbage\\Intro").GetFullPath(), "Wally3_Garbage_Intro");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 3\\Garbage\\Loop").GetFullPath(), "Wally3_Garbage_Loop");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 3\\Garbage\\Outro").GetFullPath(), "Wally3_Garbage_Outro");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 3\\Idle").GetFullPath(), "Wally3_Idle");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 3\\Death\\Death").GetFullPath(), "Wally3_Death");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 3\\Regurgitate\\Intro").GetFullPath(), "Wally3_Regurgitate_Intro");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 3\\Regurgitate\\Loop").GetFullPath(), "Wally3_Regurgitate_Loop");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 3\\Regurgitate\\Outro").GetFullPath(), "Wally3_Regurgitate_Outro");
	// wally3 garbage
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 3\\Garbage\\Garbages\\garbage_apple").GetFullPath(), "Wally3_Garbage_Apple");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 3\\Garbage\\Garbages\\garbage_boot").GetFullPath(), "Wally3_Garbage_Boot");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 3\\Garbage\\Garbages\\garbage_fish").GetFullPath(), "Wally3_Garbage_Fish");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 3\\Garbage\\Garbages\\pink_garbage_boot").GetFullPath(), "Wally3_Garbage_Boot_Pink");
	// wally3 hearts
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 3\\Regurgitate\\Heart\\Heart").GetFullPath(), "Wally3_Heart");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 3\\Regurgitate\\Heart\\Mouse_Attack").GetFullPath(), "Wally3_Mouse_Attack");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 3\\Regurgitate\\Heart\\Mouse_Idle").GetFullPath(), "Wally3_Mouse_Idle");
	// wally3 leftbird
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 3\\Birds\\Bird A\\Idle").GetFullPath(), "Wally3_LeftBird_Idle");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 3\\Birds\\Bird A\\Attack").GetFullPath(), "Wally3_LeftBird_Attack");
	// wally3 pepper
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 3\\Death\\Pepper\\A").GetFullPath(), "Wally3_Pepper_A");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 3\\Death\\Pepper\\B").GetFullPath(), "Wally3_Pepper_B");
	// wally3 pill
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 3\\Birds\\Pills\\Normal\\Whole").GetFullPath(), "Wally3_Pill_Blue");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 3\\Birds\\Pills\\Pink\\Whole").GetFullPath(), "Wally3_Pill_Pink");
	// wally3 piil pieces
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 3\\Birds\\Pills\\Normal\\Blue Piece").GetFullPath(), "Wally3_Pill_Blue_Piece");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 3\\Birds\\Pills\\Normal\\Yellow Piece").GetFullPath(), "Wally3_Pill_Yellow_Piece");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 3\\Birds\\Pills\\Pink\\Dark Pink Piece").GetFullPath(), "Wally3_Pill_DPink_Piece");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 3\\Birds\\Pills\\Pink\\Light Pink Piece").GetFullPath(), "Wally3_Pill_LPink_Piece");
	// wally3 rightbird
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 3\\Birds\\Bird B\\Idle").GetFullPath(), "Wally3_RightBird_Idle");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 3\\Birds\\Bird B\\Attack").GetFullPath(), "Wally3_RightBird_Attack");
	// wally3 salt
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 3\\Death\\Salt\\A").GetFullPath(), "Wally3_Salt_A");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 3\\Death\\Salt\\B").GetFullPath(), "Wally3_Salt_B");


	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources\\Texture\\stage2\\Boss\\Wally\\Level");
		std::vector<GameEngineFile> AllLoadFile = NewDir.GetAllFile({ ".png" });
		if (nullptr == GameEngineTexture::Find("birdhouse_bg_0006.png"))
		{
			for (size_t i = 0; i < AllLoadFile.size(); i++)
			{
				GameEngineTexture::Load(AllLoadFile[i].GetFullPath());
			}
		}
		else
		{
			for (size_t i = 0; i < AllLoadFile.size(); i++)
			{
				GameEngineTexture::ReLoad(AllLoadFile[i].GetFullPath());
			}
		}
	}
	LoadingPlayer();
	LoadingPlayerUI();
	isDone = true;

}

void LoadingStoryLevel(GameEngineThread* Thread)
{
	GameEngineDirectory NewDir;
	NewDir.MoveParentToDirectory("ContentResources");
	NewDir.Move("ContentResources\\Texture");
	for (int i = 0; i <= 10; i++)
	{
		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("story\\before\\Page" + std::to_string(i)).GetFullPath(), "story" + std::to_string(i));
	}
	isDone = true;
}

void LoadingHildaLevel(GameEngineThread* Thread)
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentResources");
	Dir.Move("ContentResources\\Texture");
	//Fx
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\ChangePhase\\FX\\HildaChangeFX").GetFullPath(), "HildaChangeFX");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\ChangePhase\\FX\\DashBackExplodeFX").GetFullPath(), "HildaChangePhaseDashBackExplode");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\ChangePhase\\FX\\DashExplodeFX").GetFullPath(), "HildaChangePhaseDashExplode");
	// Hilda
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\Intro\\Hilda").GetFullPath(), "Hilda_Intro");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\Idle").GetFullPath(), "Hilda_Idle");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\Laugh\\Hilda").GetFullPath(), "Hilda_Shoot");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\ChangePhase\\Dash\\Dash").GetFullPath(), "Hilda_Dash");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\ChangePhase\\Dash\\DashBack").GetFullPath(), "Hilda_DashBack");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\ChangePhase\\Summon").GetFullPath(), "Hilda_Summon");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\Tornado\\Hilda").GetFullPath(), "Hilda_Tornado");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\ChangePhase\\ChangeBack").GetFullPath(), "Hilda_ChangeBack");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\ChangePhase\\FX\\SmokeFX").GetFullPath(), "HildaChangePhaseDashSmoke");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\Laugh\\Ha").GetFullPath(), "Hilda_Ha");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\Tornado\\Tornado\\Attack").GetFullPath(), "Hilda_Tornado_Attack");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\Tornado\\Tornado\\Intro").GetFullPath(), "Hilda_Tornado_Intro");
	//Taurus
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Taurus\\Idle").GetFullPath(), "Taurus_Idle");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Taurus\\Attack\\Charge").GetFullPath(), "Taurus_Charge");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Taurus\\Attack\\Attack").GetFullPath(), "Taurus_Attack");

	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Taurus\\Constellation").GetFullPath(), "Taurus_Constellation");
	//Sagittarius
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Sagittarius\\Sagittarius\\Lower\\Idle").GetFullPath(), "Sagittarius_Lower_Idle");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Sagittarius\\Sagittarius\\Upper\\Idle").GetFullPath(), "Sagittarius_Upper_Idle");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Sagittarius\\Sagittarius\\Upper\\Attack").GetFullPath(), "Sagittarius_Upper_Attack");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Sagittarius\\Arrow\\Arrow").GetFullPath(), "Sagittarius_Arrow");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Sagittarius\\Arrow\\AppearFX").GetFullPath(), "Sagittarius_AppearFX");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Sagittarius\\Arrow\\Star\\Idle").GetFullPath(), "Sagittarius_Star_Idle");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Sagittarius\\Arrow\\Star\\Trail\\A").GetFullPath(), "Sagittarius_Star_Trail");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Sagittarius\\Arrow\\Star\\Death").GetFullPath(), "Sagittarius_Star_Death");

	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Sagittarius\\Constellation").GetFullPath(), "Sagittarius_Constellation");
	//Gemini
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Gemini\\Idle").GetFullPath(), "Gemini_Idle");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Gemini\\Attack (A)").GetFullPath(), "Gemini_AttackA");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Gemini\\Attack (B)").GetFullPath(), "Gemini_AttackB");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Gemini\\Orb\\Idle\\Intro").GetFullPath(), "Orb_Idle_Intro");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Gemini\\Orb\\Idle\\Loop").GetFullPath(), "Orb_Idle_Loop");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Gemini\\Orb\\Idle\\Leave").GetFullPath(), "Orb_Idle_Leave");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Gemini\\Orb\\Attack\\Intro").GetFullPath(), "Orb_Attack_Intro");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Gemini\\Orb\\Attack\\Loop").GetFullPath(), "Orb_Attack_Loop");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Gemini\\Orb\\Attack\\Leave").GetFullPath(), "Orb_Attack_Leave");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Gemini\\Orb\\Attack\\FX\\Large").GetFullPath(), "Orb_Attack_Scatter");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Gemini\\Orb\\Attack\\BulletStream").GetFullPath(), "Orb_Bullet");

	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Gemini\\Constellation").GetFullPath(), "Gemini_Constellation");
	//Moon
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\TransitionToMoon\\Start").GetFullPath(), "Moon_Intro0");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\TransitionToMoon\\BoilA").GetFullPath(), "Moon_Intro1");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\TransitionToMoon\\Middle").GetFullPath(), "Moon_Intro2");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\TransitionToMoon\\BoilB").GetFullPath(), "Moon_Intro3");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\TransitionToMoon\\End").GetFullPath(), "Moon_Intro4");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Idle").GetFullPath(), "Moon_Idle");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Attack\\Intro").GetFullPath(), "Moon_Attack_Intro");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Attack\\AttackIdle").GetFullPath(), "Moon_Attack");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Attack\\Outtro").GetFullPath(), "Moon_Attack_Outro");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Death").GetFullPath(), "Moon_Death");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Projectiles\\UFO\\Red").GetFullPath(), "Hilda_UFO_Red");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Projectiles\\UFO\\Bronze").GetFullPath(), "Hilda_UFO_Bronze");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Projectiles\\UFO\\Beam").GetFullPath(), "Hilda_UFO_Beam");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Projectiles\\Star\\A").GetFullPath(), "Moon_Star_A");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Projectiles\\Star\\B").GetFullPath(), "Moon_Star_B");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Projectiles\\Star\\C").GetFullPath(), "Moon_Star_C");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Projectiles\\Star\\Pink").GetFullPath(), "Moon_Star_Pink");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Projectiles\\Star\\IdleFX").GetFullPath(), "Moon_Star_IdleFX");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Projectiles\\Star\\PinkFX").GetFullPath(), "Moon_Star_PinkFX");
	//Zeppling
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Purple\\Idle").GetFullPath(), "BlimpEnemy_PurPle_Idle");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Green\\Idle").GetFullPath(), "BlimpEnemy_Green_Idle");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Purple\\Attack").GetFullPath(), "BlimpEnemy_Purple_Attack");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Green\\Attack").GetFullPath(), "BlimpEnemy_Green_Attack");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Purple\\Turn").GetFullPath(), "BlimpEnemy_Purple_Turn");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Green\\Turn").GetFullPath(), "BlimpEnemy_Green_Turn");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Green\\Pieces\\A").GetFullPath(), "BlimpEnemy_Green_Death_A");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Green\\Pieces\\B").GetFullPath(), "BlimpEnemy_Green_Death_B");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Green\\Pieces\\C").GetFullPath(), "BlimpEnemy_Green_Death_C");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Green\\Pieces\\D").GetFullPath(), "BlimpEnemy_Green_Death_D");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Green\\Pieces\\E").GetFullPath(), "BlimpEnemy_Green_Death_E");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Green\\Pieces\\F").GetFullPath(), "BlimpEnemy_Green_Death_F");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Purple\\Pieces\\A").GetFullPath(), "BlimpEnemy_Purple_Death_A");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Purple\\Pieces\\B").GetFullPath(), "BlimpEnemy_Purple_Death_B");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Purple\\Pieces\\C").GetFullPath(), "BlimpEnemy_Purple_Death_C");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Purple\\Pieces\\D").GetFullPath(), "BlimpEnemy_Purple_Death_D");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Purple\\Pieces\\E").GetFullPath(), "BlimpEnemy_Purple_Death_E");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Purple\\Pieces\\F").GetFullPath(), "BlimpEnemy_Purple_Death_F");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Explode (Death)\\Explode").GetFullPath(), "BlimpEnemy_Explode");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Explode (Death)\\Spark").GetFullPath(), "BlimpEnemy_Spark");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Bullet\\A\\Bullet").GetFullPath(), "BlimpEnemy_BulletA");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Bullet\\B\\Bullet").GetFullPath(), "BlimpEnemy_BulletB");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Bullet\\C\\Bullet").GetFullPath(), "BlimpEnemy_BulletC");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Bullet\\Pink\\A").GetFullPath(), "BlimpEnemy_BulletPinkA");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Bullet\\Pink\\B").GetFullPath(), "BlimpEnemy_BulletPinkB");


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
	else
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources\\Texture\\stage1\\Boss\\Hilda\\Level");
		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });
		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::ReLoad(File[i].GetFileName());
		}
	}

	LoadingPlayer();
	LoadingPlayerUI();
	isDone = true;
}

LoadingLevel::LoadingLevel()
{
}

LoadingLevel::~LoadingLevel()
{
}



void LoadingLevel::Update(float _DeltaTime)
{
	if (0.0f == NextLevelTime && true == isDone)
	{
		NextLevelTime = GetLiveTime() + 1.0f;
	}
	if(0.0f != NextLevelTime && GetLiveTime() > NextLevelTime )
	{
		switch (NextLevel)
		{
		case CupheadLevel::NONE:
			return;
		case CupheadLevel::STORY:
			//if (true == isDone)
			//{
			GameEngineCore::ChangeLevel("StoryLevel");
			NextLevel = CupheadLevel::NONE;
			//}
			break;
		case CupheadLevel::HILDA:
			//if (1491 == GameEngineTexture::TextureReLoadCount || true == isDone)
			//{
			GameEngineCore::ChangeLevel("HildaBergLevel");
			NextLevel = CupheadLevel::NONE;
			//}
			break;
		case CupheadLevel::WALLY:
			//if (935 == GameEngineTexture::TextureReLoadCount || true == isDone)
			//{
			GameEngineCore::ChangeLevel("WallyLevel");
			NextLevel = CupheadLevel::NONE;
			//}
			break;
		case CupheadLevel::MAX:
			break;
		default:
			break;
		}
	}
}

void LoadingLevel::LevelChangeStart()
{
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });
	if (nullptr == BackGround)
	{
		BackGround = CreateActor<LoadingBackGround>(CupHeadActorOrder::BackGround);
	}

	if (nullptr == FEffect)
	{
		FEffect = GetLastTarget()->CreateEffect<FadeEffect>();
	}

	Dir.MoveParentToDirectory("ContentResources");
	Dir.Move("ContentResources\\Texture");

	ResetLiveTime();
	isDone = false;
	GameEngineTexture::TextureReLoadCount = 0;
	NextLevelTime = 0.0f;

	switch (NextLevel)
	{
	case CupheadLevel::NONE:
		break;
	case CupheadLevel::STORY:
		GameEngineCore::JobQueue.Work(LoadingStoryLevel);
		break;
	case CupheadLevel::HILDA:
		GameEngineCore::JobQueue.Work(LoadingHildaLevel);
		break;
	case CupheadLevel::WALLY:
		GameEngineCore::JobQueue.Work(LoadingWallyLevel);
		break;
	case CupheadLevel::MAX:
		break;
	default:
		break;
	}
}

void LoadingLevel::LevelChangeEnd()
{
	BackGround->Death();
	BackGround = nullptr;
	AllActorDestroy();
}