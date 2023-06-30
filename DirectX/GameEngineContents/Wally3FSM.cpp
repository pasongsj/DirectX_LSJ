#include "PrecompileHeader.h"
#include "Wally3.h"
#include "GameContentsEnemyRenderer.h"


//fsm
void Wally3::Intro_Start()
{
	BossRender->ChangeAnimation("Idle");
	MakeBirds();
}

void Wally3::Intro_Update(float _DeltaTime)
{
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
	MoveUpdate(_DeltaTime);
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

}

void Wally3::Garbage_Update(float _DeltaTime)
{
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
}

void Wally3::Regurgitate_Update(float _DeltaTime)
{

	if (false == isRegurgitateIntroDone && true == BossRender->IsAnimationEnd())
	{
		BossRender->ChangeAnimation("Regurgitate_Loop");
		isRegurgitateIntroDone = true;
	}
	else if (true == isRegurgitateIntroDone && false == isRegurgitateLoopDone && RegurgitateCount >= 20)
	{
		BossRender->ChangeAnimation("Regurgitate_Outro");
		isRegurgitateLoopDone = true;
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
}

void Wally3::Death_Update(float _DeltaTime)
{

}

void Wally3::Death_End()
{

}


