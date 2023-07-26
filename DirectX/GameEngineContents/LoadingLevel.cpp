#include "PrecompileHeader.h"
#include "LoadingLevel.h"
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineCore.h>

#include "LoadingBackGround.h"
#include "FadeEffect.h"


CupheadLevel LoadingLevel::NextLevel = CupheadLevel::OVERWORLD;
std::atomic_bool isDone = false;
std::atomic_int LoadFuncCount = 0;

void LoadingAnnouncerSound()
{
	if (false == GameEngineSound::Find("announcer_0001_d.wav"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources\\Sound\\Announcer");
		std::vector<GameEngineFile> AllSoundFile = Dir.GetAllFile({ ".wav" });
		for (GameEngineFile _File : AllSoundFile)
		{
			GameEngineSound::Load(_File.GetFullPath());
		}
	}
}

void LoadingResultSound(GameEngineThread* Thread)
{
	if (false == GameEngineSound::Find("win_award_ping_01.wav"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources\\Sound\\Result");
		std::vector<GameEngineFile> AllSoundFile = Dir.GetAllFile({ ".wav" });
		for (GameEngineFile _File : AllSoundFile)
		{
			GameEngineSound::Load(_File.GetFullPath());
		}
	}
	++LoadFuncCount;
}

void LoadingShopSound(GameEngineThread* Thread)
{
	if (false == GameEngineSound::Find("store_pig_goodbye.wav"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources\\Sound\\Shop");
		std::vector<GameEngineFile> AllSoundFile = Dir.GetAllFile({ ".wav" });
		for (GameEngineFile _File : AllSoundFile)
		{
			GameEngineSound::Load(_File.GetFullPath());
		}
	}
	++LoadFuncCount;
}

void LoadingOverWorldSound(GameEngineThread* Thread)
{
	if (false == GameEngineSound::Find("WorldMap_Footstep_001.wav"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources\\Sound\\OverWorld");
		std::vector<GameEngineFile> AllSoundFile = Dir.GetAllFile({ ".wav" });
		for (GameEngineFile _File : AllSoundFile)
		{
			GameEngineSound::Load(_File.GetFullPath());
		}
	}
	++LoadFuncCount;
}
void LoadingPlayerSound(GameEngineThread* Thread)
{
	if (false == GameEngineSound::Find("player_plane_damaged_001.wav"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources\\Sound\\Cuphead_AirPlane");
		std::vector<GameEngineFile> AllSoundFile = Dir.GetAllFile({ ".wav" });
		for (GameEngineFile _File : AllSoundFile)
		{
			GameEngineSound::Load(_File.GetFullPath());
		}
	}
	++LoadFuncCount;

}
void LoadingHildaSound(GameEngineThread* Thread)
{
	LoadingAnnouncerSound();
	if (false == GameEngineSound::Find("blimp_cannon_ship_death_01.wav"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources\\Sound\\Stage1");
		std::vector<GameEngineFile> AllSoundFile = Dir.GetAllFile({ ".wav" });
		for (GameEngineFile _File : AllSoundFile)
		{
			GameEngineSound::Load(_File.GetFullPath());
		}
	}
	++LoadFuncCount;

}

void LoadingWallySound(GameEngineThread* Thread)
{
	LoadingAnnouncerSound();
	if (false == GameEngineSound::Find("flying_bird_bird_feathers_hesitate.wav"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources\\Sound\\Stage2");
		std::vector<GameEngineFile> AllSoundFile = Dir.GetAllFile({ ".wav" });
		for (GameEngineFile _File : AllSoundFile)
		{
			GameEngineSound::Load(_File.GetFullPath());
		}
	}
	++LoadFuncCount;

}

void LoadingDeathResultSprite(GameEngineThread* Thread)
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentResources");
	Dir.Move("ContentResources\\Texture\\Result\\deathscreen");

	if (nullptr == GameEngineTexture::Find("Death_Result_BG.png"))
	{
		GameEngineTexture::Load(Dir.GetPlusFileName("Death_Result_BG.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("death_card_blimp.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("death_card_wally .png").GetFullPath());

		GameEngineTexture::Load(Dir.GetPlusFileName("RetryButton_hover.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("RetryButton_release.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("ExitButton_hover.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("ExitButton_release.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("QuitButton_hover.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("QuitButton_release.png").GetFullPath());
	}
	{
		GameEngineTexture::ReLoad(Dir.GetPlusFileName("Death_Result_BG.png").GetFullPath());
		GameEngineTexture::ReLoad(Dir.GetPlusFileName("death_card_blimp.png").GetFullPath());
		GameEngineTexture::ReLoad(Dir.GetPlusFileName("death_card_wally .png").GetFullPath());

		GameEngineTexture::ReLoad(Dir.GetPlusFileName("RetryButton_hover.png").GetFullPath());
		GameEngineTexture::ReLoad(Dir.GetPlusFileName("RetryButton_release.png").GetFullPath());
		GameEngineTexture::ReLoad(Dir.GetPlusFileName("ExitButton_hover.png").GetFullPath());
		GameEngineTexture::ReLoad(Dir.GetPlusFileName("ExitButton_release.png").GetFullPath());
		GameEngineTexture::ReLoad(Dir.GetPlusFileName("QuitButton_hover.png").GetFullPath());
		GameEngineTexture::ReLoad(Dir.GetPlusFileName("QuitButton_release.png").GetFullPath());
	}
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("deathcard_ch_run").GetFullPath(), "deathcard_ch_run"); // path, name
	++LoadFuncCount;
}
void LoadingResultLevel(GameEngineThread* Thread)
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentResources");
	Dir.Move("ContentResources\\Texture\\Result\\winscreen");
	if (nullptr == GameEngineTexture::Find("winscreen_bg.png"))
	{
		GameEngineTexture::Load(Dir.GetPlusFileName("winscreen_bg.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("winscreen_board.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("winscreen_board_letter.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("winscreen_grey_star_a.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("winscreen_main_star_a.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("winscreen_line.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("Rank\\A_Pluse.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("Rank\\A_Zero.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("Rank\\B_Pluse.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("Rank\\B_Zero.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("Rank\\S_Zero.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("Rank\\question.png").GetFullPath());
	}
	{
		GameEngineTexture::ReLoad(Dir.GetPlusFileName("winscreen_bg.png").GetFullPath());
		GameEngineTexture::ReLoad(Dir.GetPlusFileName("winscreen_board.png").GetFullPath());
		GameEngineTexture::ReLoad(Dir.GetPlusFileName("winscreen_board_letter.png").GetFullPath());
		GameEngineTexture::ReLoad(Dir.GetPlusFileName("winscreen_grey_star_a.png").GetFullPath());
		GameEngineTexture::ReLoad(Dir.GetPlusFileName("winscreen_main_star_a.png").GetFullPath());
		GameEngineTexture::ReLoad(Dir.GetPlusFileName("winscreen_line.png").GetFullPath());
		GameEngineTexture::ReLoad(Dir.GetPlusFileName("Rank\\A_Pluse.png").GetFullPath());
		GameEngineTexture::ReLoad(Dir.GetPlusFileName("Rank\\A_Zero.png").GetFullPath());
		GameEngineTexture::ReLoad(Dir.GetPlusFileName("Rank\\B_Pluse.png").GetFullPath());
		GameEngineTexture::ReLoad(Dir.GetPlusFileName("Rank\\B_Zero.png").GetFullPath());
		GameEngineTexture::ReLoad(Dir.GetPlusFileName("Rank\\S_Zero.png").GetFullPath());
		GameEngineTexture::ReLoad(Dir.GetPlusFileName("Rank\\question.png").GetFullPath());
	}

	GameEngineSprite::ReLoad(Dir.GetPlusFileName("wincreen_result_title").GetFullPath(), "wincreen_result_title"); // path, name
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("winscreen_cuphead").GetFullPath(), "winscreen_cuphead"); // path, name
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("banner\\banner_NewRecord").GetFullPath(), "banner_NewRecord"); // path, name
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("winscreen_appear_star").GetFullPath(), "winscreen_appear_star"); // path, name
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("winscreen_circle").GetFullPath(), "winscreen_circle"); // path, name
	++LoadFuncCount;

}

void LoadingTutorialLevel(GameEngineThread* Thread)
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentResources");
	Dir.Move("ContentResources\\Texture\\Tutorial");

	GameEngineSprite::ReLoad(Dir.GetPlusFileName("shmup_tutorial_BG").GetFullPath(), "shmup_tutorial_BG");

	if (nullptr == GameEngineTexture::Find("shmup_tutorial_linework.png"))
	{
		GameEngineTexture::Load(Dir.GetPlusFileName("shmup_tutorial_linework.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("tutorial_pink_sphere_1.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("exit.png").GetFullPath());

	}
	else
	{
		GameEngineTexture::ReLoad(Dir.GetPlusFileName("shmup_tutorial_linework.png").GetFullPath());
		GameEngineTexture::ReLoad(Dir.GetPlusFileName("tutorial_pink_sphere_1.png").GetFullPath());
		GameEngineTexture::ReLoad(Dir.GetPlusFileName("exit.png").GetFullPath());
	}

	if (false == GameEngineSound::Find("MUS_Tutorial.wav"))
	{
		GameEngineDirectory SoundDir;
		SoundDir.MoveParentToDirectory("ContentResources");
		SoundDir.Move("ContentResources\\Sound\\Tutorial");
		GameEngineSound::Load(SoundDir.GetPlusFileName("MUS_Tutorial.wav").GetFullPath());

	}
	//LoadingPlayer();
	++LoadFuncCount;

}

void LoadingShopLevel(GameEngineThread* Thread)
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentResources");
	Dir.Move("ContentResources\\Texture\\Shop");

	if (nullptr == GameEngineTexture::Find("shop-background.png"))
	{
		GameEngineTexture::Load(Dir.GetPlusFileName("shop-background.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("shop_draped_fabric.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("shop_table.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("shop_table_chalkboard.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("shop_chalk_coin.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("shop_drawer_left.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("shop_drawer_right.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("ConfirmBack.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("hp1_explain.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("hp2_explain.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("coffee_explain.png").GetFullPath());
	}
	else
	{
		GameEngineTexture::ReLoad(Dir.GetPlusFileName("shop-background.png").GetFullPath());
		GameEngineTexture::ReLoad(Dir.GetPlusFileName("shop_draped_fabric.png").GetFullPath());
		GameEngineTexture::ReLoad(Dir.GetPlusFileName("shop_table.png").GetFullPath());
		GameEngineTexture::ReLoad(Dir.GetPlusFileName("shop_table_chalkboard.png").GetFullPath());
		GameEngineTexture::ReLoad(Dir.GetPlusFileName("shop_chalk_coin.png").GetFullPath());
		GameEngineTexture::ReLoad(Dir.GetPlusFileName("shop_drawer_left.png").GetFullPath());
		GameEngineTexture::ReLoad(Dir.GetPlusFileName("shop_drawer_right.png").GetFullPath());
		GameEngineTexture::ReLoad(Dir.GetPlusFileName("ConfirmBack.png").GetFullPath());
		GameEngineTexture::ReLoad(Dir.GetPlusFileName("hp1_explain.png").GetFullPath());
		GameEngineTexture::ReLoad(Dir.GetPlusFileName("hp2_explain.png").GetFullPath());
		GameEngineTexture::ReLoad(Dir.GetPlusFileName("coffee_explain.png").GetFullPath());
	}
	{
		GameEngineDirectory GoldDir;
		GoldDir.MoveParentToDirectory("ContentResources");
		GoldDir.Move("ContentResources\\Texture\\Shop\\GoldNumber");
		std::vector<GameEngineFile> numbertex = GoldDir.GetAllFile({".png"});
		if (nullptr == GameEngineTexture::Find("ch_world_map_gold_number_0.png"))
		{
			for (GameEngineFile _File : numbertex)
			{
				GameEngineTexture::Load(_File.GetFullPath());

			}
		}
		else
		{
			for (GameEngineFile _File : numbertex)
			{
				GameEngineTexture::ReLoad(_File.GetFullPath());

			}
		}
	}
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Coin").GetFullPath(), "Shop_Coin");

	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Items\\Coffee\\glow").GetFullPath(), "Item_Coffee_Glow");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Items\\Coffee\\dim").GetFullPath(), "Item_Coffee_Dim");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Items\\Coffee\\sold").GetFullPath(), "Item_Coffee_Sold");

	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Items\\Hp1\\glow").GetFullPath(), "Item_Hp1_Glow");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Items\\Hp1\\dim").GetFullPath(), "Item_Hp1_Dim");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Items\\Hp1\\sold").GetFullPath(), "Item_Hp1_Sold");

	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Items\\Hp2\\glow").GetFullPath(), "Item_Hp2_Glow");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Items\\Hp2\\dim").GetFullPath(), "Item_Hp2_Dim");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Items\\Hp2\\sold").GetFullPath(), "Item_Hp2_Sold");

	//pig
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Pig\\Clock").GetFullPath(), "Shop_Pig_Clock");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Pig\\GoodBye").GetFullPath(), "Shop_Pig_GoodBye");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Pig\\Idle").GetFullPath(), "Shop_Pig_Idle");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Pig\\nod").GetFullPath(), "Shop_Pig_nod");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Pig\\Welcome").GetFullPath(), "Shop_Pig_Welcome");
	++LoadFuncCount;

}

void LoadingOverWorldLevel1(GameEngineThread* Thread)
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
			GameEngineTexture::Load(Dir.GetPlusFileName("interactionIcon.png").GetFullPath());
			GameEngineTexture::Load(Dir.GetPlusFileName("title_card_tutorial_background.png").GetFullPath());
			GameEngineTexture::Load(Dir.GetPlusFileName("title_card_blimp_background.png").GetFullPath());
			GameEngineTexture::Load(Dir.GetPlusFileName("title_card_wally_background.png").GetFullPath());
			GameEngineTexture::Load(Dir.GetPlusFileName("title_card_shop_background.png").GetFullPath());

		}
		else
		{
			GameEngineTexture::ReLoad(Dir.GetPlusFileName("Overworld_Map.png").GetFullPath());
			GameEngineTexture::ReLoad(Dir.GetPlusFileName("Overworld_ColMap.png").GetFullPath());
			GameEngineTexture::ReLoad(Dir.GetPlusFileName("Overworld_Bush_Left.png").GetFullPath());
			GameEngineTexture::ReLoad(Dir.GetPlusFileName("Overworld_Bush_Right.png").GetFullPath());
			GameEngineTexture::ReLoad(Dir.GetPlusFileName("interactionIcon.png").GetFullPath());
			GameEngineTexture::ReLoad(Dir.GetPlusFileName("title_card_tutorial_background.png").GetFullPath());
			GameEngineTexture::ReLoad(Dir.GetPlusFileName("title_card_blimp_background.png").GetFullPath());
			GameEngineTexture::ReLoad(Dir.GetPlusFileName("title_card_wally_background.png").GetFullPath());
			GameEngineTexture::ReLoad(Dir.GetPlusFileName("title_card_shop_background.png").GetFullPath());

		}

		// Sprite
	}
	{
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToDirectory("ContentResources");
			Dir.Move("ContentResources\\Texture\\stage1\\Overworld");
			GameEngineSprite::ReLoad(Dir.GetPlusFileName("blimp").GetFullPath(), "OverWorld_To_Hilda");
			GameEngineSprite::ReLoad(Dir.GetPlusFileName("birdhouse").GetFullPath(), "OverWorld_To_Wally");
			GameEngineSprite::ReLoad(Dir.GetPlusFileName("Shmup_Tutorial").GetFullPath(), "OverWorld_To_Shmup_Tutorial");
			GameEngineSprite::ReLoad(Dir.GetPlusFileName("Shop").GetFullPath(), "OverWorld_To_Shop");
			GameEngineSprite::ReLoad(Dir.GetPlusFileName("NPC\\Canteen").GetFullPath(), "OverWorld_NPC_Canteen");
		}
	}
	++LoadFuncCount;

}
void LoadingOverWorldLevel2(GameEngineThread* Thread)
{
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources\\Texture\\Cuphead_Overworld");


		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Diag_Down_Idle").GetFullPath(), "Diag_Down_Idle");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Diag_Down_Move").GetFullPath(), "Diag_Down_Move");

		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Diag_Down_Idle_Left").GetFullPath(), "Diag_Down_Idle_Left");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Diag_Down_Move_Left").GetFullPath(), "Diag_Down_Move_Left");

		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Diag_Up_Idle").GetFullPath(), "Diag_Up_Idle");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Diag_Up_Move").GetFullPath(), "Diag_Up_Move");

		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Diag_Up_Idle_Left").GetFullPath(), "Diag_Up_Idle_Left");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Diag_Up_Move_Left").GetFullPath(), "Diag_Up_Move_Left");

		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Down_Idle").GetFullPath(), "Down_Idle");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Down_Move").GetFullPath(), "Down_Move");

		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Side_Idle").GetFullPath(), "Side_Idle");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Side_Move").GetFullPath(), "Side_Move");

		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Side_Idle_Left").GetFullPath(), "Side_Idle_Left");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Side_Move_Left").GetFullPath(), "Side_Move_Left");

		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Up_Idle").GetFullPath(), "Up_Idle");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Up_Move").GetFullPath(), "Up_Move");

		GameEngineSprite::ReLoad(Dir.GetPlusFileName("InterAction_Win").GetFullPath(), "InterAction_Win");

		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Dust").GetFullPath(), "OverWorldDust");
	}
	++LoadFuncCount;
}

