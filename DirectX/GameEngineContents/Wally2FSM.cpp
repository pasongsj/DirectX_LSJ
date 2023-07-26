#include "PrecompileHeader.h"
#include "Wally2.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineLevel.h>
//#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "GameContentsEnemyRenderer.h"
#include "Wally2_Egg.h"


void Wally2::Intro_Start()
{
	BossRender->ChangeAnimation("Idle");
	ResetLiveTime();
}

void Wally2::Intro_Update(float _DeltaTime)
{
	if (GetLiveTime() > 1.5f)
	{
		NextState = Wally2State::IDLE;
	}
}

void Wally2::Intro_End()
{
	EggSound = GameEngineSound::Play("flying_bird_small_bird_rotating_eggs_loop.wav");
	EggSound.SetVolume(0.2f);
}



void Wally2::Idle_Start()
{
	BossRender->ChangeAnimation("Idle",false);
	StartPos = GetTransform()->GetLocalPosition();
}

void Wally2::Idle_Update(float _DeltaTime)
{
	ToZeroMoveDuration += _DeltaTime * 2;
	if (ToZeroMoveDuration < 1.0f)
	{
		GetTransform()->SetLocalPosition(float4::Zero.LerpClamp(StartPos, DestPos, ToZeroMoveDuration));
		return;
	}
	MoveUpdate(_DeltaTime);
	
	if (GetHP() < 0)
	{
		NextState = Wally2State::DEATH;
		return;
	}
	if (true == isTransAnimatioin && true == BossRender->IsAnimationEnd())
	{
		BossRender->ChangeAnimation("Idle",false);

		isTransAnimatioin = false;
	}
	AttackInterval -= _DeltaTime;
	if (AttackInterval < 0)
	{
		NextState = Wally2State::SHOOT;
		AttackInterval = GameEngineRandom::MainRandom.RandomFloat(8.0f, 10.0f);
		return;
	}
}

void Wally2::Idle_End()
{
}


void Wally2::Shoot_Start()
{
	GetTransform()->SetLocalScale(float4::One);
	BossRender->ChangeAnimation("Shoot");
	GameEngineSound::Play("flying_bird_small_bird_shoot.wav");
}

void Wally2::Shoot_Update(float _DeltaTime)
{
	if (true == BossRender->IsAnimationEnd())
	{
		NextState = Wally2State::IDLE;
	}
}

void Wally2::Shoot_End()
{
}


void Wally2::Death_Start()
{
	BossRender->ChangeAnimation("Death_Trans");
	isDeathLoop = false;
	DeathLoopCount = 0;
	for (std::shared_ptr<Wally2_Egg> _Egg : Eggs)
	{
		_Egg->MakeDeath();
	}
	std::vector < std::shared_ptr<GameEngineActor>> Eggs;
	EggSound.Stop();
	CryingSound = GameEngineSound::Play("flying_bird_small_bird_death_cry.wav");
}

void Wally2::Death_Update(float _DeltaTime)
{
	if (false == isDeathLoop && true == BossRender->IsAnimationEnd())
	{
		isDeathLoop = true;
		BossRender->ChangeAnimation("Death_Loop");
	}
	else if (true == isDeathLoop && DeathLoopCount > 5)
	{
		GetTransform()->AddLocalPosition(float4::Right * _DeltaTime * 500.0f);
	}
	if (false == GetLevel()->GetMainCamera()->IsView(BossRender->GetTransform()->GetTransDataRef()))
	{
		CryingSound.Stop();
		isWallyDeath = true;
		Death();
		return;
	}
}

void Wally2::Death_End()
{
}
