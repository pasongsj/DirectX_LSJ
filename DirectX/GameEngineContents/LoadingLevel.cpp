#include "PrecompileHeader.h"
#include "LoadingLevel.h"
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineCore.h>

#include "LoadingBackGround.h"
#include "FadeEffect.h"

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

	FEffect = GetLastTarget()->CreateEffect<FadeEffect>();

}

void LoadingLevel::Update(float _DeltaTime)
{
	LoadHildaSprite();
}

void LoadingLevel::LevelChangeStart()
{
	CreateActor<LoadingBackGround>(CupHeadActorOrder::BackGround);

	Dir.MoveParentToDirectory("ContentResources");
	Dir.Move("ContentResources\\Texture");
}

void LoadingLevel::LevelChangeEnd()
{

}

void LoadingLevel::LoadHildaSprite()
{
	switch (Phase)
	{
	case 0:
		// intro
		GameEngineSprite::LoadFolder("Hilda_Intro", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\Intro\\Hilda").GetFullPath());
		++Phase;
		break;
	case 1:
		// idle
		GameEngineSprite::LoadFolder("Hilda_Idle", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\Idle").GetFullPath());

		++Phase;
		break;
	case 2:
		// shoot
		GameEngineSprite::LoadFolder("Hilda_Shoot", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\Laugh\\Hilda").GetFullPath());
		++Phase;
		break;
	case 3:
		GameEngineSprite::LoadFolder("Hilda_Ha", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\Laugh\\Ha").GetFullPath());
		++Phase;
		break;
	case 4:
		// Dash
		GameEngineSprite::LoadFolder("Hilda_Dash", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\ChangePhase\\Dash\\Dash").GetFullPath());
		++Phase;
		break;
	case 5:


		// DashBack
		GameEngineSprite::LoadFolder("Hilda_DashBack", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\ChangePhase\\Dash\\DashBack").GetFullPath());
		++Phase;
		break;
	case 6:
		// Summon
		GameEngineSprite::LoadFolder("Hilda_Summon", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\ChangePhase\\Summon").GetFullPath());
		++Phase;
		break;
	case 7:
		// Tornato
		GameEngineSprite::LoadFolder("Hilda_Tornado", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\Tornado\\Hilda").GetFullPath());
		++Phase;
		break;
	case 8:
		GameEngineSprite::LoadFolder("Hilda_Tornado_Attack", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\Tornado\\Tornado\\Attack").GetFullPath());
		++Phase;
		break;
	case 9:
		GameEngineSprite::LoadFolder("Hilda_Tornado_Intro", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\Tornado\\Tornado\\Intro").GetFullPath());
		++Phase;
		break;
	case 10:



		GameEngineSprite::LoadFolder("Taurus_Idle", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Taurus\\Idle").GetFullPath());
		++Phase;
		break;
	case 11:
		GameEngineSprite::LoadFolder("Taurus_Charge", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Taurus\\Attack\\Charge").GetFullPath());
		++Phase;
		break;
	case 12:

		GameEngineSprite::LoadFolder("Taurus_Attack", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Taurus\\Attack\\Attack").GetFullPath());
		++Phase;
		break;
	case 13:
		GameEngineSprite::LoadFolder("Taurus_Constellation", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Taurus\\Constellation").GetFullPath());

		++Phase;
		break;
	case 14:


		GameEngineSprite::LoadFolder("Sagittarius_Lower_Idle", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Sagittarius\\Sagittarius\\Lower\\Idle").GetFullPath());
		++Phase;
		break;
	case 15:
		GameEngineSprite::LoadFolder("Sagittarius_Upper_Idle", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Sagittarius\\Sagittarius\\Upper\\Idle").GetFullPath());
		++Phase;
		break;
	case 16:
		GameEngineSprite::LoadFolder("Sagittarius_Upper_Attack", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Sagittarius\\Sagittarius\\Upper\\Attack").GetFullPath());
		++Phase;
		break;
	case 17:


		GameEngineSprite::LoadFolder("Sagittarius_Arrow", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Sagittarius\\Arrow\\Arrow").GetFullPath());
		++Phase;
		break;
	case 18:
		GameEngineSprite::LoadFolder("Sagittarius_AppearFX", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Sagittarius\\Arrow\\AppearFX").GetFullPath());
		++Phase;
		break;
	case 19:
		GameEngineSprite::LoadFolder("Sagittarius_Constellation", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Sagittarius\\Constellation").GetFullPath());
		++Phase;
		break;
	case 20:

		GameEngineSprite::LoadFolder("Gemini_Idle", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Gemini\\Idle").GetFullPath());
		++Phase;
		break;
	case 21:
		GameEngineSprite::LoadFolder("Gemini_AttackA", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Gemini\\Attack (A)").GetFullPath());
		++Phase;
		break;
	case 22:

		GameEngineSprite::LoadFolder("Gemini_AttackB", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Gemini\\Attack (B)").GetFullPath());
		++Phase;
		break;
	case 23:
		GameEngineSprite::LoadFolder("Gemini_Constellation", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Gemini\\Constellation").GetFullPath());
		++Phase;
		break;
	case 24:


		// idle
		GameEngineSprite::LoadFolder("Orb_Idle_Intro", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Gemini\\Orb\\Idle\\Intro").GetFullPath());
		++Phase;
		break;
	case 25:
		GameEngineSprite::LoadFolder("Orb_Idle_Loop", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Gemini\\Orb\\Idle\\Loop").GetFullPath());
		++Phase;
		break;
	case 26:
		GameEngineSprite::LoadFolder("Orb_Idle_Leave", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Gemini\\Orb\\Idle\\Leave").GetFullPath());
		++Phase;
		break;
	case 27:

		// attack																											
		GameEngineSprite::LoadFolder("Orb_Attack_Intro", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Gemini\\Orb\\Attack\\Intro").GetFullPath());
		++Phase;
		break;
	case 28:
		GameEngineSprite::LoadFolder("Orb_Attack_Loop", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Gemini\\Orb\\Attack\\Loop").GetFullPath());
		++Phase;
		break;
	case 29:
		GameEngineSprite::LoadFolder("Orb_Attack_Leave", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Gemini\\Orb\\Attack\\Leave").GetFullPath());
		++Phase;
		break;
	case 30:

		// scatter																										 
		GameEngineSprite::LoadFolder("Orb_Attack_Scatter", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Gemini\\Orb\\Attack\\FX\\Large").GetFullPath());
		++Phase;
		break;
	case 31:



		GameEngineSprite::LoadFolder("Orb_Bullet", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Gemini\\Orb\\Attack\\BulletStream").GetFullPath());

		++Phase;
		break;
	case 32:


		GameEngineSprite::LoadFolder("Moon_Intro0", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\TransitionToMoon\\Start").GetFullPath());
		++Phase;
		break;
	case 33:
		GameEngineSprite::LoadFolder("Moon_Intro1", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\TransitionToMoon\\BoilA").GetFullPath());
		++Phase;
		break;
	case 34:
		GameEngineSprite::LoadFolder("Moon_Intro2", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\TransitionToMoon\\Middle").GetFullPath());
		++Phase;
		break;
	case 35:
		GameEngineSprite::LoadFolder("Moon_Intro3", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\TransitionToMoon\\BoilB").GetFullPath());
		++Phase;
		break;
	case 36:
		GameEngineSprite::LoadFolder("Moon_Intro4", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\TransitionToMoon\\End").GetFullPath());

		++Phase;
		break;
	case 37:

		GameEngineSprite::LoadFolder("Moon_Idle", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Idle").GetFullPath());
		++Phase;
		break;
	case 38:
		GameEngineSprite::LoadFolder("Moon_Attack_Intro", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Attack\\Intro").GetFullPath());
		++Phase;
		break;
	case 39:
		GameEngineSprite::LoadFolder("Moon_Attack", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Attack\\AttackIdle").GetFullPath());
		++Phase;
		break;
	case 40:
		GameEngineSprite::LoadFolder("Moon_Attack_Outtro", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Attack\\Outtro").GetFullPath());
		++Phase;
		break;
	case 41:
		GameEngineSprite::LoadFolder("Moon_Death", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Death").GetFullPath());
		++Phase;
		break;
	case 42:


		GameEngineSprite::LoadFolder("Hilda_UFO_Red", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Projectiles\\UFO\\Red").GetFullPath());
		++Phase;
		break;
	case 43:
		GameEngineSprite::LoadFolder("Hilda_UFO_Bronze", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Projectiles\\UFO\\Bronze").GetFullPath());
		++Phase;
		break;
	case 44:
		GameEngineSprite::LoadFolder("Hilda_UFO_Beam", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Projectiles\\UFO\\Beam").GetFullPath());
		++Phase;
		break;
	case 45:



		// Origin
		// idle

		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Origin_Idle", Dir.GetPlusFileName("Cuphead_AirPlane\\Idle\\Idle").GetFullPath());
		++Phase;
		break;
	case 46:
		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Origin_Idleup", Dir.GetPlusFileName("Cuphead_AirPlane\\Idle\\up").GetFullPath());
		++Phase;
		break;
	case 47:
		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Origin_Idledown", Dir.GetPlusFileName("Cuphead_AirPlane\\Idle\\down").GetFullPath());
		++Phase;
		break;
	case 48:


		// intro
		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Origin_intro", Dir.GetPlusFileName("Cuphead_AirPlane\\Intros\\Regular").GetFullPath());
		++Phase;
		break;
	case 49:

		// trans
		//Dir.Move("..\\Transicion");
		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Origin_transup", Dir.GetPlusFileName("Cuphead_AirPlane\\Transicion\\transup").GetFullPath());
		++Phase;
		break;
	case 50:
		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Origin_transdown", Dir.GetPlusFileName("Cuphead_AirPlane\\Transicion\\transdown").GetFullPath());
		++Phase;
		break;
	case 51:



		// Super
		// idle
		//Dir.Move("..\\Super\\Idle");
		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Super_Idle", Dir.GetPlusFileName("Cuphead_AirPlane\\Super\\Idle\\Idle").GetFullPath());
		++Phase;
		break;
	case 52:
		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Super_Idleup", Dir.GetPlusFileName("Cuphead_AirPlane\\Super\\Idle\\up").GetFullPath());
		++Phase;
		break;
	case 53:
		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Super_Idledown", Dir.GetPlusFileName("Cuphead_AirPlane\\Super\\Idle\\down").GetFullPath());
		++Phase;
		break;
	case 54:
		// intro
		//Dir.MoveParent();
		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Super_intro", Dir.GetPlusFileName("Cuphead_AirPlane\\Super\\intro").GetFullPath());

		++Phase;
		break;
	case 55:
		// trans
		//Dir.Move("trans");
		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Super_transup", Dir.GetPlusFileName("Cuphead_AirPlane\\Super\\trans\\up").GetFullPath());
		++Phase;
		break;
	case 56:
		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Super_transdown", Dir.GetPlusFileName("Cuphead_AirPlane\\Super\\trans\\down").GetFullPath());
		++Phase;
		break;
	case 57:



		// Shrink
		// idle
		//Dir.Move("..\\..\\Shrink\\idle");
		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Shrink_Idle", Dir.GetPlusFileName("Cuphead_AirPlane\\Shrink\\idle\\Idle").GetFullPath());
		++Phase;
		break;
	case 58:
		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Shrink_Idleup", Dir.GetPlusFileName("Cuphead_AirPlane\\Shrink\\idle\\up").GetFullPath());
		++Phase;
		break;
	case 59:
		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Shrink_Idledown", Dir.GetPlusFileName("Cuphead_AirPlane\\Shrink\\idle\\down").GetFullPath());
		++Phase;
		break;
	case 60:

		// intro
		//Dir.MoveParent();
		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Shrink_intro", Dir.GetPlusFileName("Cuphead_AirPlane\\Shrink\\morph").GetFullPath());
		++Phase;
		break;
	case 61:
		// trans
		//Dir.Move("trans");
		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Shrink_transup", Dir.GetPlusFileName("Cuphead_AirPlane\\Shrink\\trans\\up").GetFullPath());
		++Phase;
		break;
	case 62:
		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Shrink_transdown", Dir.GetPlusFileName("Cuphead_AirPlane\\Shrink\\trans\\down").GetFullPath());
		++Phase;
		break;
	case 63:


		//parry
		//Dir.Move("..\\..\\");
		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Parry", Dir.GetPlusFileName("Cuphead_AirPlane\\Parry").GetFullPath());
		++Phase;
		break;
	case 64:


		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Spark", Dir.GetPlusFileName("Cuphead_AirPlane\\effect\\Spark").GetFullPath());
		++Phase;
		break;
	case 65:
		GameEngineSprite::LoadFolder("BlimpEnemy_PurPle_Idle", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Purple\\Idle").GetFullPath());
		++Phase;
		break;
	case 66:
		GameEngineSprite::LoadFolder("BlimpEnemy_Green_Idle", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Green\\Idle").GetFullPath());
		++Phase;
		break;
	case 67:
		GameEngineSprite::LoadFolder("BlimpEnemy_Purple_Attack", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Purple\\Attack").GetFullPath());
		++Phase;
		break;
	case 68:
		GameEngineSprite::LoadFolder("BlimpEnemy_Green_Attack", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Green\\Attack").GetFullPath());
		++Phase;
		break;
	case 69:
		GameEngineSprite::LoadFolder("BlimpEnemy_Purple_Turn", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Purple\\Turn").GetFullPath());
		++Phase;
		break;
	case 70:
		GameEngineSprite::LoadFolder("BlimpEnemy_Green_Turn", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Green\\Turn").GetFullPath());
		++Phase;
		break;
	case 71:
		GameEngineSprite::LoadFolder("BlimpEnemy_Green_Death_A", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Green\\Pieces\\A").GetFullPath());
		++Phase;
		break;
	case 72:
		GameEngineSprite::LoadFolder("BlimpEnemy_Green_Death_B", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Green\\Pieces\\B").GetFullPath());
		++Phase;
		break;
	case 73:
		GameEngineSprite::LoadFolder("BlimpEnemy_Green_Death_C", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Green\\Pieces\\C").GetFullPath());
		++Phase;
		break;
	case 74:
		GameEngineSprite::LoadFolder("BlimpEnemy_Green_Death_D", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Green\\Pieces\\D").GetFullPath());
		++Phase;
		break;
	case 75:
		GameEngineSprite::LoadFolder("BlimpEnemy_Green_Death_E", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Green\\Pieces\\E").GetFullPath());
		++Phase;
		break;
	case 76:
		GameEngineSprite::LoadFolder("BlimpEnemy_Green_Death_F", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Green\\Pieces\\F").GetFullPath());
		++Phase;
		break;
	case 77:
		GameEngineSprite::LoadFolder("BlimpEnemy_Purple_Death_A", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Purple\\Pieces\\A").GetFullPath());
		++Phase;
		break;
	case 78:
		GameEngineSprite::LoadFolder("BlimpEnemy_Purple_Death_B", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Purple\\Pieces\\B").GetFullPath());
		++Phase;
		break;
	case 79:
		GameEngineSprite::LoadFolder("BlimpEnemy_Purple_Death_C", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Purple\\Pieces\\C").GetFullPath());
		++Phase;
		break;
	case 80:
		GameEngineSprite::LoadFolder("BlimpEnemy_Purple_Death_D", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Purple\\Pieces\\D").GetFullPath());
		++Phase;
		break;
	case 81:
		GameEngineSprite::LoadFolder("BlimpEnemy_Purple_Death_E", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Purple\\Pieces\\E").GetFullPath());
		++Phase;
		break;
	case 82:
		GameEngineSprite::LoadFolder("BlimpEnemy_Purple_Death_F", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Purple\\Pieces\\F").GetFullPath());
		++Phase;
		break;
	case 83:
		GameEngineSprite::LoadFolder("BlimpEnemy_Explode", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Explode (Death)\\Explode").GetFullPath());
		++Phase;
		break;
	case 84:
		GameEngineSprite::LoadFolder("BlimpEnemy_Spark", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Explode (Death)\\Spark").GetFullPath());
		++Phase;
		break;

	case 85:
		GameEngineSprite::LoadFolder("Sagittarius_Star_Idle", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Sagittarius\\Arrow\\Star\\Idle").GetFullPath());
		++Phase;
		break;

	case 86:
		GameEngineSprite::LoadFolder("Sagittarius_Star_Trail", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Sagittarius\\Arrow\\Star\\Trail\\A").GetFullPath());
		++Phase;
		break;

	case 87:
		GameEngineSprite::LoadFolder("Sagittarius_Star_Death", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Sagittarius\\Arrow\\Star\\Death").GetFullPath());
		++Phase;
		break;

	case 88:
		GameEngineSprite::LoadFolder("Moon_Star_A", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Projectiles\\Star\\A").GetFullPath());
		++Phase;
		break;

	case 89:
		GameEngineSprite::LoadFolder("Moon_Star_B", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Projectiles\\Star\\B").GetFullPath());
		++Phase;
		break;

	case 90:
		GameEngineSprite::LoadFolder("Moon_Star_C", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Projectiles\\Star\\C").GetFullPath());
		++Phase;
		break;

	case 91:
		GameEngineSprite::LoadFolder("Moon_Star_Pink", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Projectiles\\Star\\Pink").GetFullPath());
		++Phase;
		break;

	case 92:
		GameEngineSprite::LoadFolder("Moon_Star_IdleFX", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Projectiles\\Star\\IdleFX").GetFullPath());
		++Phase;
		break;

	case 93:
		GameEngineSprite::LoadFolder("Moon_Star_PinkFX", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Projectiles\\Star\\PinkFX").GetFullPath());
		++Phase;
		break;

	case 94:
		FEffect->FadeIn();
		++Phase;
		break;
	default:
		GameEngineCore::ChangeLevel("HildaBergLevel");
		break;
	}



	




}