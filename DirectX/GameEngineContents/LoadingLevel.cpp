#include "PrecompileHeader.h"
#include "LoadingLevel.h"
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineCore.h>

#include "LoadingBackGround.h"
#include "FadeEffect.h"


CupheadLevel LoadingLevel::NextLevel = CupheadLevel::HILDA;
int LoadingLevel::Phase = 0;
bool LoadingLevel::isEnd = false;

LoadingLevel::LoadingLevel()
{
}

LoadingLevel::~LoadingLevel()
{
}

void LoadingLevel::Start()
{
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });


	if (nullptr == FEffect)
	{
		FEffect = GetLastTarget()->CreateEffect<FadeEffect>();
	}

}

void LoadingLevel::Update(float _DeltaTime)
{
	if (true == isEnd || CupheadLevel::NONE == NextLevel)
	{
		return;
	}

	if (CupheadLevel::HILDA == NextLevel)
	{
		LoadHildaSprite();
	}
	else if (CupheadLevel::STORY == NextLevel)
	{
		LoadStorySprite();
	}
}

void LoadingLevel::LevelChangeStart()
{
	Phase = 0;
	if (nullptr == BackGround)
	{
		BackGround = CreateActor<LoadingBackGround>(CupHeadActorOrder::BackGround);
	}

	Dir.MoveParentToDirectory("ContentResources");
	Dir.Move("ContentResources\\Texture");
}

void LoadingLevel::LevelChangeEnd()
{
	BackGround->Death();
	BackGround = nullptr;
}

