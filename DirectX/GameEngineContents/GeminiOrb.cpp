#include "PrecompileHeader.h"
#include "GeminiOrb.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

GeminiOrb::GeminiOrb() 
{
}

GeminiOrb::~GeminiOrb() 
{
}

void GeminiOrb::MakeSprite()
{
	if (nullptr == GameEngineSprite::Find("Orb_Idle_Intro"))
	{

		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("stage1\\Boss\\Hilda\\Gemini\\Orb");

		// idle
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Idle\\Intro").GetFullPath(), "Orb_Idle_Intro");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Idle\\Loop").GetFullPath(), "Orb_Idle_Loop");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Idle\\Leave").GetFullPath(), "Orb_Idle_Leave");

		// attack
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Attack\\Intro").GetFullPath(), "Orb_Attack_Intro");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Attack\\Loop").GetFullPath(), "Orb_Attack_Loop");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Attack\\Leave").GetFullPath(), "Orb_Attack_Leave");

		// scatter
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Attack\\FX\\Large").GetFullPath(), "Orb_Attack_Scatter");

	}
}

void GeminiOrb::Start()
{
	MakeSprite();

	Orb = CreateComponent<GameEngineSpriteRenderer>();
	Orb->CreateAnimation({ .AnimationName = "IdleIntro",  .SpriteName = "Orb_Idle_Intro", .FrameInter = 0.05f, .Loop = false , .ScaleToImage = true });
	Orb->CreateAnimation({ .AnimationName = "IdleLoop",  .SpriteName = "Orb_Idle_Loop",.FrameInter = 0.05f, .Loop = true , .ScaleToImage = true });
	Orb->CreateAnimation({ .AnimationName = "IdleLeave",  .SpriteName = "Orb_Idle_Leave", .FrameInter = 0.05f, .Loop = false , .ScaleToImage = true });


	Orb->CreateAnimation({ .AnimationName = "AttackIntro",  .SpriteName = "Orb_Attack_Intro",.FrameInter = 0.05f, .Loop = false , .ScaleToImage = true });
	Orb->CreateAnimation({ .AnimationName = "AttackLoop",  .SpriteName = "Orb_Attack_Loop",.FrameInter = 0.05f, .Loop = true , .ScaleToImage = true });
	Orb->CreateAnimation({ .AnimationName = "AttackLeave",  .SpriteName = "Orb_Attack_Leave", .FrameInter = 0.05f, .Loop = false , .ScaleToImage = true });
	Orb->ChangeAnimation("IdleIntro");

	OrbAttackEffect = CreateComponent<GameEngineSpriteRenderer>();
	OrbAttackEffect->CreateAnimation({ .AnimationName = "Attack",  .SpriteName = "Orb_Attack_Scatter",.FrameInter = 0.05f, .Loop = true, .ScaleToImage = true });
	OrbAttackEffect->ChangeAnimation("Attack");
	OrbAttackEffect->Off();

	//GetTransform()->SetLocalPosition(float4(300.0f, 0));

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
	isLoop = false;
	isLeaveAnimation = false;
	Orb->ChangeAnimation("IdleIntro");
}
void GeminiOrb::Idle_Update(float _DeltaTime)
{
	if (false == isLoop && true == Orb->IsAnimationEnd())
	{
		isLoop = true;
		Orb->ChangeAnimation("IdleLoop");
	}
	if (true == isAttack && false == isLeaveAnimation)
	{
		Orb->ChangeAnimation("IdleLeave");
		isLeaveAnimation = true;
	}
	if (true == isLeaveAnimation && true == Orb->IsAnimationEnd())
	{
		NextState = OrbState::ATTACK;

	}
}
void GeminiOrb::Idle_End()
{
	Orb->Off();
}

void GeminiOrb::Attack_Start()
{
	Orb->On();
	isLoop = false;
	GetTransform()->SetLocalPosition(float4(-300, 0));
	Orb->ChangeAnimation("AttackIntro");
}
void GeminiOrb::Attack_Update(float _DeltaTime)
{
	if (false == isLoop && true == Orb->IsAnimationEnd())
	{
		isLoop = true;
		Orb->ChangeAnimation("AttackLoop");
		OrbAttackEffect->On();
	}

}
void GeminiOrb::Attack_End()
{
	Orb->ChangeAnimation("AttackLeave");
}