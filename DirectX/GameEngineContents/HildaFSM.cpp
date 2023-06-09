#include "PrecompileHeader.h"
#include "Hilda.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineLevel.h>
//#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "GameContentsEnemyRenderer.h"

#include "HildaTornado.h"
#include "HildaHA.h"
#include "PlayerAirPlaneMode.h"
#include "HIldaBigCloudFX.h"



void Hilda::Intro_Start()
{
}
void Hilda::Intro_Update(float _DeltaTime)
{
	if (true == BossRender->IsAnimationEnd())
	{
		NextState = HildaState::IDLE;
	}
}
void Hilda::Intro_End()
{
}


void Hilda::Idle_Start()
{
	ResetLiveTime();
	BossRender->ChangeAnimation("Idle");

}

void Hilda::Idle_Update(float _DeltaTime)
{
	if (AttackInterval < GetLiveTime())
	{
		if (GetPhase() == 1)
		{
			NextState = HildaState::SHOOT;
		}
		else
		{
			NextState = GameEngineRandom::MainRandom.RandomInt(0, 3) > 2 ? HildaState::TORNADO : HildaState::SHOOT;
			AttackInterval = GameEngineRandom::MainRandom.RandomFloat(5.0f, 8.0f);
		}
	}
	GetTransform()->SetLocalPosition(GetHildaMove(_DeltaTime) + float4(300.0f,0, 600));
}

void Hilda::Idle_End()
{

}

void Hilda::Shoot_Start()
{
	BossRender->ChangeAnimation("shoot");
	std::shared_ptr<HildaHA> Ha = GetLevel()->CreateActor<HildaHA>(CupHeadActorOrder::EnemyWeapon);
	float4 Pos = GetTransform()->GetWorldPosition();
	Pos.z = 500;
	Ha->GetTransform()->SetLocalPosition(Pos);
}
void Hilda::Shoot_Update(float _DeltaTime)
{

	if (true == BossRender->IsAnimationEnd())
	{
		NextState = HildaState::IDLE;
	}
}
void Hilda::Shoot_End()
{
}

void Hilda::ChangePhase_Start()
{
	//bool isDashBackTurn = false;
	//bool isBackTurn = false;
	isDashBackTurn = false;
	isBackTurn = false;

	WaitingTime = 0.0f;
	BossRender->ChangeAnimation("Dash");
}
void Hilda::ChangePhase_Update(float _DeltaTime)
{

	if (false == isDashBackTurn && false == isBackTurn && true == BossRender->IsAnimationEnd())
	{
		BossRender->ChangeAnimation("DashBack");
		isDashBackTurn = true;
		DestPos = CurPos = GetTransform()->GetLocalPosition();
		DestPos.x = - (GameEngineWindow::GetScreenSize().hx() + BossRender->GetTransform()->GetLocalScale().hx());
		BossSmokeRender->ChangeAnimation("DashSmoke");
		BossSmokeRender->On();
	}

	else if (true == isDashBackTurn && false == isBackTurn)
	{
		WaitingTime += _DeltaTime;

		GetTransform()->SetLocalPosition(float4::Zero.LerpClamp(CurPos, DestPos, WaitingTime));
		if (WaitingTime >1.0f)
		{
			BossRender->ChangeAnimation("Summon");
			isBackTurn = true;
			WaitingTime = 0.0f;
			BossSmokeRender->Off();
		}
	}
	else if(true == isDashBackTurn && true == isBackTurn)
	{
		WaitingTime += _DeltaTime;
		GetTransform()->SetLocalPosition(float4::Zero.LerpClamp(DestPos, CurPos, WaitingTime * 0.95f));
		if (true == BossRender->IsAnimationEnd())
		{
			NextState = HildaState::IDLE;
		}

	}


}
void Hilda::ChangePhase_End()
{
	HildaBoss::HildaDeath();
	return;
}

void Hilda::Tornado_Start()
{
	// 토네이도 공격 생성
	BossRender->ChangeAnimation("Tornato");
	std::shared_ptr<HildaTornado> Tronado = GetLevel()->CreateActor<HildaTornado>(CupHeadActorOrder::EnemyWeapon);

	float4 Pos = GetTransform()->GetWorldPosition();
	Pos.z = 500;
	Pos.x -= BossRender->GetTransform()->GetLocalScale().hx();
	Tronado->GetTransform()->SetLocalPosition(Pos);

	// 토네이도 방향설정
	float4 tmpDir = PlayerAirPlaneMode::MainPlayer->GetTransform()->GetWorldPosition() - GetTransform()->GetWorldPosition();
	tmpDir.z = 0;
	tmpDir.Normalize();
	Tronado->SetTornadoDir(tmpDir);
}
void Hilda::Tornado_Update(float _DeltaTime)
{
	if (true == BossRender->IsAnimationEnd())
	{
		NextState = HildaState::IDLE;
	}
}
void Hilda::Tornado_End()
{
}