void LoadingLevel::LoadHildaSprite()
{

	switch (Phase)
	{
	case 0:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\Intro\\Hilda").GetFullPath(), "Hilda_Intro");
		++Phase;
		break;
	case 1:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\Idle").GetFullPath(), "Hilda_Idle");
		++Phase;
		break;
	case 2:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\Laugh\\Hilda").GetFullPath(), "Hilda_Shoot");
		++Phase;
		break;
	case 3:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\Laugh\\Ha").GetFullPath(), "Hilda_Ha");
		++Phase;
		break;
	case 4:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\ChangePhase\\Dash\\Dash").GetFullPath(), "Hilda_Dash");
		++Phase;
		break;
	case 5:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\ChangePhase\\Dash\\DashBack").GetFullPath(), "Hilda_DashBack");
		++Phase;
		break;
	case 6:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\ChangePhase\\Summon").GetFullPath(), "Hilda_Summon");
		++Phase;
		break;
	case 7:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\Tornado\\Hilda").GetFullPath(), "Hilda_Tornado");
		++Phase;
		break;
	case 8:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\Tornado\\Tornado\\Attack").GetFullPath(), "Hilda_Tornado_Attack");
		++Phase;
		break;
	case 9:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\Tornado\\Tornado\\Intro").GetFullPath(), "Hilda_Tornado_Intro");
		++Phase;
		break;
	case 10:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Taurus\\Idle").GetFullPath(), "Taurus_Idle");
		++Phase;
		break;
	case 11:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Taurus\\Attack\\Charge").GetFullPath(), "Taurus_Charge");
		++Phase;
		break;
	case 12:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Taurus\\Attack\\Attack").GetFullPath(), "Taurus_Attack");
		++Phase;
		break;
	case 13:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Taurus\\Constellation").GetFullPath(), "Taurus_Constellation");
		++Phase;
		break;
	case 14:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Sagittarius\\Sagittarius\\Lower\\Idle").GetFullPath(), "Sagittarius_Lower_Idle");
		++Phase;
		break;
	case 15:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Sagittarius\\Sagittarius\\Upper\\Idle").GetFullPath(), "Sagittarius_Upper_Idle");
		++Phase;
		break;
	case 16:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Sagittarius\\Sagittarius\\Upper\\Attack").GetFullPath(), "Sagittarius_Upper_Attack");
		++Phase;
		break;
	case 17:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Sagittarius\\Arrow\\Arrow").GetFullPath(), "Sagittarius_Arrow");
		++Phase;
		break;
	case 18:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Sagittarius\\Arrow\\AppearFX").GetFullPath(), "Sagittarius_AppearFX");
		++Phase;
		break;
	case 19:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Sagittarius\\Constellation").GetFullPath(), "Sagittarius_Constellation");
		++Phase;
		break;
	case 20:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Gemini\\Idle").GetFullPath(), "Gemini_Idle");
		++Phase;
		break;
	case 21:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Gemini\\Attack (A)").GetFullPath(), "Gemini_AttackA");
		++Phase;
		break;
	case 22:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Gemini\\Attack (B)").GetFullPath(), "Gemini_AttackB");
		++Phase;
		break;
	case 23:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Gemini\\Constellation").GetFullPath(), "Gemini_Constellation");
		++Phase;
		break;
	case 24:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Gemini\\Orb\\Idle\\Intro").GetFullPath(), "Orb_Idle_Intro");
		++Phase;
		break;
	case 25:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Gemini\\Orb\\Idle\\Loop").GetFullPath(), "Orb_Idle_Loop");
		++Phase;
		break;
	case 26:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Gemini\\Orb\\Idle\\Leave").GetFullPath(), "Orb_Idle_Leave");
		++Phase;
		break;
	case 27:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Gemini\\Orb\\Attack\\Intro").GetFullPath(), "Orb_Attack_Intro");
		++Phase;
		break;
	case 28:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Gemini\\Orb\\Attack\\Loop").GetFullPath(), "Orb_Attack_Loop");
		++Phase;
		break;
	case 29:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Gemini\\Orb\\Attack\\Leave").GetFullPath(), "Orb_Attack_Leave");
		++Phase;
		break;
	case 30:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Gemini\\Orb\\Attack\\FX\\Large").GetFullPath(), "Orb_Attack_Scatter");
		++Phase;
		break;
	case 31:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Gemini\\Orb\\Attack\\BulletStream").GetFullPath(), "Orb_Bullet");
		++Phase;
		break;
	case 32:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\TransitionToMoon\\Start").GetFullPath(), "Moon_Intro0");
		++Phase;
		break;
	case 33:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\TransitionToMoon\\BoilA").GetFullPath(), "Moon_Intro1");
		++Phase;
		break;
	case 34:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\TransitionToMoon\\Middle").GetFullPath(), "Moon_Intro2");
		++Phase;
		break;
	case 35:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\TransitionToMoon\\BoilB").GetFullPath(), "Moon_Intro3");
		++Phase;
		break;
	case 36:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\TransitionToMoon\\End").GetFullPath(), "Moon_Intro4");
		++Phase;
		break;
	case 37:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Idle").GetFullPath(), "Moon_Idle");
		++Phase;
		break;
	case 38:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Attack\\Intro").GetFullPath(), "Moon_Attack_Intro");
		++Phase;
		break;
	case 39:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Attack\\AttackIdle").GetFullPath(), "Moon_Attack");
		++Phase;
		break;
	case 40:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Attack\\Outtro").GetFullPath(), "Moon_Attack_Outtro");
		++Phase;
		break;
	case 41:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Death").GetFullPath(), "Moon_Death");
		++Phase;
		break;
	case 42:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Projectiles\\UFO\\Red").GetFullPath(), "Hilda_UFO_Red");
		++Phase;
		break;
	case 43:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Projectiles\\UFO\\Bronze").GetFullPath(), "Hilda_UFO_Bronze");
		++Phase;
		break;
	case 44:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Projectiles\\UFO\\Beam").GetFullPath(), "Hilda_UFO_Beam");
		++Phase;
		break;
	case 45:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\Idle\\Idle").GetFullPath(), "Cuphead_AirPlane_Origin_Idle");
		++Phase;
		break;
	case 46:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\Idle\\up").GetFullPath(), "Cuphead_AirPlane_Origin_Idleup");
		++Phase;
		break;
	case 47:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\Idle\\down").GetFullPath(), "Cuphead_AirPlane_Origin_Idledown");
		++Phase;
		break;
	case 48:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\Intros\\Regular").GetFullPath(), "Cuphead_AirPlane_Origin_intro");
		++Phase;
		break;
	case 49:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\Transicion\\transup").GetFullPath(), "Cuphead_AirPlane_Origin_transup");
		++Phase;
		break;
	case 50:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\Transicion\\transdown").GetFullPath(), "Cuphead_AirPlane_Origin_transdown");
		++Phase;
		break;
	case 51:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\Super\\Idle\\Idle").GetFullPath(), "Cuphead_AirPlane_Super_Idle");
		++Phase;
		break;
	case 52:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\Super\\Idle\\up").GetFullPath(), "Cuphead_AirPlane_Super_Idleup");
		++Phase;
		break;
	case 53:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\Super\\Idle\\down").GetFullPath(), "Cuphead_AirPlane_Super_Idledown");
		++Phase;
		break;
	case 54:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\Super\\intro").GetFullPath(), "Cuphead_AirPlane_Super_intro");
		++Phase;
		break;
	case 55:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\Super\\trans\\up").GetFullPath(), "Cuphead_AirPlane_Super_transup");
		++Phase;
		break;
	case 56:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\Super\\trans\\down").GetFullPath(), "Cuphead_AirPlane_Super_transdown");
		++Phase;
		break;
	case 57:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\Shrink\\idle\\Idle").GetFullPath(), "Cuphead_AirPlane_Shrink_Idle");
		++Phase;
		break;
	case 58:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\Shrink\\idle\\up").GetFullPath(), "Cuphead_AirPlane_Shrink_Idleup");
		++Phase;
		break;
	case 59:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\Shrink\\idle\\down").GetFullPath(), "Cuphead_AirPlane_Shrink_Idledown");
		++Phase;
		break;
	case 60:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\Shrink\\morph").GetFullPath(), "Cuphead_AirPlane_Shrink_intro");
		++Phase;
		break;
	case 61:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\Shrink\\trans\\up").GetFullPath(), "Cuphead_AirPlane_Shrink_transup");
		++Phase;
		break;
	case 62:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\Shrink\\trans\\down").GetFullPath(), "Cuphead_AirPlane_Shrink_transdown");
		++Phase;
		break;
	case 63:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\Parry").GetFullPath(), "Cuphead_AirPlane_Parry");
		++Phase;
		break;
	case 64:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\effect\\Spark").GetFullPath(), "Cuphead_AirPlane_Spark");
		++Phase;
		break;
	case 65:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Purple\\Idle").GetFullPath(), "BlimpEnemy_PurPle_Idle");
		++Phase;
		break;
	case 66:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Green\\Idle").GetFullPath(), "BlimpEnemy_Green_Idle");
		++Phase;
		break;
	case 67:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Purple\\Attack").GetFullPath(), "BlimpEnemy_Purple_Attack");
		++Phase;
		break;
	case 68:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Green\\Attack").GetFullPath(), "BlimpEnemy_Green_Attack");
		++Phase;
		break;
	case 69:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Purple\\Turn").GetFullPath(), "BlimpEnemy_Purple_Turn");
		++Phase;
		break;
	case 70:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Green\\Turn").GetFullPath(), "BlimpEnemy_Green_Turn");
		++Phase;
		break;
	case 71:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Green\\Pieces\\A").GetFullPath(), "BlimpEnemy_Green_Death_A");
		++Phase;
		break;
	case 72:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Green\\Pieces\\B").GetFullPath(), "BlimpEnemy_Green_Death_B");
		++Phase;
		break;
	case 73:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Green\\Pieces\\C").GetFullPath(), "BlimpEnemy_Green_Death_C");
		++Phase;
		break;
	case 74:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Green\\Pieces\\D").GetFullPath(), "BlimpEnemy_Green_Death_D");
		++Phase;
		break;
	case 75:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Green\\Pieces\\E").GetFullPath(), "BlimpEnemy_Green_Death_E");
		++Phase;
		break;
	case 76:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Green\\Pieces\\F").GetFullPath(), "BlimpEnemy_Green_Death_F");
		++Phase;
		break;
	case 77:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Purple\\Pieces\\A").GetFullPath(), "BlimpEnemy_Purple_Death_A");
		++Phase;
		break;
	case 78:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Purple\\Pieces\\B").GetFullPath(), "BlimpEnemy_Purple_Death_B");
		++Phase;
		break;
	case 79:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Purple\\Pieces\\C").GetFullPath(), "BlimpEnemy_Purple_Death_C");
		++Phase;
		break;
	case 80:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Purple\\Pieces\\D").GetFullPath(), "BlimpEnemy_Purple_Death_D");
		++Phase;
		break;
	case 81:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Purple\\Pieces\\E").GetFullPath(), "BlimpEnemy_Purple_Death_E");
		++Phase;
		break;
	case 82:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Purple\\Pieces\\F").GetFullPath(), "BlimpEnemy_Purple_Death_F");
		++Phase;
		break;
	case 83:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Explode (Death)\\Explode").GetFullPath(), "BlimpEnemy_Explode");
		++Phase;
		break;
	case 84:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Explode (Death)\\Spark").GetFullPath(), "BlimpEnemy_Spark");
		++Phase;
		break;

	case 85:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Sagittarius\\Arrow\\Star\\Idle").GetFullPath(), "Sagittarius_Star_Idle");
		++Phase;
		break;

	case 86:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Sagittarius\\Arrow\\Star\\Trail\\A").GetFullPath(), "Sagittarius_Star_Trail");
		++Phase;
		break;

	case 87:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Sagittarius\\Arrow\\Star\\Death").GetFullPath(), "Sagittarius_Star_Death");
		++Phase;
		break;

	case 88:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Projectiles\\Star\\A").GetFullPath(), "Moon_Star_A");
		++Phase;
		break;

	case 89:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Projectiles\\Star\\B").GetFullPath(), "Moon_Star_B");
		++Phase;
		break;

	case 90:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Projectiles\\Star\\C").GetFullPath(), "Moon_Star_C");
		++Phase;
		break;

	case 91:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Projectiles\\Star\\Pink").GetFullPath(), "Moon_Star_Pink");
		++Phase;
		break;

	case 92:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Projectiles\\Star\\IdleFX").GetFullPath(), "Moon_Star_IdleFX");
		++Phase;
		break;

	case 93:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Projectiles\\Star\\PinkFX").GetFullPath(), "Moon_Star_PinkFX");
		++Phase;
		break;

	case 94:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\ChangePhase\\ChangeBack").GetFullPath(), "Hilda_ChangeBack");
		++Phase;
		break;

	case 95:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\ChangePhase\\FX\\SmokeFX").GetFullPath(), "HildaChangePhaseDashSmoke");
		++Phase;
		break;

	case 96:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\bullet\\peashotFX").GetFullPath(), "peashotFX");
		++Phase;
		break;

	case 97:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\ChangePhase\\FX\\DashBackExplodeFX").GetFullPath(), "HildaChangePhaseDashBackExplode");
		++Phase;
		break;

	case 98:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\ChangePhase\\FX\\DashExplodeFX").GetFullPath(), "HildaChangePhaseDashExplode");
		++Phase;
		break;

	case 99:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\ChangePhase\\FX\\HildaChangeFX").GetFullPath(), "HildaChangeFX");
		++Phase;
		break;

	case 100:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\effect\\PlaneSmoke").GetFullPath(), "Cuphead_AirPlane_Smoke_Idle");
		++Phase;
		break;
	case 101:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\bullet\\peashot").GetFullPath(), "Cuphead_AirPlane_Bullet");
		++Phase;
		break;
	case 102:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Bullet\\A\\Bullet").GetFullPath(), "BlimpEnemy_BulletA");
		++Phase;
		break;
	case 103:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Bullet\\B\\Bullet").GetFullPath(), "BlimpEnemy_BulletB");
		++Phase;
		break;
	case 104:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Bullet\\C\\Bullet").GetFullPath(), "BlimpEnemy_BulletC");
		++Phase;
		break;
	case 105:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Bullet\\Pink\\A").GetFullPath(), "BlimpEnemy_BulletPinkA");
		++Phase;
		break;
	case 106:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Bullet\\Pink\\B").GetFullPath(), "BlimpEnemy_BulletPinkB");
		++Phase;
		break;
	case 107:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\effect\\Boom").GetFullPath(), "shmup_super_boom");
		++Phase;
		break;
	case 108:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\effect\\Explode").GetFullPath(), "shmup_super_explode");
		++Phase;
		break;

	case 109:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\effect\\Super_FX").GetFullPath(), "Super_FX");
		++Phase;
		break;

	case 110:
	{
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
		++Phase;
		break;
	}

	case 111:
	{
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
		else
		{
			GameEngineDirectory NewDir;
			NewDir.MoveParentToDirectory("ContentResources");
			NewDir.Move("ContentResources\\Texture\\PlayerUI\\HPBar");

			std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });
			for (size_t i = 0; i < File.size(); i++)
			{
				GameEngineTexture::ReLoad(File[i].GetFullPath());
			}
		}
		++Phase;
		break;
	}

	case 112:
	{
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
		++Phase;
		break;
	}

	case 113:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Cuphead_AirPlane\\Ghost").GetFullPath(), "Cuphead_AirPlane_Ghost");
		++Phase;
		break;

	case 114:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("TextUI\\Text_YouDied").GetFullPath(), "Text_YouDied");
		++Phase;
		break;

	case 115:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("TextUI\\Text_KO").GetFullPath(), "Text_KO");
		++Phase;
		break;

	case 116:
		++Phase;
		break;

	case 117:
		FEffect->FadeIn();
		++Phase;
		break;
	default:
		GameEngineCore::ChangeLevel("HildaBergLevel");
		NextLevel = CupheadLevel::NONE;
		break;
	}

}


