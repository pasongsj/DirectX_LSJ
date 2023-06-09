#include "PrecompileHeader.h"
#include "Moon.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "GameContentsEnemyRenderer.h"

#include "MoonStar.h"

Moon::Moon()
{
}

Moon::~Moon()
{
}

void Moon::MakeSprite()
{

	if (nullptr == GameEngineSprite::Find("Moon_Idle"))
	{

		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources\\Texture\\stage1\\Boss\\Hilda\\Moon");


		GameEngineSprite::LoadFolder("Moon_Intro0", NewDir.GetPlusFileName("TransitionToMoon\\Start").GetFullPath());
		GameEngineSprite::LoadFolder("Moon_Intro1", NewDir.GetPlusFileName("TransitionToMoon\\BoilA").GetFullPath());
		GameEngineSprite::LoadFolder("Moon_Intro2", NewDir.GetPlusFileName("TransitionToMoon\\Middle").GetFullPath());
		GameEngineSprite::LoadFolder("Moon_Intro3", NewDir.GetPlusFileName("TransitionToMoon\\BoilB").GetFullPath());
		GameEngineSprite::LoadFolder("Moon_Intro4", NewDir.GetPlusFileName("TransitionToMoon\\End").GetFullPath());

		GameEngineSprite::LoadFolder("Moon_Idle", NewDir.GetPlusFileName("Idle").GetFullPath());
		GameEngineSprite::LoadFolder("Moon_Attack_Intro", NewDir.GetPlusFileName("Attack\\Intro").GetFullPath());
		GameEngineSprite::LoadFolder("Moon_Attack", NewDir.GetPlusFileName("Attack\\AttackIdle").GetFullPath());
		GameEngineSprite::LoadFolder("Moon_Attack_Outtro", NewDir.GetPlusFileName("Attack\\Outtro").GetFullPath());
		GameEngineSprite::LoadFolder("Moon_Death", NewDir.GetPlusFileName("Death").GetFullPath());

	}
}

void Moon::HildaDeath()
{
	NextState = MoonState::DEATH;
}


