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


	if (nullptr == FEffect)
	{
		FEffect = GetLastTarget()->CreateEffect<FadeEffect>();
	}

}

void LoadingLevel::Update(float _DeltaTime)
{
	if (true == isEnd)
	{
		return;
	}
	if (CupheadLevel::HILDA == Level)
	{
		LoadHildaSprite();
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
		if (nullptr != GameEngineSprite::Find("Hilda_Intro"))
		{
			GameEngineSprite::ReLoad("Hilda_Intro");
		}
		else
		{
			GameEngineSprite::LoadFolder("Hilda_Intro", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\Intro\\Hilda").GetFullPath());
		}
		++Phase;
		break;
	case 1:
		if (nullptr != GameEngineSprite::Find("Hilda_Idle"))
		{
			GameEngineSprite::ReLoad("Hilda_Idle");
		}
		else
		{
			GameEngineSprite::LoadFolder("Hilda_Idle", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\Idle").GetFullPath());
		}++Phase;
		break;
	case 2:
		if (nullptr != GameEngineSprite::Find("Hilda_Shoot"))
		{
			GameEngineSprite::ReLoad("Hilda_Shoot");
		}
		else
		{
			GameEngineSprite::LoadFolder("Hilda_Shoot", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\Laugh\\Hilda").GetFullPath());

		}
		++Phase;
		break;
	case 3:
		if (nullptr != GameEngineSprite::Find("Hilda_Ha"))
		{
			GameEngineSprite::ReLoad("Hilda_Ha");
		}
		else
		{
			GameEngineSprite::LoadFolder("Hilda_Ha", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\Laugh\\Ha").GetFullPath());
		}
		++Phase;
		break;
	case 4:
		if (nullptr != GameEngineSprite::Find("Hilda_Dash"))
		{
			GameEngineSprite::ReLoad("Hilda_Dash");
		}
		else
		{
			GameEngineSprite::LoadFolder("Hilda_Dash", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\ChangePhase\\Dash\\Dash").GetFullPath());
		}
		++Phase;
		break;
	case 5:
		if (nullptr != GameEngineSprite::Find("Hilda_DashBack"))
		{
			GameEngineSprite::ReLoad("Hilda_DashBack");
		}
		else
		{
			GameEngineSprite::LoadFolder("Hilda_DashBack", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\ChangePhase\\Dash\\DashBack").GetFullPath());
		}
		++Phase;
		break;
	case 6:
		if (nullptr != GameEngineSprite::Find("Hilda_Summon"))
		{
			GameEngineSprite::ReLoad("Hilda_Summon");
		}
		else
		{
			GameEngineSprite::LoadFolder("Hilda_Summon", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\ChangePhase\\Summon").GetFullPath());
		}++Phase;
		break;
	case 7:
		if (nullptr != GameEngineSprite::Find("Hilda_Tornado"))
		{
			GameEngineSprite::ReLoad("Hilda_Tornado");
		}
		else
		{
			GameEngineSprite::LoadFolder("Hilda_Tornado", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\Tornado\\Hilda").GetFullPath());
		}++Phase;
		break;
	case 8:
		if (nullptr != GameEngineSprite::Find("Hilda_Tornado_Attack"))
		{
			GameEngineSprite::ReLoad("Hilda_Tornado_Attack");
		}
		else
		{
			GameEngineSprite::LoadFolder("Hilda_Tornado_Attack", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\Tornado\\Tornado\\Attack").GetFullPath());
		}++Phase;
		break;
	case 9:
		if (nullptr != GameEngineSprite::Find("Hilda_Tornado_Intro"))
		{
			GameEngineSprite::ReLoad("Hilda_Tornado_Intro");
		}
		else
		{
			GameEngineSprite::LoadFolder("Hilda_Tornado_Intro", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\Tornado\\Tornado\\Intro").GetFullPath());
		}++Phase;
		break;
	case 10:
		if (nullptr != GameEngineSprite::Find("Taurus_Idle"))
		{
			GameEngineSprite::ReLoad("Taurus_Idle");
		}
		else
		{
			GameEngineSprite::LoadFolder("Taurus_Idle", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Taurus\\Idle").GetFullPath());
		}++Phase;
		break;
	case 11:
		if (nullptr != GameEngineSprite::Find("Taurus_Charge"))
		{
			GameEngineSprite::ReLoad("Taurus_Charge");
		}
		else
		{
			GameEngineSprite::LoadFolder("Taurus_Charge", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Taurus\\Attack\\Charge").GetFullPath());
		}++Phase;
		break;
	case 12:
		if (nullptr != GameEngineSprite::Find("Taurus_Attack"))
		{
			GameEngineSprite::ReLoad("Taurus_Attack");
		}
		else
		{
			GameEngineSprite::LoadFolder("Taurus_Attack", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Taurus\\Attack\\Attack").GetFullPath());
		}++Phase;
		break;
	case 13:
		if (nullptr != GameEngineSprite::Find("Taurus_Constellation"))
		{
			GameEngineSprite::ReLoad("Taurus_Constellation");
		}
		else
		{
			GameEngineSprite::LoadFolder("Taurus_Constellation", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Taurus\\Constellation").GetFullPath());
		}++Phase;
		break;
	case 14:
		if (nullptr != GameEngineSprite::Find("Sagittarius_Lower_Idle"))
		{
			GameEngineSprite::ReLoad("Sagittarius_Lower_Idle");
		}
		else
		{
			GameEngineSprite::LoadFolder("Sagittarius_Lower_Idle", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Sagittarius\\Sagittarius\\Lower\\Idle").GetFullPath());
		}++Phase;
		break;
	case 15:
		if (nullptr != GameEngineSprite::Find("Sagittarius_Upper_Idle"))
		{
			GameEngineSprite::ReLoad("Sagittarius_Upper_Idle");
		}
		else
		{
			GameEngineSprite::LoadFolder("Sagittarius_Upper_Idle", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Sagittarius\\Sagittarius\\Upper\\Idle").GetFullPath());
		}++Phase;
		break;
	case 16:
		if (nullptr != GameEngineSprite::Find("Sagittarius_Upper_Attack"))
		{
			GameEngineSprite::ReLoad("Sagittarius_Upper_Attack");
		}
		else
		{
			GameEngineSprite::LoadFolder("Sagittarius_Upper_Attack", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Sagittarius\\Sagittarius\\Upper\\Attack").GetFullPath());
		}++Phase;
		break;
	case 17:
		if (nullptr != GameEngineSprite::Find("Sagittarius_Arrow"))
		{
			GameEngineSprite::ReLoad("Sagittarius_Arrow");
		}
		else
		{
			GameEngineSprite::LoadFolder("Sagittarius_Arrow", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Sagittarius\\Arrow\\Arrow").GetFullPath());
		}++Phase;
		break;
	case 18:
		if (nullptr != GameEngineSprite::Find("Sagittarius_AppearFX"))
		{
			GameEngineSprite::ReLoad("Sagittarius_AppearFX");
		}
		else
		{
			GameEngineSprite::LoadFolder("Sagittarius_AppearFX", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Sagittarius\\Arrow\\AppearFX").GetFullPath());
		}++Phase;
		break;
	case 19:
		if (nullptr != GameEngineSprite::Find("Sagittarius_Constellation"))
		{
			GameEngineSprite::ReLoad("Sagittarius_Constellation");
		}
		else
		{
			GameEngineSprite::LoadFolder("Sagittarius_Constellation", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Sagittarius\\Constellation").GetFullPath());
		}++Phase;
		break;
	case 20:
		if (nullptr != GameEngineSprite::Find("Gemini_Idle"))
		{
			GameEngineSprite::ReLoad("Gemini_Idle");
		}
		else
		{
			GameEngineSprite::LoadFolder("Gemini_Idle", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Gemini\\Idle").GetFullPath());
		}++Phase;
		break;
	case 21:
		if (nullptr != GameEngineSprite::Find("Gemini_AttackA"))
		{
			GameEngineSprite::ReLoad("Gemini_AttackA");
		}
		else
		{
			GameEngineSprite::LoadFolder("Gemini_AttackA", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Gemini\\Attack (A)").GetFullPath());
		}++Phase;
		break;
	case 22:
		if (nullptr != GameEngineSprite::Find("Gemini_AttackB"))
		{
			GameEngineSprite::ReLoad("Gemini_AttackB");
		}
		else
		{
			GameEngineSprite::LoadFolder("Gemini_AttackB", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Gemini\\Attack (B)").GetFullPath());
		}++Phase;
		break;
	case 23:
		if (nullptr != GameEngineSprite::Find("Gemini_Constellation"))
		{
			GameEngineSprite::ReLoad("Gemini_Constellation");
		}
		else
		{
			GameEngineSprite::LoadFolder("Gemini_Constellation", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Gemini\\Constellation").GetFullPath());
		}++Phase;
		break;
	case 24:
		if (nullptr != GameEngineSprite::Find("Orb_Idle_Intro"))
		{
			GameEngineSprite::ReLoad("Orb_Idle_Intro");
		}
		else
		{
			GameEngineSprite::LoadFolder("Orb_Idle_Intro", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Gemini\\Orb\\Idle\\Intro").GetFullPath());
		}++Phase;
		break;
	case 25:
		if (nullptr != GameEngineSprite::Find("Orb_Idle_Loop"))
		{
			GameEngineSprite::ReLoad("Orb_Idle_Loop");
		}
		else
		{
			GameEngineSprite::LoadFolder("Orb_Idle_Loop", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Gemini\\Orb\\Idle\\Loop").GetFullPath());
		}++Phase;
		break;
	case 26:
		if (nullptr != GameEngineSprite::Find("Orb_Idle_Leave"))
		{
			GameEngineSprite::ReLoad("Orb_Idle_Leave");
		}
		else
		{
			GameEngineSprite::LoadFolder("Orb_Idle_Leave", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Gemini\\Orb\\Idle\\Leave").GetFullPath());
		}++Phase;
		break;
	case 27:
		if (nullptr != GameEngineSprite::Find("Orb_Attack_Intro"))
		{
			GameEngineSprite::ReLoad("Orb_Attack_Intro");
		}
		else
		{
			GameEngineSprite::LoadFolder("Orb_Attack_Intro", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Gemini\\Orb\\Attack\\Intro").GetFullPath());
		}++Phase;
		break;
	case 28:
		if (nullptr != GameEngineSprite::Find("Orb_Attack_Loop"))
		{
			GameEngineSprite::ReLoad("Orb_Attack_Loop");
		}
		else
		{
			GameEngineSprite::LoadFolder("Orb_Attack_Loop", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Gemini\\Orb\\Attack\\Loop").GetFullPath());
		}++Phase;
		break;
	case 29:
		if (nullptr != GameEngineSprite::Find("Orb_Attack_Leave"))
		{
			GameEngineSprite::ReLoad("Orb_Attack_Leave");
		}
		else
		{
			GameEngineSprite::LoadFolder("Orb_Attack_Leave", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Gemini\\Orb\\Attack\\Leave").GetFullPath());
		}++Phase;
		break;
	case 30:
		if (nullptr != GameEngineSprite::Find("Orb_Attack_Scatter"))
		{
			GameEngineSprite::ReLoad("Orb_Attack_Scatter");
		}
		else
		{
			GameEngineSprite::LoadFolder("Orb_Attack_Scatter", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Gemini\\Orb\\Attack\\FX\\Large").GetFullPath());
		}++Phase;
		break;
	case 31:
		if (nullptr != GameEngineSprite::Find("Orb_Bullet"))
		{
			GameEngineSprite::ReLoad("Orb_Bullet");
		}
		else
		{
			GameEngineSprite::LoadFolder("Orb_Bullet", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Gemini\\Orb\\Attack\\BulletStream").GetFullPath());
		}++Phase;
		break;
	case 32:
		if (nullptr != GameEngineSprite::Find("Moon_Intro0"))
		{
			GameEngineSprite::ReLoad("Moon_Intro0");
		}
		else
		{
			GameEngineSprite::LoadFolder("Moon_Intro0", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\TransitionToMoon\\Start").GetFullPath());
		}++Phase;
		break;
	case 33:
		if (nullptr != GameEngineSprite::Find("Moon_Intro1"))
		{
			GameEngineSprite::ReLoad("Moon_Intro1");
		}
		else
		{
			GameEngineSprite::LoadFolder("Moon_Intro1", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\TransitionToMoon\\BoilA").GetFullPath());
		}++Phase;
		break;
	case 34:
		if (nullptr != GameEngineSprite::Find("Moon_Intro2"))
		{
			GameEngineSprite::ReLoad("Moon_Intro2");
		}
		else
		{
			GameEngineSprite::LoadFolder("Moon_Intro2", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\TransitionToMoon\\Middle").GetFullPath());
		}++Phase;
		break;
	case 35:
		if (nullptr != GameEngineSprite::Find("Moon_Intro3"))
		{
			GameEngineSprite::ReLoad("Moon_Intro3");
		}
		else
		{
			GameEngineSprite::LoadFolder("Moon_Intro3", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\TransitionToMoon\\BoilB").GetFullPath());
		}++Phase;
		break;
	case 36:
		if (nullptr != GameEngineSprite::Find("Moon_Intro4"))
		{
			GameEngineSprite::ReLoad("Moon_Intro4");
		}
		else
		{
			GameEngineSprite::LoadFolder("Moon_Intro4", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\TransitionToMoon\\End").GetFullPath());
		}++Phase;
		break;
	case 37:
		if (nullptr != GameEngineSprite::Find("Moon_Idle"))
		{
			GameEngineSprite::ReLoad("Moon_Idle");
		}
		else
		{
			GameEngineSprite::LoadFolder("Moon_Idle", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Idle").GetFullPath());
		}++Phase;
		break;
	case 38:
		if (nullptr != GameEngineSprite::Find("Moon_Attack_Intro"))
		{
			GameEngineSprite::ReLoad("Moon_Attack_Intro");
		}
		else
		{
			GameEngineSprite::LoadFolder("Moon_Attack_Intro", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Attack\\Intro").GetFullPath());
		}++Phase;
		break;
	case 39:
		if (nullptr != GameEngineSprite::Find("Moon_Attack"))
		{
			GameEngineSprite::ReLoad("Moon_Attack");
		}
		else
		{
			GameEngineSprite::LoadFolder("Moon_Attack", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Attack\\AttackIdle").GetFullPath());
		}++Phase;
		break;
	case 40:
		if (nullptr != GameEngineSprite::Find("Moon_Attack_Outtro"))
		{
			GameEngineSprite::ReLoad("Moon_Attack_Outtro");
		}
		else
		{
			GameEngineSprite::LoadFolder("Moon_Attack_Outtro", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Attack\\Outtro").GetFullPath());
		}++Phase;
		break;
	case 41:
		if (nullptr != GameEngineSprite::Find("Moon_Death"))
		{
			GameEngineSprite::ReLoad("Moon_Death");
		}
		else
		{
			GameEngineSprite::LoadFolder("Moon_Death", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Death").GetFullPath());
		}++Phase;
		break;
	case 42:
		if (nullptr != GameEngineSprite::Find("Hilda_UFO_Red"))
		{
			GameEngineSprite::ReLoad("Hilda_UFO_Red");
		}
		else
		{
			GameEngineSprite::LoadFolder("Hilda_UFO_Red", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Projectiles\\UFO\\Red").GetFullPath());
		}++Phase;
		break;
	case 43:
		if (nullptr != GameEngineSprite::Find("Hilda_UFO_Bronze"))
		{
			GameEngineSprite::ReLoad("Hilda_UFO_Bronze");
		}
		else
		{
			GameEngineSprite::LoadFolder("Hilda_UFO_Bronze", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Projectiles\\UFO\\Bronze").GetFullPath());
		}++Phase;
		break;
	case 44:
		if (nullptr != GameEngineSprite::Find("Hilda_UFO_Beam"))
		{
			GameEngineSprite::ReLoad("Hilda_UFO_Beam");
		}
		else
		{
			GameEngineSprite::LoadFolder("Hilda_UFO_Beam", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Projectiles\\UFO\\Beam").GetFullPath());
		}++Phase;
		break;
	case 45:
		if (nullptr != GameEngineSprite::Find("Cuphead_AirPlane_Origin_Idle"))
		{
			GameEngineSprite::ReLoad("Cuphead_AirPlane_Origin_Idle");
		}
		else
		{
			GameEngineSprite::LoadFolder("Cuphead_AirPlane_Origin_Idle", Dir.GetPlusFileName("Cuphead_AirPlane\\Idle\\Idle").GetFullPath());
		}++Phase;
		break;
	case 46:
		if (nullptr != GameEngineSprite::Find("Cuphead_AirPlane_Origin_Idleup"))
		{
			GameEngineSprite::ReLoad("Cuphead_AirPlane_Origin_Idleup");
		}
		else
		{
			GameEngineSprite::LoadFolder("Cuphead_AirPlane_Origin_Idleup", Dir.GetPlusFileName("Cuphead_AirPlane\\Idle\\up").GetFullPath());
		}++Phase;
		break;
	case 47:
		if (nullptr != GameEngineSprite::Find("Cuphead_AirPlane_Origin_Idledown"))
		{
			GameEngineSprite::ReLoad("Cuphead_AirPlane_Origin_Idledown");
		}
		else
		{
			GameEngineSprite::LoadFolder("Cuphead_AirPlane_Origin_Idledown", Dir.GetPlusFileName("Cuphead_AirPlane\\Idle\\down").GetFullPath());
		}++Phase;
		break;
	case 48:
		if (nullptr != GameEngineSprite::Find("Cuphead_AirPlane_Origin_intro"))
		{
			GameEngineSprite::ReLoad("Cuphead_AirPlane_Origin_intro");
		}
		else
		{
			GameEngineSprite::LoadFolder("Cuphead_AirPlane_Origin_intro", Dir.GetPlusFileName("Cuphead_AirPlane\\Intros\\Regular").GetFullPath());
		}++Phase;
		break;
	case 49:
		if (nullptr != GameEngineSprite::Find("Cuphead_AirPlane_Origin_transup"))
		{
			GameEngineSprite::ReLoad("Cuphead_AirPlane_Origin_transup");
		}
		else
		{
			GameEngineSprite::LoadFolder("Cuphead_AirPlane_Origin_transup", Dir.GetPlusFileName("Cuphead_AirPlane\\Transicion\\transup").GetFullPath());
		}++Phase;
		break;
	case 50:
		if (nullptr != GameEngineSprite::Find("Cuphead_AirPlane_Origin_transdown"))
		{
			GameEngineSprite::ReLoad("Cuphead_AirPlane_Origin_transdown");
		}
		else
		{
			GameEngineSprite::LoadFolder("Cuphead_AirPlane_Origin_transdown", Dir.GetPlusFileName("Cuphead_AirPlane\\Transicion\\transdown").GetFullPath());
		}++Phase;
		break;
	case 51:
		if (nullptr != GameEngineSprite::Find("Cuphead_AirPlane_Super_Idle"))
		{
			GameEngineSprite::ReLoad("Cuphead_AirPlane_Super_Idle");
		}
		else
		{
			GameEngineSprite::LoadFolder("Cuphead_AirPlane_Super_Idle", Dir.GetPlusFileName("Cuphead_AirPlane\\Super\\Idle\\Idle").GetFullPath());
		}++Phase;
		break;
	case 52:
		if (nullptr != GameEngineSprite::Find("Cuphead_AirPlane_Super_Idleup"))
		{
			GameEngineSprite::ReLoad("Cuphead_AirPlane_Super_Idleup");
		}
		else
		{
			GameEngineSprite::LoadFolder("Cuphead_AirPlane_Super_Idleup", Dir.GetPlusFileName("Cuphead_AirPlane\\Super\\Idle\\up").GetFullPath());
		}++Phase;
		break;
	case 53:
		if (nullptr != GameEngineSprite::Find("Cuphead_AirPlane_Super_Idledown"))
		{
			GameEngineSprite::ReLoad("Cuphead_AirPlane_Super_Idledown");
		}
		else
		{
			GameEngineSprite::LoadFolder("Cuphead_AirPlane_Super_Idledown", Dir.GetPlusFileName("Cuphead_AirPlane\\Super\\Idle\\down").GetFullPath());
		}++Phase;
		break;
	case 54:
		if (nullptr != GameEngineSprite::Find("Cuphead_AirPlane_Super_intro"))
		{
			GameEngineSprite::ReLoad("Cuphead_AirPlane_Super_intro");
		}
		else
		{
			GameEngineSprite::LoadFolder("Cuphead_AirPlane_Super_intro", Dir.GetPlusFileName("Cuphead_AirPlane\\Super\\intro").GetFullPath());
		}++Phase;
		break;
	case 55:
		if (nullptr != GameEngineSprite::Find("Cuphead_AirPlane_Super_transup"))
		{
			GameEngineSprite::ReLoad("Cuphead_AirPlane_Super_transup");
		}
		else
		{
			GameEngineSprite::LoadFolder("Cuphead_AirPlane_Super_transup", Dir.GetPlusFileName("Cuphead_AirPlane\\Super\\trans\\up").GetFullPath());
		}++Phase;
		break;
	case 56:
		if (nullptr != GameEngineSprite::Find("Cuphead_AirPlane_Super_transdown"))
		{
			GameEngineSprite::ReLoad("Cuphead_AirPlane_Super_transdown");
		}
		else
		{
			GameEngineSprite::LoadFolder("Cuphead_AirPlane_Super_transdown", Dir.GetPlusFileName("Cuphead_AirPlane\\Super\\trans\\down").GetFullPath());
		}++Phase;
		break;
	case 57:
		if (nullptr != GameEngineSprite::Find("Cuphead_AirPlane_Shrink_Idle"))
		{
			GameEngineSprite::ReLoad("Cuphead_AirPlane_Shrink_Idle");
		}
		else
		{
			GameEngineSprite::LoadFolder("Cuphead_AirPlane_Shrink_Idle", Dir.GetPlusFileName("Cuphead_AirPlane\\Shrink\\idle\\Idle").GetFullPath());
		}++Phase;
		break;
	case 58:
		if (nullptr != GameEngineSprite::Find("Cuphead_AirPlane_Shrink_Idleup"))
		{
			GameEngineSprite::ReLoad("Cuphead_AirPlane_Shrink_Idleup");
		}
		else
		{
			GameEngineSprite::LoadFolder("Cuphead_AirPlane_Shrink_Idleup", Dir.GetPlusFileName("Cuphead_AirPlane\\Shrink\\idle\\up").GetFullPath());
		}++Phase;
		break;
	case 59:
		if (nullptr != GameEngineSprite::Find("Cuphead_AirPlane_Shrink_Idledown"))
		{
			GameEngineSprite::ReLoad("Cuphead_AirPlane_Shrink_Idledown");
		}
		else
		{
			GameEngineSprite::LoadFolder("Cuphead_AirPlane_Shrink_Idledown", Dir.GetPlusFileName("Cuphead_AirPlane\\Shrink\\idle\\down").GetFullPath());
		}++Phase;
		break;
	case 60:
		if (nullptr != GameEngineSprite::Find("Cuphead_AirPlane_Shrink_intro"))
		{
			GameEngineSprite::ReLoad("Cuphead_AirPlane_Shrink_intro");
		}
		else
		{
			GameEngineSprite::LoadFolder("Cuphead_AirPlane_Shrink_intro", Dir.GetPlusFileName("Cuphead_AirPlane\\Shrink\\morph").GetFullPath());
		}++Phase;
		break;
	case 61:
		if (nullptr != GameEngineSprite::Find("Cuphead_AirPlane_Shrink_transup"))
		{
			GameEngineSprite::ReLoad("Cuphead_AirPlane_Shrink_transup");
		}
		else
		{
			GameEngineSprite::LoadFolder("Cuphead_AirPlane_Shrink_transup", Dir.GetPlusFileName("Cuphead_AirPlane\\Shrink\\trans\\up").GetFullPath());
		}++Phase;
		break;
	case 62:
		if (nullptr != GameEngineSprite::Find("Cuphead_AirPlane_Shrink_transdown"))
		{
			GameEngineSprite::ReLoad("Cuphead_AirPlane_Shrink_transdown");
		}
		else
		{
			GameEngineSprite::LoadFolder("Cuphead_AirPlane_Shrink_transdown", Dir.GetPlusFileName("Cuphead_AirPlane\\Shrink\\trans\\down").GetFullPath());
		}++Phase;
		break;
	case 63:
		if (nullptr != GameEngineSprite::Find("Cuphead_AirPlane_Parry"))
		{
			GameEngineSprite::ReLoad("Cuphead_AirPlane_Parry");
		}
		else
		{
			GameEngineSprite::LoadFolder("Cuphead_AirPlane_Parry", Dir.GetPlusFileName("Cuphead_AirPlane\\Parry").GetFullPath());
		}++Phase;
		break;
	case 64:
		if (nullptr != GameEngineSprite::Find("Cuphead_AirPlane_Spark"))
		{
			GameEngineSprite::ReLoad("Cuphead_AirPlane_Spark");
		}
		else
		{
			GameEngineSprite::LoadFolder("Cuphead_AirPlane_Spark", Dir.GetPlusFileName("Cuphead_AirPlane\\effect\\Spark").GetFullPath());
		}++Phase;
		break;
	case 65:
		if (nullptr != GameEngineSprite::Find("BlimpEnemy_PurPle_Idle"))
		{
			GameEngineSprite::ReLoad("BlimpEnemy_PurPle_Idle");
		}
		else
		{
			GameEngineSprite::LoadFolder("BlimpEnemy_PurPle_Idle", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Purple\\Idle").GetFullPath());
		}++Phase;
		break;
	case 66:
		if (nullptr != GameEngineSprite::Find("BlimpEnemy_Green_Idle"))
		{
			GameEngineSprite::ReLoad("BlimpEnemy_Green_Idle");
		}
		else
		{
			GameEngineSprite::LoadFolder("BlimpEnemy_Green_Idle", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Green\\Idle").GetFullPath());
		}++Phase;
		break;
	case 67:
		if (nullptr != GameEngineSprite::Find("BlimpEnemy_Purple_Attack"))
		{
			GameEngineSprite::ReLoad("BlimpEnemy_Purple_Attack");
		}
		else
		{
			GameEngineSprite::LoadFolder("BlimpEnemy_Purple_Attack", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Purple\\Attack").GetFullPath());
		}++Phase;
		break;
	case 68:
		if (nullptr != GameEngineSprite::Find("BlimpEnemy_Green_Attack"))
		{
			GameEngineSprite::ReLoad("BlimpEnemy_Green_Attack");
		}
		else
		{
			GameEngineSprite::LoadFolder("BlimpEnemy_Green_Attack", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Green\\Attack").GetFullPath());
		}++Phase;
		break;
	case 69:
		if (nullptr != GameEngineSprite::Find("BlimpEnemy_Purple_Turn"))
		{
			GameEngineSprite::ReLoad("BlimpEnemy_Purple_Turn");
		}
		else
		{
			GameEngineSprite::LoadFolder("BlimpEnemy_Purple_Turn", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Purple\\Turn").GetFullPath());
		}++Phase;
		break;
	case 70:
		if (nullptr != GameEngineSprite::Find("BlimpEnemy_Green_Turn"))
		{
			GameEngineSprite::ReLoad("BlimpEnemy_Green_Turn");
		}
		else
		{
			GameEngineSprite::LoadFolder("BlimpEnemy_Green_Turn", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Green\\Turn").GetFullPath());
		}++Phase;
		break;
	case 71:
		if (nullptr != GameEngineSprite::Find("BlimpEnemy_Green_Death_A"))
		{
			GameEngineSprite::ReLoad("BlimpEnemy_Green_Death_A");
		}
		else
		{
			GameEngineSprite::LoadFolder("BlimpEnemy_Green_Death_A", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Green\\Pieces\\A").GetFullPath());
		}++Phase;
		break;
	case 72:
		if (nullptr != GameEngineSprite::Find("BlimpEnemy_Green_Death_B"))
		{
			GameEngineSprite::ReLoad("BlimpEnemy_Green_Death_B");
		}
		else
		{
			GameEngineSprite::LoadFolder("BlimpEnemy_Green_Death_B", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Green\\Pieces\\B").GetFullPath());
		}++Phase;
		break;
	case 73:
		if (nullptr != GameEngineSprite::Find("BlimpEnemy_Green_Death_C"))
		{
			GameEngineSprite::ReLoad("BlimpEnemy_Green_Death_C");
		}
		else
		{
			GameEngineSprite::LoadFolder("BlimpEnemy_Green_Death_C", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Green\\Pieces\\C").GetFullPath());
		}++Phase;
		break;
	case 74:
		if (nullptr != GameEngineSprite::Find("BlimpEnemy_Green_Death_D"))
		{
			GameEngineSprite::ReLoad("BlimpEnemy_Green_Death_D");
		}
		else
		{
			GameEngineSprite::LoadFolder("BlimpEnemy_Green_Death_D", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Green\\Pieces\\D").GetFullPath());
		}++Phase;
		break;
	case 75:
		if (nullptr != GameEngineSprite::Find("BlimpEnemy_Green_Death_E"))
		{
			GameEngineSprite::ReLoad("BlimpEnemy_Green_Death_E");
		}
		else
		{
			GameEngineSprite::LoadFolder("BlimpEnemy_Green_Death_E", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Green\\Pieces\\E").GetFullPath());
		}++Phase;
		break;
	case 76:
		if (nullptr != GameEngineSprite::Find("BlimpEnemy_Green_Death_F"))
		{
			GameEngineSprite::ReLoad("BlimpEnemy_Green_Death_F");
		}
		else
		{
			GameEngineSprite::LoadFolder("BlimpEnemy_Green_Death_F", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Green\\Pieces\\F").GetFullPath());
		}++Phase;
		break;
	case 77:
		if (nullptr != GameEngineSprite::Find("BlimpEnemy_Purple_Death_A"))
		{
			GameEngineSprite::ReLoad("BlimpEnemy_Purple_Death_A");
		}
		else
		{
			GameEngineSprite::LoadFolder("BlimpEnemy_Purple_Death_A", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Purple\\Pieces\\A").GetFullPath());
		}++Phase;
		break;
	case 78:
		if (nullptr != GameEngineSprite::Find("BlimpEnemy_Purple_Death_B"))
		{
			GameEngineSprite::ReLoad("BlimpEnemy_Purple_Death_B");
		}
		else
		{
			GameEngineSprite::LoadFolder("BlimpEnemy_Purple_Death_B", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Purple\\Pieces\\B").GetFullPath());
		}++Phase;
		break;
	case 79:
		if (nullptr != GameEngineSprite::Find("BlimpEnemy_Purple_Death_C"))
		{
			GameEngineSprite::ReLoad("BlimpEnemy_Purple_Death_C");
		}
		else
		{
			GameEngineSprite::LoadFolder("BlimpEnemy_Purple_Death_C", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Purple\\Pieces\\C").GetFullPath());
		}++Phase;
		break;
	case 80:
		if (nullptr != GameEngineSprite::Find("BlimpEnemy_Purple_Death_D"))
		{
			GameEngineSprite::ReLoad("BlimpEnemy_Purple_Death_D");
		}
		else
		{
			GameEngineSprite::LoadFolder("BlimpEnemy_Purple_Death_D", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Purple\\Pieces\\D").GetFullPath());
		}++Phase;
		break;
	case 81:
		if (nullptr != GameEngineSprite::Find("BlimpEnemy_Purple_Death_E"))
		{
			GameEngineSprite::ReLoad("BlimpEnemy_Purple_Death_E");
		}
		else
		{
			GameEngineSprite::LoadFolder("BlimpEnemy_Purple_Death_E", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Purple\\Pieces\\E").GetFullPath());
		}++Phase;
		break;
	case 82:
		if (nullptr != GameEngineSprite::Find("BlimpEnemy_Purple_Death_F"))
		{
			GameEngineSprite::ReLoad("BlimpEnemy_Purple_Death_F");
		}
		else
		{
			GameEngineSprite::LoadFolder("BlimpEnemy_Purple_Death_F", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Purple\\Pieces\\F").GetFullPath());
		}++Phase;
		break;
	case 83:
		if (nullptr != GameEngineSprite::Find("BlimpEnemy_Explode"))
		{
			GameEngineSprite::ReLoad("BlimpEnemy_Explode");
		}
		else
		{
			GameEngineSprite::LoadFolder("BlimpEnemy_Explode", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Explode (Death)\\Explode").GetFullPath());
		}++Phase;
		break;
	case 84:
		if (nullptr != GameEngineSprite::Find("BlimpEnemy_Spark"))
		{
			GameEngineSprite::ReLoad("BlimpEnemy_Spark");
		}
		else
		{
			GameEngineSprite::LoadFolder("BlimpEnemy_Spark", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Explode (Death)\\Spark").GetFullPath());
		}++Phase;
		break;

	case 85:
		if (nullptr != GameEngineSprite::Find("Sagittarius_Star_Idle"))
		{
			GameEngineSprite::ReLoad("Sagittarius_Star_Idle");
		}
		else
		{
			GameEngineSprite::LoadFolder("Sagittarius_Star_Idle", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Sagittarius\\Arrow\\Star\\Idle").GetFullPath());
		}++Phase;
		break;

	case 86:
		if (nullptr != GameEngineSprite::Find("Sagittarius_Star_Trail"))
		{
			GameEngineSprite::ReLoad("Sagittarius_Star_Trail");
		}
		else
		{
			GameEngineSprite::LoadFolder("Sagittarius_Star_Trail", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Sagittarius\\Arrow\\Star\\Trail\\A").GetFullPath());
		}++Phase;
		break;

	case 87:
		if (nullptr != GameEngineSprite::Find("Sagittarius_Star_Death"))
		{
			GameEngineSprite::ReLoad("Sagittarius_Star_Death");//Sagittarius_Star_Death
		}
		else
		{
			GameEngineSprite::LoadFolder("Sagittarius_Star_Death", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Sagittarius\\Arrow\\Star\\Death").GetFullPath());
		}++Phase;
		break;

	case 88:
		if (nullptr != GameEngineSprite::Find("Moon_Star_A"))
		{
			GameEngineSprite::ReLoad("Moon_Star_A");
		}
		else
		{
			GameEngineSprite::LoadFolder("Moon_Star_A", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Projectiles\\Star\\A").GetFullPath());
		}++Phase;
		break;

	case 89:
		if (nullptr != GameEngineSprite::Find("Moon_Star_B"))
		{
			GameEngineSprite::ReLoad("Moon_Star_B");
		}
		else
		{
			GameEngineSprite::LoadFolder("Moon_Star_B", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Projectiles\\Star\\B").GetFullPath());
		}++Phase;
		break;

	case 90:
		if (nullptr != GameEngineSprite::Find("Moon_Star_C"))
		{
			GameEngineSprite::ReLoad("Moon_Star_C");
		}
		else
		{
			GameEngineSprite::LoadFolder("Moon_Star_C", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Projectiles\\Star\\C").GetFullPath());
		}++Phase;
		break;

	case 91:
		if (nullptr != GameEngineSprite::Find("Moon_Star_Pink"))
		{
			GameEngineSprite::ReLoad("Moon_Star_Pink");
		}
		else
		{
			GameEngineSprite::LoadFolder("Moon_Star_Pink", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Projectiles\\Star\\Pink").GetFullPath());
		}++Phase;
		break;

	case 92:
		if (nullptr != GameEngineSprite::Find("Moon_Star_IdleFX"))
		{
			GameEngineSprite::ReLoad("Moon_Star_IdleFX");
		}
		else
		{
			GameEngineSprite::LoadFolder("Moon_Star_IdleFX", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Projectiles\\Star\\IdleFX").GetFullPath());
		}++Phase;
		break;

	case 93:
		if (nullptr != GameEngineSprite::Find("Moon_Star_PinkFX"))
		{
			GameEngineSprite::ReLoad("Moon_Star_PinkFX");
		}
		else
		{
			GameEngineSprite::LoadFolder("Moon_Star_PinkFX", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\Moon\\Projectiles\\Star\\PinkFX").GetFullPath());
		}++Phase;
		break;

	case 94:
		if (nullptr != GameEngineSprite::Find("Hilda_ChangeBack"))
		{
			GameEngineSprite::ReLoad("Hilda_ChangeBack");
		}
		else
		{
			GameEngineSprite::LoadFolder("Hilda_ChangeBack", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\ChangePhase\\ChangeBack").GetFullPath());
		}++Phase;
		break;

	case 95:
		if (nullptr != GameEngineSprite::Find("HildaChangePhaseDashSmoke"))
		{
			GameEngineSprite::ReLoad("HildaChangePhaseDashSmoke");
		}
		else
		{
			GameEngineSprite::LoadFolder("HildaChangePhaseDashSmoke", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\ChangePhase\\FX\\SmokeFX").GetFullPath());
		}++Phase;
		break;

	case 96:
		if (nullptr != GameEngineSprite::Find("peashotFX"))
		{
			GameEngineSprite::ReLoad("peashotFX");
		}
		else
		{
			GameEngineSprite::LoadFolder("peashotFX", Dir.GetPlusFileName("Cuphead_AirPlane\\bullet\\peashotFX").GetFullPath());
		}++Phase;
		break;

	case 97:
		if (nullptr != GameEngineSprite::Find("HildaChangePhaseDashBackExplode"))
		{
			GameEngineSprite::ReLoad("HildaChangePhaseDashBackExplode");
		}
		else
		{
			GameEngineSprite::LoadFolder("HildaChangePhaseDashBackExplode", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\ChangePhase\\FX\\DashBackExplodeFX").GetFullPath());
		}++Phase;
		break;

	case 98:
		if (nullptr != GameEngineSprite::Find("HildaChangePhaseDashExplode"))
		{
			GameEngineSprite::ReLoad("HildaChangePhaseDashExplode");
		}
		else
		{
			GameEngineSprite::LoadFolder("HildaChangePhaseDashExplode", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\ChangePhase\\FX\\DashExplodeFX").GetFullPath());
		}++Phase;
		break;

	case 99:
		if (nullptr != GameEngineSprite::Find("HildaChangeFX"))
		{
			GameEngineSprite::ReLoad("HildaChangeFX");
		}
		else
		{
			GameEngineSprite::LoadFolder("HildaChangeFX", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\HildaBerg\\Normal\\ChangePhase\\FX\\HildaChangeFX").GetFullPath());
		}++Phase;
		break;
	case 100:
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
	case 101:
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
	case 102:
		if (nullptr != GameEngineSprite::Find("BlimpEnemy_BulletA"))
		{
			GameEngineSprite::ReLoad("BlimpEnemy_BulletA");
		}
		else
		{
			GameEngineSprite::LoadFolder("BlimpEnemy_BulletA", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Bullet\\A\\Bullet").GetFullPath());
		}
		++Phase;
		break;
	case 103:
		if (nullptr != GameEngineSprite::Find("BlimpEnemy_BulletB"))
		{
			GameEngineSprite::ReLoad("BlimpEnemy_BulletB");
		}
		else
		{
			GameEngineSprite::LoadFolder("BlimpEnemy_BulletB", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Bullet\\B\\Bullet").GetFullPath());
		}
		++Phase;
		break;
	case 104:
		if (nullptr != GameEngineSprite::Find("BlimpEnemy_BulletC"))
		{
			GameEngineSprite::ReLoad("BlimpEnemy_BulletC");
		}
		else
		{
			GameEngineSprite::LoadFolder("BlimpEnemy_BulletC", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Bullet\\C\\Bullet").GetFullPath());
		}
		++Phase;
		break;
	case 105:
		if (nullptr != GameEngineSprite::Find("BlimpEnemy_BulletPinkA"))
		{
			GameEngineSprite::ReLoad("BlimpEnemy_BulletPinkA");
		}
		else
		{
			GameEngineSprite::LoadFolder("BlimpEnemy_BulletPinkA", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Bullet\\Pink\\A").GetFullPath());
		}
		++Phase;
		break;
	case 106:
		if (nullptr != GameEngineSprite::Find("BlimpEnemy_BulletPinkB"))
		{
			GameEngineSprite::ReLoad("BlimpEnemy_BulletPinkB");
		}
		else
		{
			GameEngineSprite::LoadFolder("BlimpEnemy_BulletPinkB", Dir.GetPlusFileName("stage1\\Boss\\Hilda\\BlimpEnemy\\Bullet\\Pink\\B").GetFullPath());
		}
		++Phase;
		break;
	case 107:
		if (nullptr != GameEngineSprite::Find("shmup_super_boom"))
		{
			GameEngineSprite::ReLoad("shmup_super_boom");
		}
		else
		{
			GameEngineSprite::LoadFolder("shmup_super_boom", Dir.GetPlusFileName("Cuphead_AirPlane\\effect\\Boom").GetFullPath());
		}
		++Phase;
		break;
	case 108:
		if (nullptr != GameEngineSprite::Find("shmup_super_explode"))
		{
			GameEngineSprite::ReLoad("shmup_super_explode");
		}
		else
		{
			GameEngineSprite::LoadFolder("shmup_super_explode", Dir.GetPlusFileName("Cuphead_AirPlane\\effect\\Explode").GetFullPath());
		}
		++Phase;
		break;

	case 109:
		if (nullptr != GameEngineSprite::Find("Super_FX"))
		{
			GameEngineSprite::ReLoad("Super_FX");
		}
		else
		{
			GameEngineSprite::LoadFolder("Super_FX", Dir.GetPlusFileName("Cuphead_AirPlane\\effect\\Super_FX").GetFullPath());
		}
		++Phase;
		break;

	case 110:
		if (nullptr != GameEngineSprite::Find("Cuphead_AirPlane_Smoke_Idle"))
		{
			GameEngineSprite::ReLoad("Cuphead_AirPlane_Smoke_Idle");
		}
		else
		{
			GameEngineSprite::LoadFolder("Cuphead_AirPlane_Smoke_Idle", Dir.GetPlusFileName("Cuphead_AirPlane\\effect\\PlaneSmoke").GetFullPath());
		}
		++Phase;
		break;

	case 111:
		if (nullptr != GameEngineSprite::Find("Cuphead_AirPlane_Bullet"))
		{
			GameEngineSprite::ReLoad("Cuphead_AirPlane_Bullet");
		}
		else
		{
			GameEngineSprite::LoadFolder("Cuphead_AirPlane_Bullet", Dir.GetPlusFileName("Cuphead_AirPlane\\bullet\\peashot").GetFullPath());
		}
		++Phase;
		break;


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
		++Phase;
		break;

	case 114:
		++Phase;
		break;

	case 115:
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
		break;
	}







}