void LoadingPlayer1(GameEngineThread* Thread)
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentResources");
	Dir.Move("ContentResources\\Texture");


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
		GameEngineTexture::ReLoad(NewDir.GetPlusFileName("BlackBack.png").GetFullPath());
	}
	++LoadFuncCount;

}
void LoadingPlayer2(GameEngineThread* Thread)
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
	++LoadFuncCount;
}

void LoadingPlayerUI1(GameEngineThread* Thread)
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
			GameEngineTexture::ReLoad(NewDir.GetPlusFileName("hud_ch_card_Back.png").GetFullPath());
			GameEngineTexture::ReLoad(NewDir.GetPlusFileName("hud_ch_card_front.png").GetFullPath());
		}
	}


	++LoadFuncCount;

}
void LoadingPlayerUI2(GameEngineThread* Thread)
{
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
	++LoadFuncCount;

}


void LoadingWallyLevel0(GameEngineThread* Thread)
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentResources");
	Dir.Move("ContentResources\\Texture");


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
				GameEngineTexture::ReLoad(AllLoadFile[i].GetFileName());
			}
		}
	}
	//LoadingPlayer();
	//LoadingPlayerUI();
	++LoadFuncCount;


}

void LoadingWallyLevel1(GameEngineThread* Thread)
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentResources");
	Dir.Move("ContentResources\\Texture");
	//flappyBird
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 1\\FlappyBirds\\Yellow\\Fly").GetFullPath(), "FlapyBird_Yellow_Idle");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 1\\FlappyBirds\\Yellow\\Death").GetFullPath(), "FlapyBird_Yellow_Death");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 1\\FlappyBirds\\Pink\\Fly").GetFullPath(), "FlapyBird_Pink_Idle");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage2\\Boss\\Wally\\Phase 1\\FlappyBirds\\Pink\\Death").GetFullPath(), "FlapyBird_Pink_Death");

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
	++LoadFuncCount;

}
void LoadingWallyLevel2(GameEngineThread* Thread)
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentResources");
	Dir.Move("ContentResources\\Texture");
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
	++LoadFuncCount;

}
void LoadingWallyLevel3(GameEngineThread* Thread)
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentResources");
	Dir.Move("ContentResources\\Texture");

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
	++LoadFuncCount;

}
void LoadingWallyLevel4(GameEngineThread* Thread)
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentResources");
	Dir.Move("ContentResources\\Texture");

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

	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Bullet\\A\\Bullet").GetFullPath(), "BlimpEnemy_BulletA");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Bullet\\B\\Bullet").GetFullPath(), "BlimpEnemy_BulletB");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Bullet\\C\\Bullet").GetFullPath(), "BlimpEnemy_BulletC");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Bullet\\Pink\\A").GetFullPath(), "BlimpEnemy_BulletPinkA");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Bullet\\Pink\\B").GetFullPath(), "BlimpEnemy_BulletPinkB");
	++LoadFuncCount;

}



