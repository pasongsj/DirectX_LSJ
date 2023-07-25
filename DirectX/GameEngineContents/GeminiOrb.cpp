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
	//MakeSprite();

	Orb = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::EnemyWeapon);

	Orb->CreateAnimation({ .AnimationName = "AttackIntro",  .SpriteName = "Orb_Attack_Intro",.FrameInter = 0.05f, .Loop = false , .ScaleToTexture = true });
	Orb->CreateAnimation({ .AnimationName = "AttackLoop",  .SpriteName = "Orb_Attack_Loop",.FrameInter = 0.03f, .Loop = true , .ScaleToTexture = true });
	Orb->CreateAnimation({ .AnimationName = "AttackLeave",  .SpriteName = "Orb_Attack_Leave", .FrameInter = 0.05f, .Loop = false , .ScaleToTexture = true });
	Orb->ChangeAnimation("AttackIntro");

	OrbAttackEffect = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::EnemyEffect);
	OrbAttackEffect->CreateAnimation({ .AnimationName = "Attack",  .SpriteName = "Orb_Attack_Scatter",.FrameInter = 0.03f, .Loop = true, .ScaleToTexture = true });
	OrbAttackEffect->ChangeAnimation("Attack");
	OrbAttackEffect->Off();

	GetTransform()->SetLocalPosition(float4(0, 0, 500));
	GameEngineSound::Play("blimp_gemini_sphere_reappear_01.wav");

}

void GeminiOrb::Update(float _DeltaTime)
{
	if (nullptr == Orb || nullptr == OrbAttackEffect)
	{
		MsgAssert("Gemini Orb 랜더러가 제대로 생성되지 않았습니다.");
		return;
	}


	if (false == isLoop && true == Orb->IsAnimationEnd())
	{
		isLoop = true;
		Orb->ChangeAnimation("AttackLoop");
		OrbAttackEffect->On();
		ScatterSound = GameEngineSound::Play("blimp_gemini_projectile.wav");
		ScatterSound.SetLoop(-1);
		GameEngineSound::Play("blimp_gemini_sphere_attack.wav").SetVolume(0.5f);
		return;
	}
	else if (true == isLoop && false == isEnd)
	{
		ScatterInterval -= _DeltaTime;
		if (ScatterInterval < 0 /*&& GetLiveTime() < 6.5f*/)
		{
			std::shared_ptr<GeminiOrbScatter> Scatter = GetLevel()->CreateActor<GeminiOrbScatter>(CupHeadActorOrder::EnemyWeapon);

			float Theta = -GetLiveTime() * 1.5f + 45;
			float4 Dir = float4(cosf(Theta), sinf(Theta));
			Scatter->GetTransform()->SetLocalPosition(GetTransform()->GetWorldPosition() + Dir * 200);
			Scatter->GetTransform()->AddLocalRotation(float4(0, 0, (Theta)*GameEngineMath::RadToDeg));
			Scatter->SetDir(Dir);
			ScatterInterval += 0.15f;
		}
		if (GetLiveTime() > 8.0f)
		{
			isEnd = true;
		}
	}
	else if (true == isEnd)
	{
		Orb->ChangeAnimation("AttackLeave");
		ScatterSound.Stop();
		Death();
	}



	
}
//
//
//void GeminiOrb::Idle_Start()
//{
//	isLoop = false;
//	isLeaveAnimation = false;
//	Orb->ChangeAnimation("IdleIntro");
//}
//void GeminiOrb::Idle_Update(float _DeltaTime)
//{
//	if (false == isLoop && true == Orb->IsAnimationEnd())
//	{
//		isLoop = true;
//		Orb->ChangeAnimation("IdleLoop");
//	}
//	if (true == isAttack && false == isLeaveAnimation)
//	{
//		Orb->ChangeAnimation("IdleLeave");
//		isLeaveAnimation = true;
//	}
//	if (true == isLeaveAnimation && true == Orb->IsAnimationEnd())
//	{
//		NextState = OrbState::ATTACK;
//
//	}
//}
//void GeminiOrb::Idle_End()
//{
//	Orb->Off();
//}
//
//void GeminiOrb::Attack_Start()
//{
//	Orb->On();
//	isLoop = false;
//	GetTransform()->SetLocalPosition(float4(-300, 0));
//	Orb->ChangeAnimation("AttackIntro");
//	ResetLiveTime();
//}
//void GeminiOrb::Attack_Update(float _DeltaTime)
//{
//	ScatterInterval -= _DeltaTime;
//	if (false == isLoop && true == Orb->IsAnimationEnd())
//	{
//		isLoop = true;
//		Orb->ChangeAnimation("AttackLoop");
//		OrbAttackEffect->On();
//	}
//	if (ScatterInterval < 0 /*&& GetLiveTime() < 6.5f*/)
//	{
//		std::shared_ptr<GeminiOrbScatter> Scatter = GetLevel()->CreateActor<GeminiOrbScatter>(CupHeadActorOrder::Enemy);
//
//		float Theta = -GetLiveTime() * 1.5f + 45;
//		float4 Dir = float4(cosf(Theta), sinf(Theta));
//		Scatter->GetTransform()->SetLocalPosition(GetTransform()->GetWorldPosition() + Dir * 200);
//		Scatter->GetTransform()->AddLocalRotation(float4(0, 0, (Theta)*GameEngineMath::RadToDeg));
//		Scatter->SetDir(Dir);
//		ScatterInterval += 0.15f;
//	}
//	if (GetLiveTime() > 8.0f)
//	{
//		// 임시
//		//Death();
//	}
//}
//void GeminiOrb::Attack_End()
//{
//	Orb->ChangeAnimation("AttackLeave");
//}