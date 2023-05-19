#include "PrecompileHeader.h"
#include "LoadingLevel.h"
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineCore.h>

#include "LoadingBackGround.h"

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

	default:
		GameEngineCore::ChangeLevel("HildaBergLevel");
		break;
	}



















	//switch (Phase)
	//{

	//case 0:
	//{
	//	if (nullptr == GameEngineSprite::Find("Hilda_Intro"))
	//	{

	//		GameEngineDirectory NewDir;
	//		NewDir.MoveParentToDirectory("ContentResources");
	//		NewDir.Move("ContentResources\\Texture\\stage1\\Boss\\Hilda\\HildaBerg\\Normal");

	//		// intro
	//		GameEngineSprite::LoadFolder("Hilda_Intro", NewDir.GetPlusFileName("Intro\\Hilda").GetFullPath());
	//		// idle
	//		GameEngineSprite::LoadFolder("Hilda_Idle", NewDir.GetPlusFileName("Idle").GetFullPath());
	//		return;
	//	}
	//	if (nullptr == GameEngineSprite::Find("Hilda_Shoot"))
	//	{

	//		GameEngineDirectory NewDir;
	//		NewDir.MoveParentToDirectory("ContentResources");
	//		NewDir.Move("ContentResources\\Texture\\stage1\\Boss\\Hilda\\HildaBerg\\Normal");
	//		// shoot
	//		GameEngineSprite::LoadFolder("Hilda_Shoot", NewDir.GetPlusFileName("Laugh\\Hilda").GetFullPath());
	//		GameEngineSprite::LoadFolder("Hilda_Ha", NewDir.GetPlusFileName("Laugh\\Ha").GetFullPath());
	//		// Dash
	//		GameEngineSprite::LoadFolder("Hilda_Dash", NewDir.GetPlusFileName("ChangePhase\\Dash\\Dash").GetFullPath());
	//	}
	//	++Phase;
	//}
	//break;
	//case 1:
	//{
	//	if (nullptr == GameEngineSprite::Find("Hilda_DashBack"))
	//	{

	//		GameEngineDirectory NewDir;
	//		NewDir.MoveParentToDirectory("ContentResources");
	//		NewDir.Move("ContentResources\\Texture\\stage1\\Boss\\Hilda\\HildaBerg\\Normal");


	//		// DashBack
	//		GameEngineSprite::LoadFolder("Hilda_DashBack", NewDir.GetPlusFileName("ChangePhase\\Dash\\DashBack").GetFullPath());
	//		// Summon
	//		GameEngineSprite::LoadFolder("Hilda_Summon", NewDir.GetPlusFileName("ChangePhase\\Summon").GetFullPath());
	//		return;
	//	}
	//	if (nullptr == GameEngineSprite::Find("Hilda_Tornado"))
	//	{

	//		GameEngineDirectory NewDir;
	//		NewDir.MoveParentToDirectory("ContentResources");
	//		NewDir.Move("ContentResources\\Texture\\stage1\\Boss\\Hilda\\HildaBerg\\Normal");

	//		// Tornato
	//		GameEngineSprite::LoadFolder("Hilda_Tornado", NewDir.GetPlusFileName("Tornado\\Hilda").GetFullPath());
	//		GameEngineSprite::LoadFolder("Hilda_Tornado_Attack", NewDir.GetPlusFileName("Tornado\\Tornado\\Attack").GetFullPath());
	//		GameEngineSprite::LoadFolder("Hilda_Tornado_Intro", NewDir.GetPlusFileName("Tornado\\Tornado\\Intro").GetFullPath());

	//	}
	//	++Phase;
	//}
	//break;
	//case 2:
	//{
	//	// Taurus
	//	if (nullptr == GameEngineSprite::Find("Taurus_Idle"))
	//	{

	//		GameEngineDirectory NewDir;
	//		NewDir.MoveParentToDirectory("ContentResources");
	//		NewDir.Move("ContentResources\\Texture\\stage1\\Boss\\Hilda\\Taurus");

	//		GameEngineSprite::LoadFolder("Taurus_Idle", NewDir.GetPlusFileName("Idle").GetFullPath());
	//		GameEngineSprite::LoadFolder("Taurus_Charge", NewDir.GetPlusFileName("Attack\\Charge").GetFullPath());
	//		return;
	//	}
	//	if (nullptr == GameEngineSprite::Find("Taurus_Attack"))
	//	{

	//		GameEngineDirectory NewDir;
	//		NewDir.MoveParentToDirectory("ContentResources");
	//		NewDir.Move("ContentResources\\Texture\\stage1\\Boss\\Hilda\\Taurus");
	//		GameEngineSprite::LoadFolder("Taurus_Attack", NewDir.GetPlusFileName("Attack\\Attack").GetFullPath());
	//		GameEngineSprite::LoadFolder("Taurus_Constellation", NewDir.GetPlusFileName("Constellation").GetFullPath());

	//	}
	//	++Phase;
	//}
	//break;
	//case 3:
	//{
	//	// sagittarius
	//	if (nullptr == GameEngineSprite::Find("Sagittarius_Lower_Idle"))
	//	{

	//		GameEngineDirectory NewDir;
	//		NewDir.MoveParentToDirectory("ContentResources");
	//		NewDir.Move("ContentResources\\Texture\\stage1\\Boss\\Hilda\\Sagittarius");


	//		GameEngineSprite::LoadFolder("Sagittarius_Lower_Idle", NewDir.GetPlusFileName("Sagittarius\\Lower\\Idle").GetFullPath());
	//		GameEngineSprite::LoadFolder("Sagittarius_Upper_Idle", NewDir.GetPlusFileName("Sagittarius\\Upper\\Idle").GetFullPath());
	//		GameEngineSprite::LoadFolder("Sagittarius_Upper_Attack", NewDir.GetPlusFileName("Sagittarius\\Upper\\Attack").GetFullPath());
	//		return;
	//	}
	//	if (nullptr == GameEngineSprite::Find("Sagittarius_Arrow"))
	//	{

	//		GameEngineDirectory NewDir;
	//		NewDir.MoveParentToDirectory("ContentResources");
	//		NewDir.Move("ContentResources\\Texture\\stage1\\Boss\\Hilda\\Sagittarius");

	//		GameEngineSprite::LoadFolder("Sagittarius_Arrow", NewDir.GetPlusFileName("Arrow\\Arrow").GetFullPath());
	//		GameEngineSprite::LoadFolder("Sagittarius_AppearFX", NewDir.GetPlusFileName("Arrow\\AppearFX").GetFullPath());
	//		GameEngineSprite::LoadFolder("Sagittarius_Constellation", NewDir.GetPlusFileName("Constellation").GetFullPath());

	//	}
	//	++Phase;
	//}
	//break;
	//case 4:
	//{
	//	// Gemini
	//	if (nullptr == GameEngineSprite::Find("Gemini_Idle"))
	//	{

	//		GameEngineDirectory NewDir;
	//		NewDir.MoveParentToDirectory("ContentResources");
	//		NewDir.Move("ContentResources\\Texture\\stage1\\Boss\\Hilda\\Gemini");

	//		GameEngineSprite::LoadFolder("Gemini_Idle", NewDir.GetPlusFileName("Idle").GetFullPath());
	//		GameEngineSprite::LoadFolder("Gemini_AttackA", NewDir.GetPlusFileName("Attack (A)").GetFullPath());
	//		return;

	//	}
	//	if (nullptr == GameEngineSprite::Find("Gemini_AttackB"))
	//	{

	//		GameEngineDirectory NewDir;
	//		NewDir.MoveParentToDirectory("ContentResources");
	//		NewDir.Move("ContentResources\\Texture\\stage1\\Boss\\Hilda\\Gemini");

	//		GameEngineSprite::LoadFolder("Gemini_AttackB", NewDir.GetPlusFileName("Attack (B)").GetFullPath());
	//		GameEngineSprite::LoadFolder("Gemini_Constellation", NewDir.GetPlusFileName("Constellation").GetFullPath());

	//	}
	//	++Phase;
	//}
	//break;
	//case 5:
	//{
	//	if (nullptr == GameEngineSprite::Find("Orb_Idle_Intro"))
	//	{

	//		GameEngineDirectory NewDir;
	//		NewDir.MoveParentToDirectory("ContentResources");
	//		NewDir.Move("ContentResources\\Texture\\stage1\\Boss\\Hilda\\Gemini\\Orb");

	//		// idle
	//		GameEngineSprite::LoadFolder("Orb_Idle_Intro", NewDir.GetPlusFileName("Idle\\Intro").GetFullPath());
	//		GameEngineSprite::LoadFolder("Orb_Idle_Loop", NewDir.GetPlusFileName("Idle\\Loop").GetFullPath());
	//		GameEngineSprite::LoadFolder("Orb_Idle_Leave", NewDir.GetPlusFileName("Idle\\Leave").GetFullPath());
	//		return;
	//	}
	//	if (nullptr == GameEngineSprite::Find("Orb_Attack_Intro"))
	//	{

	//		GameEngineDirectory NewDir;
	//		NewDir.MoveParentToDirectory("ContentResources");
	//		NewDir.Move("ContentResources\\Texture\\stage1\\Boss\\Hilda\\Gemini\\Orb");

	//		// attack																											
	//		GameEngineSprite::LoadFolder("Orb_Attack_Intro", NewDir.GetPlusFileName("Attack\\Intro").GetFullPath());
	//		GameEngineSprite::LoadFolder("Orb_Attack_Loop", NewDir.GetPlusFileName("Attack\\Loop").GetFullPath());
	//		GameEngineSprite::LoadFolder("Orb_Attack_Leave", NewDir.GetPlusFileName("Attack\\Leave").GetFullPath());

	//		// scatter																										 
	//		GameEngineSprite::LoadFolder("Orb_Attack_Scatter", NewDir.GetPlusFileName("Attack\\FX\\Large").GetFullPath());

	//	}
	//	++Phase;
	//}
	//break;
	//case 6:
	//{

	//	if (nullptr == GameEngineSprite::Find("Orb_Bullet"))
	//	{

	//		GameEngineDirectory NewDir;
	//		NewDir.MoveParentToDirectory("ContentResources");
	//		NewDir.Move("ContentResources\\Texture\\stage1\\Boss\\Hilda\\Gemini\\Orb\\Attack");

	//		GameEngineSprite::LoadFolder("Orb_Bullet", NewDir.GetPlusFileName("BulletStream").GetFullPath());


	//	}
	//	++Phase;
	//}
	//break;
	//case 7:
	//{
	//	// Moon
	//	if (nullptr == GameEngineSprite::Find("Moon_Intro0"))
	//	{

	//		GameEngineDirectory NewDir;
	//		NewDir.MoveParentToDirectory("ContentResources");
	//		NewDir.Move("ContentResources\\Texture\\stage1\\Boss\\Hilda\\Moon");


	//		GameEngineSprite::LoadFolder("Moon_Intro0", NewDir.GetPlusFileName("TransitionToMoon\\Start").GetFullPath());
	//		GameEngineSprite::LoadFolder("Moon_Intro1", NewDir.GetPlusFileName("TransitionToMoon\\BoilA").GetFullPath());
	//		GameEngineSprite::LoadFolder("Moon_Intro2", NewDir.GetPlusFileName("TransitionToMoon\\Middle").GetFullPath());
	//		GameEngineSprite::LoadFolder("Moon_Intro3", NewDir.GetPlusFileName("TransitionToMoon\\BoilB").GetFullPath());
	//		GameEngineSprite::LoadFolder("Moon_Intro4", NewDir.GetPlusFileName("TransitionToMoon\\End").GetFullPath());
	//	}
	//	++Phase;
	//}
	//break;
	//case 8:
	//{
	//	if (nullptr == GameEngineSprite::Find("Moon_Idle"))
	//	{

	//		GameEngineDirectory NewDir;
	//		NewDir.MoveParentToDirectory("ContentResources");
	//		NewDir.Move("ContentResources\\Texture\\stage1\\Boss\\Hilda\\Moon");

	//		GameEngineSprite::LoadFolder("Moon_Idle", NewDir.GetPlusFileName("Idle").GetFullPath());
	//		GameEngineSprite::LoadFolder("Moon_Attack_Intro", NewDir.GetPlusFileName("Attack\\Intro").GetFullPath());
	//		GameEngineSprite::LoadFolder("Moon_Attack", NewDir.GetPlusFileName("Attack\\AttackIdle").GetFullPath());
	//		GameEngineSprite::LoadFolder("Moon_Attack_Outtro", NewDir.GetPlusFileName("Attack\\Outtro").GetFullPath());
	//		GameEngineSprite::LoadFolder("Moon_Death", NewDir.GetPlusFileName("Death").GetFullPath());

	//	}
	//	++Phase;
	//}
	//break;
	//case 9:
	//{
	//	if (nullptr == GameEngineSprite::Find("Hilda_UFO_Red"))
	//	{
	//		GameEngineDirectory Dir;
	//		Dir.MoveParentToDirectory("ContentResources");
	//		Dir.Move("ContentResources\\Texture\\stage1\\Boss\\Hilda\\Moon\\Projectiles\\UFO");

	//		GameEngineSprite::LoadFolder("Hilda_UFO_Red", Dir.GetPlusFileName("Red").GetFullPath());
	//		GameEngineSprite::LoadFolder("Hilda_UFO_Bronze", Dir.GetPlusFileName("Bronze").GetFullPath());
	//		GameEngineSprite::LoadFolder("Hilda_UFO_Beam", Dir.GetPlusFileName("Beam").GetFullPath());
	//	}
	//	++Phase;
	//}
	//break;
	//case 10:
	//{
	//	if (nullptr == GameEngineSprite::Find("Cuphead_AirPlane_Origin_Idle"))
	//	{

	//		GameEngineDirectory NewDir;
	//		NewDir.MoveParentToDirectory("ContentResources");
	//		NewDir.Move("ContentResources\\Texture\\Cuphead_AirPlane");



	//		// Origin
	//		// idle

	//		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Origin_Idle", NewDir.GetPlusFileName("Idle\\Idle").GetFullPath());
	//		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Origin_Idleup", NewDir.GetPlusFileName("Idle\\up").GetFullPath());
	//		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Origin_Idledown", NewDir.GetPlusFileName("Idle\\down").GetFullPath());
	//		return;
	//	}
	//	if (nullptr == GameEngineSprite::Find("Cuphead_AirPlane_Origin_intro"))
	//	{
	//		GameEngineDirectory NewDir;
	//		NewDir.MoveParentToDirectory("ContentResources");
	//		NewDir.Move("ContentResources\\Texture\\Cuphead_AirPlane");
	//		// intro
	//		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Origin_intro", NewDir.GetPlusFileName("Intros\\Regular").GetFullPath());

	//		// trans
	//		//NewDir.Move("..\\Transicion");
	//		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Origin_transup", NewDir.GetPlusFileName("Transicion\\transup").GetFullPath());
	//		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Origin_transdown", NewDir.GetPlusFileName("Transicion\\transdown").GetFullPath());
	//	}
	//	++Phase;
	//}
	//break;
	//case 11:
	//{

	//	if (nullptr == GameEngineSprite::Find("Cuphead_AirPlane_Super_Idle"))
	//	{

	//		GameEngineDirectory NewDir;
	//		NewDir.MoveParentToDirectory("ContentResources");
	//		NewDir.Move("ContentResources\\Texture\\Cuphead_AirPlane");



	//		// Super
	//		// idle
	//		//NewDir.Move("..\\Super\\Idle");
	//		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Super_Idle", NewDir.GetPlusFileName("Super\\Idle\\Idle").GetFullPath());
	//		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Super_Idleup", NewDir.GetPlusFileName("Super\\Idle\\up").GetFullPath());
	//		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Super_Idledown", NewDir.GetPlusFileName("Super\\Idle\\down").GetFullPath());
	//		return;
	//	}
	//	if (nullptr == GameEngineSprite::Find("Cuphead_AirPlane_Super_intro"))
	//	{
	//		GameEngineDirectory NewDir;
	//		NewDir.MoveParentToDirectory("ContentResources");
	//		NewDir.Move("ContentResources\\Texture\\Cuphead_AirPlane");
	//		// intro
	//		//NewDir.MoveParent();
	//		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Super_intro", NewDir.GetPlusFileName("Super\\intro").GetFullPath());

	//		// trans
	//		//NewDir.Move("trans");
	//		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Super_transup", NewDir.GetPlusFileName("Super\\trans\\up").GetFullPath());
	//		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Super_transdown", NewDir.GetPlusFileName("Super\\trans\\down").GetFullPath());
	//	}
	//	++Phase;
	//}
	//break;
	//case 12:
	//{
	//	if (nullptr == GameEngineSprite::Find("Cuphead_AirPlane_Shrink_Idle"))
	//	{

	//		GameEngineDirectory NewDir;
	//		NewDir.MoveParentToDirectory("ContentResources");
	//		NewDir.Move("ContentResources\\Texture\\Cuphead_AirPlane");



	//		// Shrink
	//		// idle
	//		//NewDir.Move("..\\..\\Shrink\\idle");
	//		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Shrink_Idle", NewDir.GetPlusFileName("Shrink\\idle\\Idle").GetFullPath());
	//		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Shrink_Idleup", NewDir.GetPlusFileName("Shrink\\idle\\up").GetFullPath());
	//		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Shrink_Idledown", NewDir.GetPlusFileName("Shrink\\idle\\down").GetFullPath());
	//		return;
	//	}
	//	if (nullptr == GameEngineSprite::Find("Cuphead_AirPlane_Shrink_intro"))
	//	{
	//		GameEngineDirectory NewDir;
	//		NewDir.MoveParentToDirectory("ContentResources");
	//		NewDir.Move("ContentResources\\Texture\\Cuphead_AirPlane");
	//		// intro
	//		//NewDir.MoveParent();
	//		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Shrink_intro", NewDir.GetPlusFileName("Shrink\\morph").GetFullPath());

	//		// trans
	//		//NewDir.Move("trans");
	//		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Shrink_transup", NewDir.GetPlusFileName("Shrink\\trans\\up").GetFullPath());
	//		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Shrink_transdown", NewDir.GetPlusFileName("Shrink\\trans\\down").GetFullPath());


	//		//parry
	//		//NewDir.Move("..\\..\\");
	//		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Parry", NewDir.GetPlusFileName("Parry").GetFullPath());
	//	}
	//	++Phase;
	//}
	//break;
	//case 13:
	//{
	//	if (nullptr == GameEngineSprite::Find("Cuphead_AirPlane_Spark"))
	//	{
	//		GameEngineDirectory NewDir;
	//		NewDir.MoveParentToDirectory("ContentResources");
	//		NewDir.Move("ContentResources");
	//		NewDir.Move("Texture");
	//		NewDir.Move("Cuphead_AirPlane\\effect");

	//		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Spark", NewDir.GetPlusFileName("Spark").GetFullPath());
	//	}
	//	++Phase;
	//}
	//break;
	//case 14:
	//	GameEngineCore::ChangeLevel("HildaBergLevel");
	//	break;
	//default:
	//	break;
	//}
}