void LoadingStory0(GameEngineThread* Thread)
{
	GameEngineDirectory NewDir;
	NewDir.MoveParentToDirectory("ContentResources");
	NewDir.Move("ContentResources\\Texture");
	for (int i = 0; i <= 1; i++)
	{
		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("story\\before\\Page" + std::to_string(i)).GetFullPath(), "story" + std::to_string(i));
	}
	++LoadFuncCount;


}
void LoadingStory1(GameEngineThread* Thread)
{
	GameEngineDirectory NewDir;
	NewDir.MoveParentToDirectory("ContentResources");
	NewDir.Move("ContentResources\\Texture");
	for (int i = 2; i <= 3; i++)
	{
		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("story\\before\\Page" + std::to_string(i)).GetFullPath(), "story" + std::to_string(i));
	}
	++LoadFuncCount;

}
void LoadingStory2(GameEngineThread* Thread)
{
	GameEngineDirectory NewDir;
	NewDir.MoveParentToDirectory("ContentResources");
	NewDir.Move("ContentResources\\Texture");
	for (int i = 4; i <= 5; i++)
	{
		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("story\\before\\Page" + std::to_string(i)).GetFullPath(), "story" + std::to_string(i));
	}
	++LoadFuncCount;

}
void LoadingStory3(GameEngineThread* Thread)
{
	GameEngineDirectory NewDir;
	NewDir.MoveParentToDirectory("ContentResources");
	NewDir.Move("ContentResources\\Texture");
	for (int i = 6; i <= 7; i++)
	{
		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("story\\before\\Page" + std::to_string(i)).GetFullPath(), "story" + std::to_string(i));
	}
	++LoadFuncCount;

}
void LoadingStory4(GameEngineThread* Thread)
{
	GameEngineDirectory NewDir;
	NewDir.MoveParentToDirectory("ContentResources");
	NewDir.Move("ContentResources\\Texture");
	for (int i = 8; i <= 9; i++)
	{
		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("story\\before\\Page" + std::to_string(i)).GetFullPath(), "story" + std::to_string(i));
	}
	++LoadFuncCount;

}