void LoadingLevel::LoadStorySprite()
{
	switch (Phase)
	{
	case 0:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("story\\before\\Page1").GetFullPath(), "story1");
		++Phase;
		break;
	case 1:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("story\\before\\Page2").GetFullPath(), "story2");
		++Phase;
		break;
	case 2:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("story\\before\\Page3").GetFullPath(), "story3");
		++Phase;
		break;
	case 3:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("story\\before\\Page4").GetFullPath(), "story4");
		++Phase;
		break;
	case 4:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("story\\before\\Page5").GetFullPath(), "story5");
		++Phase;
		break;
	case 5:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("story\\before\\Page6").GetFullPath(), "story6");
		++Phase;
		break;
	case 6:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("story\\before\\Page7").GetFullPath(), "story7");
		++Phase;
		break;
	case 7:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("story\\before\\Page8").GetFullPath(), "story8");
		++Phase;
		break;
	case 8:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("story\\before\\Page9").GetFullPath(), "story9");
		++Phase;
		break;
	case 9:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("story\\before\\Page10").GetFullPath(), "story10");
		++Phase;
		break;
	case 10:
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("story\\before\\Page0").GetFullPath(), "story0");
		++Phase;
		break;
	default:
		GameEngineCore::ChangeLevel("StoryLevel");
		NextLevel = CupheadLevel::NONE;
		break;
	}
}
