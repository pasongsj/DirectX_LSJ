#include "PrecompileHeader.h"
#include "Wally1.h"
#include "ContentsSortRenderer.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineCollision.h>


void Wally1::CuckooIntro_Start()
{
	FeetRender->ChangeAnimation("Feet_Pendulum_Intro");
	FeetRender->SetLocalSortPosition(float4(-20, -85), SortRenderer::TOP);


	HouseRender->ChangeAnimation("House_Intro");

	HeadRender->ChangeAnimation("Head_Cuckoo_Intro");
	HeadRender->SetLocalSortPosition(float4(-45, 35), SortRenderer::RIGHT);

	HeadCollision->Off();
	GameEngineSound::Play("flying_bird_intro_full.wav");
}

void Wally1::CuckooIntro_Update(float _DeltaTime)
{
	if (IntroCount >= 3)
	{
		NextState = Wally1State::INTRO;
	}
}

void Wally1::CuckooIntro_End()
{
	HeadCollision->On();
}



void Wally1::Intro_Start()
{
	FeetRender->ChangeAnimation("Feet_Intro");
	FeetRender->SetLocalSortPosition(float4(-60, -15), SortRenderer::TOP);

	HouseRender->ChangeAnimation("House_Intro",false);

	HeadRender->ChangeAnimation("Head_Intro");
	HeadRender->SetLocalSortPosition(float4(-57, 0), SortRenderer::RIGHT);

	HeadCollision->GetTransform()->SetLocalPosition(float4(-200, 0));
	isFeetIntroEnd = false;

}

void Wally1::Intro_Update(float _DeltaTime)
{
	if (false == isFeetIntroEnd && true == FeetRender->IsAnimationEnd())
	{
		FeetRender->ChangeAnimation("Feet_Idle",false);
		FeetRender->Reset();
		FeetRender->GetTransform()->SetLocalPosition(float4(-20, -120));
	}
	if (true == HeadRender->IsAnimationEnd())
	{
		NextState = Wally1State::IDLE;
	}
}

void Wally1::Intro_End()
{
}


void Wally1::Idle_Start()
{

	FeetRender->ChangeAnimation("Feet_Idle",false);
	FeetRender->Reset();
	FeetRender->GetTransform()->SetLocalPosition(float4(-20, -120));
	HouseRender->ChangeAnimation("House_Intro", false);
	HouseRender->GetTransform()->SetLocalPosition(float4::Zero);

	HeadRender->ChangeAnimation("Head_Idle",false);
	HeadRender->SetLocalSortPosition(float4(-80, -10), SortRenderer::RIGHT);


	HeadCollision->GetTransform()->SetLocalPosition(float4(-200, 0));
}

void Wally1::Idle_Update(float _DeltaTime)
{
	AttackInterval -= _DeltaTime;
	MoveUpdate(_DeltaTime);
	FlappyBirdSpone(_DeltaTime);
	if (GetHP() <= 0)
	{
		NextState = Wally1State::STEAM;
		return;
	}
	if (AttackInterval < 0)
	{
		if (false == static_cast<bool>(GameEngineRandom::MainRandom.RandomInt(0, 5)))
		{
			NextState = Wally1State::HANDGUN;
		}
		else
		{
			NextState = Wally1State::BARF;
		}
		AttackInterval = GameEngineRandom::MainRandom.RandomFloat(0.5f, 1.5f);
		return;
	}
}

void Wally1::Idle_End()
{
}


void Wally1::Barf_Start()
{
	FeetRender->ChangeAnimation("Feet_Barf", false);
	FeetRender->SetLocalSortPosition(float4(120,-45),SortRenderer::RTOP);
	HouseRender->ChangeAnimation("House_Intro", false);
	HeadRender->ChangeAnimation("Head_Barf");
	HeadRender->SetLocalSortPosition(float4(-80, -5), SortRenderer::RIGHT);

	HeadCollision->GetTransform()->SetLocalPosition(float4(-300, 0));
	GameEngineSound::Play("flying_bird_bird_spit.wav");

}

void Wally1::Barf_Update(float _DeltaTime)
{
	FlappyBirdSpone(_DeltaTime);
	if (true == HeadRender->IsAnimationEnd())
	{
		NextState = Wally1State::IDLE;
	}
}

void Wally1::Barf_End()
{
}

void Wally1::HandGun_Start()
{
	FeetRender->ChangeAnimation("Feet_Idle", false);
	FeetRender->Reset();
	FeetRender->GetTransform()->SetLocalPosition(float4(-20, -120));
	HeadRender->ChangeAnimation("Head_HandGun");
	HeadRender->SetLocalSortPosition(float4(20, 5), SortRenderer::RIGHT);
	HouseRender->ChangeAnimation("House_Intro", false);
	GameEngineSound::Play("flying_bird_lasers.wav");

}