void LoadingStorySound(GameEngineThread* Thread)
{
	if (false == GameEngineSound::Find("cutscene_pageturn_01.wav"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources\\Sound\\Story");
		std::vector<GameEngineFile> AllSoundFile = Dir.GetAllFile({ ".wav" });
		for (GameEngineFile _File : AllSoundFile)
		{
			GameEngineSound::Load(_File.GetFullPath());
		}
	}
	GameEngineDirectory NewDir;
	NewDir.MoveParentToDirectory("ContentResources");
	NewDir.Move("ContentResources\\Texture");
	GameEngineSprite::ReLoad(NewDir.GetPlusFileName("story\\before\\Page" + std::to_string(10)).GetFullPath(), "story" + std::to_string(10));

	++LoadFuncCount;
}

void LoadingHildaLevel0(GameEngineThread* Thread)
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
			GameEngineTexture::ReLoad(File[i].GetFullPath());
		}
	}

	//LoadingPlayer();
	//LoadingPlayerUI();
	++LoadFuncCount;

}

void LoadingHildaLevel1(GameEngineThread* Thread)
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentResources");
	Dir.Move("ContentResources\\Texture");

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
	++LoadFuncCount;

}

void LoadingHildaLevel2(GameEngineThread* Thread)
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentResources");
	Dir.Move("ContentResources\\Texture");
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
	++LoadFuncCount;

}

