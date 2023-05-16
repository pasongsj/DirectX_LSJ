#include "PrecompileHeader.h"
#include "GeminiOrb.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "GeminiOrbScatter.h"

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
		NewDir.Move("ContentResources\\Texture\\stage1\\Boss\\Hilda\\Gemini\\Orb");

		// idle
		GameEngineSprite::LoadFolder("Orb_Idle_Intro", NewDir.GetPlusFileName("Idle\\Intro").GetFullPath());
		GameEngineSprite::LoadFolder("Orb_Idle_Loop", NewDir.GetPlusFileName("Idle\\Loop").GetFullPath());
		GameEngineSprite::LoadFolder("Orb_Idle_Leave", NewDir.GetPlusFileName("Idle\\Leave").GetFullPath());

		// attack																											
		GameEngineSprite::LoadFolder("Orb_Attack_Intro", NewDir.GetPlusFileName("Attack\\Intro").GetFullPath());
		GameEngineSprite::LoadFolder("Orb_Attack_Loop", NewDir.GetPlusFileName("Attack\\Loop").GetFullPath());
		GameEngineSprite::LoadFolder("Orb_Attack_Leave", NewDir.GetPlusFileName("Attack\\Leave").GetFullPath());

		// scatter																										 
		GameEngineSprite::LoadFolder("Orb_Attack_Scatter", NewDir.GetPlusFileName("Attack\\FX\\Large").GetFullPath());

	}
}

void GeminiOrb::Start()
{
	MakeSprite();

	Orb = CreateComponent<GameEngineSpriteRenderer>();
	Orb->CreateAnimation({ .AnimationName = "IdleIntro",  .SpriteName = "Orb_Idle_Intro", .FrameInter = 0.05f, .Loop = false , .ScaleToTexture = true });
	Orb->CreateAnimation({ .AnimationName = "IdleLoop",  .SpriteName = "Orb_Idle_Loop",.FrameInter = 0.05f, .Loop = true , .ScaleToTexture = true });
	Orb->CreateAnimation({ .AnimationName = "IdleLeave",  .SpriteName = "Orb_Idle_Leave", .FrameInter = 0.05f, .Loop = false , .ScaleToTexture = true });


	Orb->CreateAnimation({ .AnimationName = "AttackIntro",  .SpriteName = "Orb_Attack_Intro",.FrameInter = 0.05f, .Loop = false , .ScaleToTexture = true });
	Orb->CreateAnimation({ .AnimationName = "AttackLoop",  .SpriteName = "Orb_Attack_Loop",.FrameInter = 0.03f, .Loop = true , .ScaleToTexture = true });
	Orb->CreateAnimation({ .AnimationName = "AttackLeave",  .SpriteName = "Orb_Attack_Leave", .FrameInter = 0.05f, .Loop = false , .ScaleToTexture = true });
	Orb->ChangeAnimation("IdleIntro");

	OrbAttackEffect = CreateComponent<GameEngineSpriteRenderer>();
	OrbAttackEffect->CreateAnimation({ .AnimationName = "Attack",  .SpriteName = "Orb_Attack_Scatter",.FrameInter = 0.03f, .Loop = true, .ScaleToTexture = true });
	OrbAttackEffect->ChangeAnimation("Attack");
	OrbAttackEffect->Off();


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
	if (nullptr == Orb || nullptr == OrbAttackEffect)
	{
		MsgAssert("Gemini Orb 랜더러가 제대로 생성되지 않았습니다.");
		return;
	}

	if (nullptr != GeminiController && true == GeminiController->IsDeath())
	{
		Death();
	}
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
	ResetLiveTime();
}
void GeminiOrb::Attack_Update(float _DeltaTime)
{
	ScatterInterval -= _DeltaTime;
	if (false == isLoop && true == Orb->IsAnimationEnd())
	{
		isLoop = true;
		Orb->ChangeAnimation("AttackLoop");
		OrbAttackEffect->On();
	}
	if (ScatterInterval < 0 /*&& GetLiveTime() < 6.5f*/)
	{
		std::shared_ptr<GeminiOrbScatter> Scatter = GetLevel()->CreateActor<GeminiOrbScatter>();

		float Theta = -GetLiveTime() * 1.5f + 45;
		float4 Dir = float4(cosf(Theta), sinf(Theta));
		Scatter->GetTransform()->SetLocalPosition(GetTransform()->GetWorldPosition() + Dir * 200);
		Scatter->GetTransform()->AddLocalRotation(float4(0, 0, (Theta)*GameEngineMath::RadToDeg));
		Scatter->SetDir(Dir);
		ScatterInterval = 0.12f;
	}
	if (GetLiveTime() > 8.0f)
	{
		// 임시
		//Death();
	}
}
void GeminiOrb::Attack_End()
{
	Orb->ChangeAnimation("AttackLeave");
}