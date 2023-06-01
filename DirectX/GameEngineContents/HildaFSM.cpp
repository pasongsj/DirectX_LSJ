#include "PrecompileHeader.h"
#include "Hilda.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "HildaTornado.h"
#include "HildaHA.h"
#include "PlayerAirPlaneMode.h"
#include "HildaDashBackExplodeFX.h"



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
	GetTransform()->SetLocalPosition(GetHildaMove(_DeltaTime) + float4(300.0f, 0));
}

void Hilda::Idle_End()
{

}

void Hilda::Shoot_Start()
{
	BossRender->ChangeAnimation("shoot");
	std::shared_ptr<GameEngineActor> Ha = GetLevel()->CreateActor<HildaHA>(CupHeadActorOrder::Enemy);
	Ha->GetTransform()->SetLocalPosition(GetTransform()->GetWorldPosition());
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
		//if (WaitingTime < 0.5f)
		//{
		//	return;
		//}
		GetTransform()->SetLocalPosition(float4::Zero.LerpClamp(DestPos, CurPos, WaitingTime * 0.95f));
		if (true == BossRender->IsAnimationEnd())
		{
			NextState = HildaState::IDLE;
		}

	}


}
void Hilda::ChangePhase_End()
{
	std::shared_ptr<HildaDashBackExplodeFX> ExplodeGx0 = GetLevel()->CreateActor< HildaDashBackExplodeFX>(CupHeadActorOrder::EnemyEffect);
	ExplodeGx0->GetTransform()->SetLocalPosition(GetTransform()->GetWorldPosition() + float4(110, 0, -50));
	ExplodeGx0->MakeBigFX(1.3f);
	Death();
	return;
}

void Hilda::Tornado_Start()
{
	BossRender->ChangeAnimation("Tornato");
	std::shared_ptr<HildaTornado> Tronado = GetLevel()->CreateActor<HildaTornado>(CupHeadActorOrder::Enemy);
	Tronado->GetTransform()->SetLocalPosition(GetTransform()->GetWorldPosition() - float4(BossRender->GetTransform()->GetLocalScale().hx(), 0));
	float4 tmpDir = PlayerAirPlaneMode::MainPlayer->GetTransform()->GetWorldPosition() - GetTransform()->GetWorldPosition();
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