void LoadingHildaLevel3(GameEngineThread* Thread)
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentResources");
	Dir.Move("ContentResources\\Texture");
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
	++LoadFuncCount;

}

void LoadingHildaLevel4(GameEngineThread* Thread)
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentResources");
	Dir.Move("ContentResources\\Texture");
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
	++LoadFuncCount;

}



LoadingLevel::LoadingLevel()
{
}

LoadingLevel::~LoadingLevel()
{
}



void LoadingLevel::Update(float _DeltaTime)
{
	switch (NextLevel)
	{
	case CupheadLevel::NONE:
		break;
	case CupheadLevel::STORY:
		if (6 == LoadFuncCount) 
		{
			GameEngineCore::ChangeLevel("StoryLevel");
		}
		break;
	case CupheadLevel::HILDA:
		if (12 == LoadFuncCount)
		{
			GameEngineCore::ChangeLevel("HildaBergLevel");
		}
		break;
	case CupheadLevel::WALLY:
		if (12 == LoadFuncCount)
		{
			GameEngineCore::ChangeLevel("WallyLevel");
		}
		break;
	case CupheadLevel::OVERWORLD:
		if (3 == LoadFuncCount)
		{
			GameEngineCore::ChangeLevel("OverWorldLevel");
		}
		break;
	case CupheadLevel::TUTORIAL:
		if (4 == LoadFuncCount)
		{
			GameEngineCore::ChangeLevel("TutorialLevel");
		}
		break;
	case CupheadLevel::SHOP:
		if (2 == LoadFuncCount)
		{
			GameEngineCore::ChangeLevel("ShopLevel");
		}
		break;
	case CupheadLevel::RESULT:
		if (2 == LoadFuncCount)
		{
			GameEngineCore::ChangeLevel("ResultLevel");
		}
		break;
	case CupheadLevel::MAX:
		break;
	default:
		break;

	}
}

