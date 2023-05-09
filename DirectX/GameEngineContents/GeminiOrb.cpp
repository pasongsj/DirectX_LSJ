#include "PrecompileHeader.h"
#include "GeminiOrb.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

GeminiOrb::GeminiOrb() 
{
}

GeminiOrb::~GeminiOrb() 
{
}

void GeminiOrb::Start()
{
	Orb = CreateComponent<GameEngineSpriteRenderer>();
	Orb->CreateAnimation({ .AnimationName = "IdleIntro",  .TextureName = "orb_intro_000", .Start = 1, .End = 8,.InterTime = 0.05f, .Loop = false });
	Orb->CreateAnimation({ .AnimationName = "IdleLoop",  .TextureName = "orb_loop_00", .Start = 1, .End = 16,.InterTime = 0.05f, .Loop = true });
	Orb->CreateAnimation({ .AnimationName = "IdleLeave",  .TextureName = "orb_leave_00", .Start = 1, .End = 15,.InterTime = 0.05f, .Loop = false });


	Orb->CreateAnimation({ .AnimationName = "AttackIntro",  .TextureName = "orb_attack_intro_000", .Start = 1, .End = 7,.InterTime = 0.05f, .Loop = false });
	Orb->CreateAnimation({ .AnimationName = "AttackLoop",  .TextureName = "orb_attack_loop_000", .Start = 1, .End = 4,.InterTime = 0.05f, .Loop = true });
	Orb->CreateAnimation({ .AnimationName = "AttackLeave",  .TextureName = "orb_attack_leave_000", .Start = 1, .End = 7,.InterTime = 0.05f, .Loop = false });
	Orb->ChangeAnimation("IdleIntro");

	OrbAttackEffect = CreateComponent<GameEngineSpriteRenderer>();
	OrbAttackEffect->CreateAnimation({ .AnimationName = "Attack",  .TextureName = "orb_large_fx_000", .Start = 1, .End = 8,.InterTime = 0.05f, .Loop = true });
	OrbAttackEffect->ChangeAnimation("Attack");
	OrbAttackEffect->Off();

	GetTransform()->SetLocalPosition(float4(300.0f, 0));

	//FSM																							
	//INTRO
	StartFuncPtr[static_cast<int>(OrbState::IDLE)] = std::bind(&GeminiOrb::Idle_Start, this);
	UpdateFuncPtr[static_cast<int>(OrbState::IDLE)] = std::bind(&GeminiOrb::Idle_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(OrbState::IDLE)] = std::bind(&GeminiOrb::Idle_End, this);

	//ATTACK
	StartFuncPtr[static_cast<int>(OrbState::ATTACK)] = std::bind(&GeminiOrb::Attack_Start, this);
	UpdateFuncPtr[static_cast<int>(OrbState::ATTACK)] = std::bind(&GeminiOrb::Attack_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(OrbState::ATTACK)] = std::bind(&GeminiOrb::Attack_End, this);
}

void GeminiOrb::Update(float _DeltaTime)
{
	UpdateState(_DeltaTime);
}


void GeminiOrb::UpdateState(float _DeltaTime)
{
	if (CurState != NextState)
	{
		// CurState에 대한 ending
		EndFuncPtr[static_cast<int>(CurState)]();
		if (StateChangeInterval > 0)
		{
			StateChangeInterval -= _DeltaTime;
			return;
		}
		// NextState에 대한 Start
		StartFuncPtr[static_cast<int>(NextState)]();

		// State변경
		CurState = NextState;
		return;
	}

	UpdateFuncPtr[static_cast<int>(CurState)](_DeltaTime);
}




void GeminiOrb::Idle_Start()
{
	Orb->ChangeAnimation("IdleIntro");
}
void GeminiOrb::Idle_Update(float _DeltaTime)
{
	if (false == isLoop && true == Orb->IsAnimationEnd())
	{
		isLoop = true;
		Orb->ChangeAnimation("IdleLoop");
	}
	if (true == isAttack)
	{
		NextState = OrbState::ATTACK;
	}
}
void GeminiOrb::Idle_End()
{
	Orb->ChangeAnimation("IdleLeave");
	isLoop = false;
}

void GeminiOrb::Attack_Start()
{
	GetTransform()->SetLocalPosition(float4(-500, 0));
	Orb->ChangeAnimation("AttackIntro");
	OrbAttackEffect->On();
}
void GeminiOrb::Attack_Update(float _DeltaTime)
{
	if (false == isLoop && true == Orb->IsAnimationEnd())
	{
		isLoop = true;
		Orb->ChangeAnimation("AttackLoop");
	}

}
void GeminiOrb::Attack_End()
{
	Orb->ChangeAnimation("AttackLeave");
}