#include "PrecompileHeader.h"
#include "Hilda.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "HildaTornado.h"
#include "HildaHA.h"



void Hilda::Intro_Start()
{
}
void Hilda::Intro_Update(float _DeltaTime)
{
	if (true == Boss->IsAnimationEnd())
	{
		NextState = HildaState::IDLE;
	}
}
void Hilda::Intro_End()
{
}


void Hilda::Idle_Start()
{
	Boss->ChangeAnimation("Idle");

}

void Hilda::Idle_Update(float _DeltaTime)
{
	IdleMoveTime += _DeltaTime;

	GetTransform()->SetLocalPosition(float4(cosf(IdleMoveTime * 2.5f) * SpinSpeed, CircleMove * (1 - sinf(IdleMoveTime * 2.5f)) * SpinSpeed) + float4(300.0f, 0)); // 힐다베르그  8자 움직임

	float degree = (IdleMoveTime * 2.5f) / GameEngineMath::PIE2 + GameEngineMath::PIE / 4;

	if (LastShare < degree)
	{
		int RandNum = GameEngineRandom::MainRandom.RandomInt(0, 9);
		if (0 == (RandNum & 1))
		{
			CircleMove = 1;
		}
		else
		{
			CircleMove = -1;
		}
		LastShare = static_cast<int>(degree) + 1;
	}
}

void Hilda::Idle_End()
{

}

void Hilda::Shoot_Start()
{
	Boss->ChangeAnimation("shoot");
	//std::shared_ptr<GameEngineActor> Ha = GetLevel()->CreateActor<HildaHA>();
	//Ha->GetTransform()->SetLocalPosition(GetTransform()->GetWorldPosition());
}
void Hilda::Shoot_Update(float _DeltaTime)
{

	if (true == Boss->IsAnimationEnd())
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
	Boss->ChangeAnimation("Dash");
}
void Hilda::ChangePhase_Update(float _DeltaTime)
{

	if (false == isDashBackTurn && false == isBackTurn && true == Boss->IsAnimationEnd())
	{
		Boss->ChangeAnimation("DashBack");
		isDashBackTurn = true;
		CurPos = GetTransform()->GetLocalPosition();
		DestPos = CurPos - float4(GameEngineWindow::GetScreenSize().x, 0);
	}

	else if (true == isDashBackTurn && false == isBackTurn)
	{
		WaitingTime += _DeltaTime;

		GetTransform()->SetLocalPosition(float4::Zero.LerpClamp(CurPos, DestPos, WaitingTime));
		if (WaitingTime >1.0f)
		{
			Boss->ChangeAnimation("Summon");
			isBackTurn = true;
			WaitingTime = 0.0f;
		}
	}
	else if(true == isDashBackTurn && true == isBackTurn)
	{
		WaitingTime += _DeltaTime;
		GetTransform()->SetLocalPosition(float4::Zero.LerpClamp(DestPos, CurPos, WaitingTime));
		if (true == Boss->IsAnimationEnd())
		{
			NextState = HildaState::IDLE;
		}

	}


}
void Hilda::ChangePhase_End()
{
}

void Hilda::Tornado_Start()
{
	Boss->ChangeAnimation("Tornato");
	//GetLevel()->CreateActor<HildaTornado>();
}
void Hilda::Tornado_Update(float _DeltaTime)
{
	if (true == Boss->IsAnimationEnd())
	{
		NextState = HildaState::IDLE;
	}
}
void Hilda::Tornado_End()
{
}