void Moon::Start()
{
	SetPhase(6);
	MakeSprite();
	BossRender = CreateComponent<GameContentsEnemyRenderer>(CupHeadRendererOrder::Boss);
	BossRender->CreateAnimation({ .AnimationName = "Intro0",  .SpriteName = "Moon_Intro0", .FrameInter = 0.05f, .Loop = false ,.ScaleToTexture = true });
	BossRender->CreateAnimation({ .AnimationName = "Intro1",  .SpriteName = "Moon_Intro1", .FrameInter = 0.05f, .Loop = true ,.ScaleToTexture = true });
	BossRender->CreateAnimation({ .AnimationName = "Intro2",  .SpriteName = "Moon_Intro2", .FrameInter = 0.05f, .Loop = false ,.ScaleToTexture = true });
	BossRender->CreateAnimation({ .AnimationName = "Intro3",  .SpriteName = "Moon_Intro3", .FrameInter = 0.05f, .Loop = true ,.ScaleToTexture = true });
	BossRender->CreateAnimation({ .AnimationName = "Intro4",  .SpriteName = "Moon_Intro4", .FrameInter = 0.05f, .Loop = false ,.ScaleToTexture = true });

	BossRender->CreateAnimation({ .AnimationName = "Idle",  .SpriteName = "Moon_Idle", .FrameInter = 0.05f, .Loop = true ,.ScaleToTexture = true });
	BossRender->CreateAnimation({ .AnimationName = "Attack_Intro",  .SpriteName = "Moon_Attack_Intro", .FrameInter = 0.05f, .Loop = false ,.ScaleToTexture = true });
	BossRender->CreateAnimation({ .AnimationName = "Attack",  .SpriteName = "Moon_Attack", .FrameInter = 0.08f, .Loop = true ,.ScaleToTexture = true });
	BossRender->CreateAnimation({ .AnimationName = "Attack_Outtro",  .SpriteName = "Moon_Attack_Outtro", .FrameInter = 0.05f, .Loop = false ,.ScaleToTexture = true });
	BossRender->CreateAnimation({ .AnimationName = "Death",  .SpriteName = "Moon_Death", .FrameInter = 0.08f, .Loop = true ,.ScaleToTexture = true });
	BossRender->ChangeAnimation("Intro0");


	BossCollision = CreateComponent<GameEngineCollision>(CupHeadCollisionOrder::Enemy);
	//230,400
	BossCollision->GetTransform()->SetLocalScale(float4(230, 400));
	BossCollision->SetColType(ColType::AABBBOX2D);

	// 수정 필요 - 보스 콜리전을 어떻게 하지??


	//FSM			
	// 																	
	//IDLE
	StartFuncPtr[static_cast<int>(MoonState::INTRO)] = std::bind(&Moon::Intro_Start, this);
	UpdateFuncPtr[static_cast<int>(MoonState::INTRO)] = std::bind(&Moon::Intro_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(MoonState::INTRO)] = std::bind(&Moon::Intro_End, this);

	//IDLE
	StartFuncPtr[static_cast<int>(MoonState::IDLE)] = std::bind(&Moon::Idle_Start, this);
	UpdateFuncPtr[static_cast<int>(MoonState::IDLE)] = std::bind(&Moon::Idle_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(MoonState::IDLE)] = std::bind(&Moon::Idle_End, this);

	//ATTACK
	StartFuncPtr[static_cast<int>(MoonState::ATTACK)] = std::bind(&Moon::Attack_Start, this);
	UpdateFuncPtr[static_cast<int>(MoonState::ATTACK)] = std::bind(&Moon::Attack_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(MoonState::ATTACK)] = std::bind(&Moon::Attack_End, this);

	//DEATH
	StartFuncPtr[static_cast<int>(MoonState::DEATH)] = std::bind(&Moon::Death_Start, this);
	UpdateFuncPtr[static_cast<int>(MoonState::DEATH)] = std::bind(&Moon::Death_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(MoonState::DEATH)] = std::bind(&Moon::Death_End, this);


	GetTransform()->SetLocalPosition(float4(0, 0, 600));
	//test

	if (false == GameEngineInput::IsKey("SpaceBar"))
	{
		GameEngineInput::CreateKey("SpaceBar", VK_SPACE);
	}
}

void Moon::Update(float _DeltaTime)
{
	if (nullptr == BossRender)
	{
		MsgAssert("Moon 랜더러가 생성되지 않았습니다.")
	}

	if (true == GameEngineInput::IsDown("SpaceBar"))
	{
		NextState = MoonState::DEATH;
	}
	UpdateState(_DeltaTime);
}


void Moon::UpdateState(float _DeltaTime)
{
	if (CurState != NextState)
	{
		// CurState에 대한 ending
		EndFuncPtr[static_cast<int>(CurState)]();

		// NextState에 대한 Start
		StartFuncPtr[static_cast<int>(NextState)]();

		// State변경
		CurState = NextState;
		return;
	}

	UpdateFuncPtr[static_cast<int>(CurState)](_DeltaTime);
}

void Moon::MakeStar(float _DeltaTime)
{
	StarInterval -= _DeltaTime;
	if (StarInterval < 0)
	{
		GetLevel()->CreateActor<MoonStar>(CupHeadActorOrder::EnemyWeapon);
		StarInterval = 1.0f;
	}
}

// FSM


void Moon::Intro_Start()
{
	BossRender->ChangeAnimation("Intro0");
	IntroAnimationIndex = 0;
	IntroAnimationTimer = 2.0f;
}