void LoadingLevel::Start()
{
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });

}


void LoadingLevel::LevelChangeStart()
{
	if (nullptr == BackGround)
	{
		BackGround = CreateActor<LoadingBackGround>(CupHeadActorOrder::BackGround);
	}

	if (nullptr == FEffect)
	{
		FEffect = GetLastTarget()->CreateEffect<FadeEffect>();
	}

	ResetLiveTime();

	isDone = false;
	LoadFuncCount = 0;
	GameEngineTexture::TextureReLoadCount = 0;
	NextLevelTime = 0.0f;


	switch (NextLevel)
	{
	case CupheadLevel::NONE:
		break;
	case CupheadLevel::STORY:
		GameEngineCore::JobQueue.Work(LoadingStory0);
		GameEngineCore::JobQueue.Work(LoadingStory1);
		GameEngineCore::JobQueue.Work(LoadingStory2);
		GameEngineCore::JobQueue.Work(LoadingStory3);
		GameEngineCore::JobQueue.Work(LoadingStory4);
		GameEngineCore::JobQueue.Work(LoadingStorySound);
		break;
	case CupheadLevel::HILDA:
		GameEngineCore::JobQueue.Work(LoadingHildaLevel0);
		GameEngineCore::JobQueue.Work(LoadingHildaLevel1);
		GameEngineCore::JobQueue.Work(LoadingHildaLevel2);
		GameEngineCore::JobQueue.Work(LoadingHildaLevel3);
		GameEngineCore::JobQueue.Work(LoadingHildaLevel4);
		GameEngineCore::JobQueue.Work(LoadingPlayer1);
		GameEngineCore::JobQueue.Work(LoadingPlayer2);
		GameEngineCore::JobQueue.Work(LoadingPlayerUI1);
		GameEngineCore::JobQueue.Work(LoadingPlayerUI2);
		GameEngineCore::JobQueue.Work(LoadingDeathResultSprite);
		GameEngineCore::JobQueue.Work(LoadingPlayerSound);
		GameEngineCore::JobQueue.Work(LoadingHildaSound);
		break;
	case CupheadLevel::WALLY:
		GameEngineCore::JobQueue.Work(LoadingWallyLevel0);
		GameEngineCore::JobQueue.Work(LoadingWallyLevel1);
		GameEngineCore::JobQueue.Work(LoadingWallyLevel2);
		GameEngineCore::JobQueue.Work(LoadingWallyLevel3);
		GameEngineCore::JobQueue.Work(LoadingWallyLevel4);
		GameEngineCore::JobQueue.Work(LoadingPlayer1);
		GameEngineCore::JobQueue.Work(LoadingPlayer2);
		GameEngineCore::JobQueue.Work(LoadingPlayerUI1);
		GameEngineCore::JobQueue.Work(LoadingPlayerUI2);
		GameEngineCore::JobQueue.Work(LoadingDeathResultSprite);
		GameEngineCore::JobQueue.Work(LoadingPlayerSound);
		GameEngineCore::JobQueue.Work(LoadingWallySound);

		break;
	case CupheadLevel::OVERWORLD:
		GameEngineCore::JobQueue.Work(LoadingOverWorldLevel1);
		GameEngineCore::JobQueue.Work(LoadingOverWorldLevel2);
		GameEngineCore::JobQueue.Work(LoadingOverWorldSound);
		break;
	case CupheadLevel::TUTORIAL:
		GameEngineCore::JobQueue.Work(LoadingTutorialLevel);
		GameEngineCore::JobQueue.Work(LoadingPlayer1);
		GameEngineCore::JobQueue.Work(LoadingPlayer2);
		GameEngineCore::JobQueue.Work(LoadingPlayerSound);

		break;
	case CupheadLevel::SHOP:
		GameEngineCore::JobQueue.Work(LoadingShopLevel);
		GameEngineCore::JobQueue.Work(LoadingShopSound);
		break;
	case CupheadLevel::RESULT:
		GameEngineCore::JobQueue.Work(LoadingResultLevel);
		GameEngineCore::JobQueue.Work(LoadingResultSound);
		break;
	case CupheadLevel::MAX:
		break;
	default:
		break;
	}
}

void LoadingLevel::LevelChangeEnd()
{
}