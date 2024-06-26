#include "PrecompileHeader.h"
#include "Taurus.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "GameContentsEnemyRenderer.h"


#include "HIldaBigCloudFX.h"
#include "HildaDashBackExplodeFX.h"

Taurus::Taurus()
{
}

Taurus::~Taurus()
{
}

void Taurus::MakeSprite()
{
	if (nullptr == GameEngineSprite::Find("Taurus_Idle"))
	{

		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources\\Texture\\stage1\\Boss\\Hilda\\Taurus");


		GameEngineSprite::LoadFolder("Taurus_Idle", NewDir.GetPlusFileName("Idle").GetFullPath());
		GameEngineSprite::LoadFolder("Taurus_Charge", NewDir.GetPlusFileName("Attack\\Charge").GetFullPath());
		GameEngineSprite::LoadFolder("Taurus_Attack", NewDir.GetPlusFileName("Attack\\Attack").GetFullPath());

	}
}


void Taurus::SettingRender()
{
	BossRender->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "Taurus_Idle", .FrameInter = 0.05f, .Loop = true , .ScaleToTexture = true });
	BossRender->CreateAnimation({ .AnimationName = "ChargeAttack", .SpriteName = "Taurus_Charge", .FrameInter = 0.05f, .Loop = false , .ScaleToTexture = true });
	BossRender->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "Taurus_Attack",  .FrameInter = 0.05f, .Loop = false , .ScaleToTexture = true });
	BossRender->ChangeAnimation("Idle");

}

void Taurus::SettingCollision()
{
	BossCollision->SetColType(ColType::AABBBOX2D);
	BossCollision->GetTransform()->SetLocalPosition(float4(10, 40));
}



void Taurus::Start()
{
	SetPhase(2);
	//MakeSprite();
	BossRender = CreateComponent<GameContentsEnemyRenderer>(CupHeadRendererOrder::Boss);
	SettingRender();

	BossCollision = CreateComponent<GameEngineCollision>(CupHeadCollisionOrder::Enemy);
	SettingCollision();

	//FSM																							
	//INTRO
	StartFuncPtr[static_cast<int>(TaurusState::IDLE)] = std::bind(&Taurus::Idle_Start, this);
	UpdateFuncPtr[static_cast<int>(TaurusState::IDLE)] = std::bind(&Taurus::Idle_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(TaurusState::IDLE)] = std::bind(&Taurus::Idle_End, this);

	//SHOOT
	StartFuncPtr[static_cast<int>(TaurusState::ATTACK)] = std::bind(&Taurus::Attack_Start, this);
	UpdateFuncPtr[static_cast<int>(TaurusState::ATTACK)] = std::bind(&Taurus::Attack_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(TaurusState::ATTACK)] = std::bind(&Taurus::Attack_End, this);

	GetTransform()->SetLocalPosition(float4(0, 0, 600));
}

void Taurus::Update(float _DeltaTime)
{
	if (nullptr == BossRender || nullptr == BossCollision)
	{
		MsgAssert("보스렌더 혹은 보스 콜리전이 생성되지 않았습니다");
	}
	// death
	if (GetHP() <= 0)
	{
		HildaDeath();
		return;
	}

	float4 Size = BossRender->GetTransform()->GetLocalScale();
	BossCollision->GetTransform()->SetLocalScale(float4(Size.x * 0.8f, Size.y * 0.6f, 1));
	UpdateState(_DeltaTime);
	CollisionPlayer(BossCollision);

}


void Taurus::UpdateState(float _DeltaTime)
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


void Taurus::Idle_Start()
{
	ResetLiveTime();
	BossRender->ChangeAnimation("Idle");
	//Boss->SetScaleToTexture("taurus_idle_0001.png");
}
void Taurus::Idle_Update(float _DeltaTime)
{
	IdleSoundInterval -= _DeltaTime;
	if (IdleSoundInterval < 0)
	{
		GameEngineSound::Play("blimp_taurus_idle_01.wav");
		IdleSoundInterval = 3.0f;
	}

	if (AttackInterval < GetLiveTime())
	{
		NextState = TaurusState::ATTACK;
	}

	GetTransform()->SetLocalPosition(GetHildaMove(_DeltaTime) + float4(300.0f, 0, 600));
}
void Taurus::Idle_End()
{

}

void Taurus::Attack_Start()
{
	ResetLiveTime();
	AttackInterval = GameEngineRandom::MainRandom.RandomFloat(5.0f, 8.0f);
	BossRender->ChangeAnimation("ChargeAttack");
	//Boss->SetScaleToTexture("taurus_attack_0012.png");

	CurPos = GetTransform()->GetLocalPosition();
	DestPos = CurPos + float4(-500, 0);
	isCharge = true;
	GameEngineSound::Play("blimp_taurus_attack_01.wav");
	IdleSoundInterval = 3.0f;
}
void Taurus::Attack_Update(float _DeltaTime)
{
	if (true == isCharge && true == BossRender->IsAnimationEnd())
	{
		isCharge = false;
		BossRender->ChangeAnimation("Attack");
	}
	else if (false == isCharge)
	{
		GetTransform()->SetLocalPosition(float4::Zero.LerpClamp(CurPos, DestPos, GetLiveTime() * 2));
		if (true == BossRender->IsAnimationEnd())
			//if (GetLiveTime() > 1.0f)
		{
			NextState = TaurusState::IDLE;

		}

	}
}
void Taurus::Attack_End()
{
	GetTransform()->SetLocalPosition(CurPos);
}

void Taurus::Attack(int _Dmg)
{
	BossRender->MakeBright();
	GameEnemy::Attack(_Dmg);
}