void Moon::Intro_Update(float _DeltaTime)
{
	switch (IntroAnimationIndex)
	{
	case 0:
	{
		if (true == BossRender->IsAnimationEnd())
		{
			++IntroAnimationIndex;
			BossRender->ChangeAnimation("Intro1");
			IntroAnimationTimer = 2.0f;
		}
		break;
	}
	case 1:
	{
		IntroAnimationTimer -= _DeltaTime;
		if (IntroAnimationTimer < 0.0f)
		{
			++IntroAnimationIndex;
			BossRender->ChangeAnimation("Intro2");
		}
		break;
	}
	case 2:
	{
		if (true == BossRender->IsAnimationEnd())
		{
			++IntroAnimationIndex;
			BossRender->ChangeAnimation("Intro3");
			IntroAnimationTimer = 2.0f;
		}
		break;
	}
	case 3:
	{
		IntroAnimationTimer -= _DeltaTime;
		if (IntroAnimationTimer < 0.0f)
		{
			++IntroAnimationIndex;
			BossRender->ChangeAnimation("Intro4");
		}
		break;
	}
	case 4:
	{
		if (true == BossRender->IsAnimationEnd())
		{
			++IntroAnimationIndex;
			NextState = MoonState::IDLE;
		}
		break;
	}
	default:
	{

		NextState = MoonState::IDLE;
		break;
	}
	}
}

void Moon::Intro_End()
{

}

void Moon::Idle_Start()
{
	BossRender->ChangeAnimation("Idle");
	IntervalTimer = 3.0f;
	StartPos = GetTransform()->GetLocalPosition();
	DestPos = float4(320, -20, 600);
	ResetLiveTime();
	BossCollision->GetTransform()->SetLocalPosition(float4(130, 0));
}
void Moon::Idle_Update(float _DeltaTime)
{
	MakeStar(_DeltaTime);
	GetTransform()->SetLocalPosition(float4::Zero.LerpClamp(StartPos, DestPos, GetLiveTime()));

	IntervalTimer -= _DeltaTime;
	if (IntervalTimer < 0.0f)
	{
		NextState = MoonState::ATTACK;
	}

}
void Moon::Idle_End()
{

}


void Moon::Attack_Start()
{
	BossRender->ChangeAnimation("Attack_Intro");
	IntervalTimer = 13.8f;
	isAttackIntroDone = false;
	isAttackDone = false;
	StartPos = GetTransform()->GetLocalPosition();
	DestPos = float4(240, -20, 600);
	BossCollision->GetTransform()->SetLocalPosition(float4(-100, 0));
	ResetLiveTime();
}
void Moon::Attack_Update(float _DeltaTime)
{
	MakeStar(_DeltaTime);
	IntervalTimer -= _DeltaTime;
	GetTransform()->SetLocalPosition(float4::Zero.LerpClamp(StartPos, DestPos, GetLiveTime()));
	if (false == isAttackIntroDone)
	{
		if (true == BossRender->IsAnimationEnd())
		{
			BossRender->ChangeAnimation("Attack");
			isAttackIntroDone = true;
		}
	}
	else
	{
		if (false == isAttackDone  && 0.0f > IntervalTimer)
		{
			if (0.0f > IntervalTimer)
			{
				isAttackDone = true;
				BossRender->ChangeAnimation("Attack_Outtro");
				StartPos = GetTransform()->GetLocalPosition();
				DestPos = float4(320, -20, 600);
				ResetLiveTime();

			}
		}
		else if (true == isAttackDone && BossRender->IsAnimationEnd())
		{
			NextState = MoonState::IDLE;

		}
	}
}
void Moon::Attack_End()
{
	DestPos = float4(320, -20, 600);
}

void Moon::Death_Start()
{
	BossRender->ChangeAnimation("Death");
}
void Moon::Death_Update(float _DeltaTime)
{
	//GetTransform()->SetLocalPosition(float4::Zero.LerpClamp(GetTransform()->GetLocalPosition(), DestPos, GetLiveTime()));
}
void Moon::Death_End()
{
}


void Moon::Attack(int _Dmg)
{
	BossRender->MakeBright();
	GameEnemy::Attack(_Dmg);
}
