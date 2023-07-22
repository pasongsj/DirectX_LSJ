#include "PrecompileHeader.h"
#include "Hilda.h"
#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "Constellation.h"
#include "HildaDashExplodeFX.h"
#include "HildaDashBackExplodeFX.h"
#include "GameContentsEnemyRenderer.h"

Hilda::Hilda()
{
}

Hilda::~Hilda()
{
}

void Hilda::MakeSprite()
{
	if (nullptr == GameEngineSprite::Find("Hilda_Intro"))
	{

		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources\\Texture\\stage1\\Boss\\Hilda\\HildaBerg\\Normal");


		// intro
		GameEngineSprite::LoadFolder("Hilda_Intro", NewDir.GetPlusFileName("Intro\\Hilda").GetFullPath());
		// idle
		GameEngineSprite::LoadFolder("Hilda_Idle", NewDir.GetPlusFileName("Idle").GetFullPath());
		// shoot
		GameEngineSprite::LoadFolder("Hilda_Shoot", NewDir.GetPlusFileName("Laugh\\Hilda").GetFullPath());
		// Dash
		GameEngineSprite::LoadFolder("Hilda_Dash", NewDir.GetPlusFileName("ChangePhase\\Dash\\Dash").GetFullPath());
		// DashBack
		GameEngineSprite::LoadFolder("Hilda_DashBack", NewDir.GetPlusFileName("ChangePhase\\Dash\\DashBack").GetFullPath());
		// Summon
		GameEngineSprite::LoadFolder("Hilda_Summon", NewDir.GetPlusFileName("ChangePhase\\Summon").GetFullPath());
		// Tornato
		GameEngineSprite::LoadFolder("Hilda_Tornado", NewDir.GetPlusFileName("Tornado\\Hilda").GetFullPath());
		// ChangeBack
		GameEngineSprite::LoadFolder("Hilda_ChangeBack", NewDir.GetPlusFileName("ChangePhase\\ChangeBack").GetFullPath());
		// DashSmoke
		GameEngineSprite::LoadFolder("HildaChangePhaseDashSmoke", NewDir.GetPlusFileName("ChangePhase\\Dash\\SmokeFX").GetFullPath());

	}
}



void Hilda::SettingRender()
{
	BossRender->CreateAnimation({ .AnimationName = "Intro",  .SpriteName = "Hilda_Intro", .FrameInter = 0.05f, .Loop = false , .ScaleToTexture = true });
	BossRender->CreateAnimation({ .AnimationName = "SecondIntro",  .SpriteName = "Hilda_ChangeBack", .FrameInter = 0.05f, .Loop = false , .ScaleToTexture = true });
	BossRender->CreateAnimation({ .AnimationName = "Idle",  .SpriteName = "Hilda_Idle",.FrameInter = 0.05f, .Loop = true , .ScaleToTexture = true });
	BossRender->CreateAnimation({ .AnimationName = "shoot",  .SpriteName = "Hilda_Shoot",.FrameInter = 0.05f, .Loop = false , .ScaleToTexture = true });
	BossRender->CreateAnimation({ .AnimationName = "Dash",  .SpriteName = "Hilda_Dash", .FrameInter = 0.05f, .Loop = false , .ScaleToTexture = true });
	BossRender->CreateAnimation({ .AnimationName = "DashBack",  .SpriteName = "Hilda_DashBack", .FrameInter = 0.05f, .Loop = false , .ScaleToTexture = true });
	BossRender->CreateAnimation({ .AnimationName = "Summon",  .SpriteName = "Hilda_Summon", .FrameInter = 0.05f, .Loop = false , .ScaleToTexture = true });
	BossRender->CreateAnimation({ .AnimationName = "Tornato",  .SpriteName = "Hilda_Tornado",.FrameInter = 0.05f, .Loop = false , .ScaleToTexture = true });
	BossRender->ChangeAnimation("Intro");


	BossSmokeRender->CreateAnimation({ .AnimationName = "DashSmoke",  .SpriteName = "HildaChangePhaseDashSmoke",.FrameInter = 0.05f, .Loop = true , .ScaleToTexture = true });
	BossSmokeRender->GetTransform()->SetLocalPosition(float4(570, -30));
	BossSmokeRender->Off();
}

void Hilda::SettingCollision()
{
	BossBodyCollision->SetRenderScaleToCollision(BossRender);
	BossBodyCollision->SetColType(ColType::SPHERE2D);
	BossBodyCollision->SetName("HildaCollision");
	BossBodyCollision->GetTransform()->SetLocalPosition(float4(-10, 20));

	BossLegCollision->SetRenderScaleToCollision(BossRender);
	BossLegCollision->SetColType(ColType::AABBBOX2D);
	BossLegCollision->SetName("HildaCollision");
	BossLegCollision->GetTransform()->SetLocalPosition(float4(-25, -120));
	BossLegCollision->GetTransform()->SetLocalScale(float4(100, 150));

}


void Hilda::SetPhase(int _Phase)
{
	HildaBoss::SetPhase(_Phase);
	if (3 == _Phase || 5 == _Phase)
	{
		BossRender->ChangeAnimation("SecondIntro");
	}
}

//void Hilda::HildaDeath()
//{
//	if (HildaState::CHANGEPHASE != CurState && (1 == GetPhase() || 3 == GetPhase()))
//	{
//		NextState = HildaState::CHANGEPHASE;
//	}
//	else if (5 == GetPhase())
//	{
//		Death();
//	}
//	return;
//}


