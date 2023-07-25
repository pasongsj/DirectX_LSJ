#include "PrecompileHeader.h"
#include "Wally3.h"
#include "GameContentsEnemyRenderer.h"
#include <GameEngineBase/GameEngineRandom.h>

//fsm
void Wally3::Intro_Start()
{
	BossRender->ChangeAnimation("Idle");
	MakeBirds();
	StartDuration = 0.0f;
}

void Wally3::Intro_Update(float _DeltaTime)
{
	StartDuration += _DeltaTime;
	GetTransform()->SetLocalPosition(float4::Zero.LerpClamp(StartPos, float4(0, -210, 600), StartDuration/2));
	if (GetLiveTime() > 2.0f)
	{
		NextState = Wally3State::IDLE;
	}
}

void Wally3::Intro_End()
{

}



void Wally3::Idle_Start()
{
	BossRender->ChangeAnimation("Idle");
	MakeBirds();
}

void Wally3::Idle_Update(float _DeltaTime)
{
	if (GetHP() < 0)
	{
		NextState = Wally3State::DEATH;
		return;
	}
	MoveUpdate(_DeltaTime);
	AttackInterval -= _DeltaTime;
	if (AttackInterval < 0)
	{
		if (false == static_cast<bool>(GameEngineRandom::MainRandom.RandomInt(0, 2)))
		{
			NextState = Wally3State::REGURGITATE;
		}
		else
		{ 
			NextState = Wally3State::GARBAGE;
		}
		AttackInterval = GameEngineRandom::MainRandom.RandomFloat(8.0f, 10.0f);
	}
}

void Wally3::Idle_End()
{

}

void Wally3::Garbage_Start()
{
	BossRender->ChangeAnimation("Garbage_Intro");
	isGarbageIntroDone = false;
	isGarbageLoopDone = false;
	GarbageCount = 0;
	GameEngineSound::Play("bird_stretcher_garbage_start.wav");

}

void Wally3::Garbage_Update(float _DeltaTime)
{
	MoveUpdate(_DeltaTime);

	if (false == isGarbageIntroDone && true == BossRender->IsAnimationEnd())
	{
		BossRender->ChangeAnimation("Garbage_Loop");
		isGarbageIntroDone = true;
	}
	else if (true == isGarbageIntroDone && false == isGarbageLoopDone && GarbageCount >= 5)
	{
		BossRender->ChangeAnimation("Garbage_Outro");
		isGarbageLoopDone = true;
	}
	else if (true == isGarbageLoopDone && true == BossRender->IsAnimationEnd())
	{
		NextState = Wally3State::IDLE;
	}
}

void Wally3::Garbage_End()
{

}


void Wally3::Regurgitate_Start()
{
	BossRender->ChangeAnimation("Regurgitate_Intro");
	isRegurgitateIntroDone = false;
	isRegurgitateLoopDone = false;
	RegurgitateCount = 0;
	GameEngineSound::Play("bird_stretcher_garbage_regurgitate_start.wav");
}

void Wally3::Regurgitate_Update(float _DeltaTime)
{

	if (false == isRegurgitateIntroDone && true == BossRender->IsAnimationEnd())
	{
		BossRender->ChangeAnimation("Regurgitate_Loop");
		isRegurgitateIntroDone = true;
	}
	else if (true == isRegurgitateIntroDone && false == isRegurgitateLoopDone && RegurgitateCount >= 7)
	{
		BossRender->ChangeAnimation("Regurgitate_Outro");
		isRegurgitateLoopDone = true;
		GameEngineSound::Play("bird_stretcher_garbage_regurgitate_end.wav");
	}
	else if (true == isRegurgitateLoopDone && true == BossRender->IsAnimationEnd())
	{
		NextState = Wally3State::IDLE;
	}
}

void Wally3::Regurgitate_End()
{

}


void Wally3::Death_Start()
{
	BossRender->ChangeAnimation("Death");
	RightBird->Death();
	LeftBird->Death();
	RightBird = nullptr;
	LeftBird = nullptr;
	GameEngineSound::Play("bird_stretcher_death.wav");
}

void Wally3::Death_Update(float _DeltaTime)
{
	isWallyDeath = true;
}

void Wally3::Death_End()
{

}