void Wally1::HandGun_Update(float _DeltaTime)
{
	FlappyBirdSpone(_DeltaTime);
	if (true == HeadRender->IsAnimationEnd())
	{
		NextState = Wally1State::IDLE;
	}
}

void Wally1::HandGun_End()
{
}


void Wally1::Steam_Start()
{
	FeetRender->ChangeAnimation("Feet_Idle", false);
	FeetRender->Reset();
	FeetRender->GetTransform()->SetLocalPosition(float4(-20, -120));
	HeadRender->ChangeAnimation("Head_Steam");
	HeadRender->SetLocalSortPosition(float4(-70, -90), SortRenderer::RBOT);
	HouseRender->ChangeAnimation("House_Intro", false);
	GameEngineSound::Play("flying_bird_whistle.wav");

}

void Wally1::Steam_Update(float _DeltaTime)
{
	FlappyBirdSpone(_DeltaTime);
	if (true == HeadRender->IsAnimationEnd())
	{
		NextState = Wally1State::FLAP;
	}
}

void Wally1::Steam_End()
{
}


void Wally1::Flap_Start()
{
	isFlapIntroDone = false;
	isFlapLoopDone = false;
	FeetRender->Off();
	HeadRender->Off();
	HouseRender->ChangeAnimation("Flap_Intro");
	GameEngineSound::Play("flying_bird_bird_feathers_start.wav");
}

void Wally1::Flap_Update(float _DeltaTime)
{
	FlappyBirdSpone(_DeltaTime);
	if (false == isFlapIntroDone)
	{
		if(true == HouseRender->IsAnimationEnd())
		{
			HouseRender->ChangeAnimation("Flap_Loop");
			FlapLoopCout = 0;
			isFlapIntroDone = true;
			GameEngineSound::Play("flying_bird_bird_feathers_loop.wav").SetVolume(0.5f);
		}
	}
	else
	{
		if (false == isFlapLoopDone)
		{
			FeatherInterval -= _DeltaTime;
			if (FeatherInterval < 0)
			{
				FeatherInterval = 0.25f;
				MakeFeather();
			}
			if (FlapLoopCout >= 15)
			{
				HouseRender->ChangeAnimation("Flap_Outro");
				isFlapLoopDone = true;
			}
		}																						
		else																					
		{
			if (true == HouseRender->IsAnimationEnd())
			{
				NextState = Wally1State::PANT;
				//NextState = Wally1State::CHANGEPHASE; 추후 변경
			}
		}
	}

}

void Wally1::Flap_End()
{
	FeetRender->On();
	HeadRender->On();
}


void Wally1::Pant_Start()
{
	FeetRender->ChangeAnimation("Feet_Idle", false);
	FeetRender->Reset();
	FeetRender->GetTransform()->SetLocalPosition(float4(-20, -120));
	HouseRender->ChangeAnimation("House_Intro", false);
	HeadRender->ChangeAnimation("Head_Pant", false);
	HeadRender->SetLocalSortPosition(float4(-80, 115), SortRenderer::RTOP);
	PantLoopCount = 0;
	++PantCount;
	GameEngineSound::Play("flying_bird_bird_feathers_hesitate.wav");
}

void Wally1::Pant_Update(float _DeltaTime)
{
	if (PantLoopCount >= 3 && PantCount == 2)
	{
		NextState = Wally1State::CHANGEPHASE;

	}
	else if (PantLoopCount >= 5 && PantCount < 2)
	{
		NextState = Wally1State::FLAP;
	}
}

void Wally1::Pant_End()
{
}


void Wally1::ChangePhase_Start()
{
	FeetRender->Off();
	HeadRender->Off();
	HouseRender->ChangeAnimation("Dead");
	float4 Pos = HouseRender->GetTransform()->GetLocalPosition();
	Pos.y += HouseRender->GetTransform()->GetLocalScale().hy() - 50;
	HouseRender->SetLocalSortPosition(Pos, SortRenderer::TOP);

}

void Wally1::ChangePhase_Update(float _DeltaTime)
{
	if (true == HouseRender->IsAnimationEnd())
	{
		//NextState = Wally1State::IDLE;
		isWallyDeath = true;
		Death();
	}
}

void Wally1::ChangePhase_End()
{
	HouseRender->Reset();
	HeadRender->On();
	FeetRender->On();
}