void Hilda::Start()
{
	SetPhase(1);
	//MakeSprite();
	// 랜더러 설정				

	BossRender = CreateComponent<GameContentsEnemyRenderer>(CupHeadRendererOrder::Boss);
	BossSmokeRender = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::Boss);
	SettingRender();


	BossBodyCollision = CreateComponent<GameEngineCollision>(CupHeadCollisionOrder::Enemy);
	BossLegCollision = CreateComponent<GameEngineCollision>(CupHeadCollisionOrder::Enemy);
	SettingCollision();


	//effect
	for (int i = 12; i < 16; i += 3)
	{

		BossRender->SetAnimationStartEvent("Summon", i, [this]
			{
				float4 Pos = GetTransform()->GetWorldPosition();
				Pos.z = 450;
				std::shared_ptr<HildaDashBackExplodeFX> ExplodeGx0 = GetLevel()->CreateActor< HildaDashBackExplodeFX>(CupHeadActorOrder::EnemyEffect);
				ExplodeGx0->GetTransform()->SetLocalPosition(Pos + float4(100, 0));

				std::shared_ptr<HildaDashBackExplodeFX> ExplodeGx1 = GetLevel()->CreateActor< HildaDashBackExplodeFX>(CupHeadActorOrder::EnemyEffect);
				ExplodeGx1->GetTransform()->SetLocalPosition(Pos + float4(150, GameEngineRandom::MainRandom.RandomFloat(20, 200)));

				std::shared_ptr<HildaDashBackExplodeFX> ExplodeGx2 = GetLevel()->CreateActor< HildaDashBackExplodeFX>(CupHeadActorOrder::EnemyEffect);
				ExplodeGx2->GetTransform()->SetLocalPosition(Pos + float4(200, GameEngineRandom::MainRandom.RandomFloat(-200, -20)));
			});
	}

	BossSmokeRender->SetAnimationStartEvent("DashSmoke", 5, [this]
		{
			std::shared_ptr< HildaDashExplodeFX> ExplodeGx = GetLevel()->CreateActor< HildaDashExplodeFX>(CupHeadActorOrder::EnemyEffect);
			float4 Pos = GetTransform()->GetWorldPosition();
			Pos.z = 450;
			ExplodeGx->GetTransform()->SetLocalPosition(Pos);
		});
	//FSM

	//INTRO
	StartFuncPtr[static_cast<int>(HildaState::INTRO)] = std::bind(&Hilda::Intro_Start, this);
	UpdateFuncPtr[static_cast<int>(HildaState::INTRO)] = std::bind(&Hilda::Intro_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(HildaState::INTRO)] = std::bind(&Hilda::Intro_End, this);

	//IDLE
	StartFuncPtr[static_cast<int>(HildaState::IDLE)] = std::bind(&Hilda::Idle_Start, this);
	UpdateFuncPtr[static_cast<int>(HildaState::IDLE)] = std::bind(&Hilda::Idle_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(HildaState::IDLE)] = std::bind(&Hilda::Idle_End, this);

	//SHOOT
	StartFuncPtr[static_cast<int>(HildaState::SHOOT)] = std::bind(&Hilda::Shoot_Start, this);
	UpdateFuncPtr[static_cast<int>(HildaState::SHOOT)] = std::bind(&Hilda::Shoot_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(HildaState::SHOOT)] = std::bind(&Hilda::Shoot_End, this);

	//CHANGEPHASE
	StartFuncPtr[static_cast<int>(HildaState::CHANGEPHASE)] = std::bind(&Hilda::ChangePhase_Start, this);
	UpdateFuncPtr[static_cast<int>(HildaState::CHANGEPHASE)] = std::bind(&Hilda::ChangePhase_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(HildaState::CHANGEPHASE)] = std::bind(&Hilda::ChangePhase_End, this);

	//TORNADO
	StartFuncPtr[static_cast<int>(HildaState::TORNADO)] = std::bind(&Hilda::Tornado_Start, this);
	UpdateFuncPtr[static_cast<int>(HildaState::TORNADO)] = std::bind(&Hilda::Tornado_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(HildaState::TORNADO)] = std::bind(&Hilda::Tornado_End, this);


	GetTransform()->SetLocalPosition(float4(300.0f, 0, 600));

	// TestCode
	if (false == GameEngineInput::IsKey("TestT"))
	{
		GameEngineInput::CreateKey("TestT", 'T');
		GameEngineInput::CreateKey("TestH", 'H');
		GameEngineInput::CreateKey("TestG", 'G');
	}

}

void Hilda::Update(float _DeltaTime)
{
	if (nullptr == BossRender || nullptr == BossBodyCollision)
	{
		MsgAssert("Hilda 랜더러 또는 콜리전이 제대로 생성되지 않았습니다.");
		return;
	}

	// 임시 테스트용
	if (true == GameEngineInput::IsPress("TestT"))
	{
		NextState = HildaState::TORNADO;
	}
	if (true == GameEngineInput::IsPress("TestH"))
	{
		NextState = HildaState::SHOOT;
	}
	if (true == GameEngineInput::IsPress("TestG"))
	{
		NextState = HildaState::CHANGEPHASE;
	}

	
	// death
	if (false == isHildaDeath && GetHP() <= 0)
	{
		if (HildaState::CHANGEPHASE != CurState && (1 == GetPhase() || 3 == GetPhase()))
		{
			NextState = HildaState::CHANGEPHASE;
		}
		else if (5 == GetPhase())
		{
			Death();
			return;
		}
	}

	BossBodyCollision->GetTransform()->SetLocalScale(BossRender->GetTransform()->GetLocalScale().half());
	UpdateState(_DeltaTime);
	CollisionPlayer(BossBodyCollision);
	CollisionPlayer(BossLegCollision);

	
}



void Hilda::UpdateState(float _DeltaTime)
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

void Hilda::Attack(int _Dmg)
{
	if (HildaState::CHANGEPHASE == CurState)
	{
		return;
	}
	BossRender->MakeBright();
	GameEnemy::Attack(_Dmg);
}
