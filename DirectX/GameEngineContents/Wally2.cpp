#include "PrecompileHeader.h"
#include "Wally2.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Wally2_Bullet.h"
#include "Wally1_House_Death.h"
#include "Wally2_Egg.h"

Wally2::Wally2()
{
}

Wally2::~Wally2()
{
}

void Wally2::MakeSprite()
{
	if(nullptr == GameEngineSprite::Find("Wally2_Idle"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources\\Texture\\stage2\\Boss\\Wally\\Phase 2");

		// intro
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Idle\\Idle").GetFullPath(), "Wally2_Idle");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Idle\\Blink").GetFullPath(), "Wally2_Blink");
		// Shoot
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Shoot").GetFullPath(), "Wally2_Shoot");
		// Dead
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Death\\Transition").GetFullPath(), "Wally2_Death_Trans");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Death\\Loop").GetFullPath(), "Wally2_Death_Loop");
		//Turn
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Turn\\Turn_Right").GetFullPath(), "Wally2_Turn_Right");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Turn\\Turn_Left").GetFullPath(), "Wally2_Turn_Left");
	}

}


void Wally2::Start()
{
	MakeSprite();

	BossRender = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::Boss);
	BossRender->CreateAnimation({ .AnimationName = "Idle",.SpriteName = "Wally2_Idle" , .FrameInter = 0.05f, .Loop = true,.ScaleToTexture = true });
	BossRender->CreateAnimation({ .AnimationName = "Blink",.SpriteName = "Wally2_Blink" , .FrameInter = 0.05f, .Loop = true,.ScaleToTexture = true });

	BossRender->CreateAnimation({ .AnimationName = "Shoot",.SpriteName = "Wally2_Shoot" , .FrameInter = 0.05f, .Loop = false,.ScaleToTexture = true });
	BossRender->SetAnimationStartEvent("Shoot", 12, [this]
		{
			std::shared_ptr< Wally2_Bullet> Bullet = GetLevel()->CreateActor< Wally2_Bullet>(CupHeadActorOrder::EnemyWeapon);
			Bullet->SetPos(GetTransform()->GetWorldPosition());
		});

	BossRender->CreateAnimation({ .AnimationName = "Death_Trans",.SpriteName = "Wally2_Death_Trans" , .FrameInter = 0.05f, .Loop = false,.ScaleToTexture = true });
	BossRender->CreateAnimation({ .AnimationName = "Death_Loop",.SpriteName = "Wally2_Death_Loop" , .FrameInter = 0.05f, .Loop = true,.ScaleToTexture = true });
	BossRender->SetAnimationStartEvent("Death_Loop", 3, [this] {++DeathLoopCount; });

	BossRender->CreateAnimation({ .AnimationName = "TurnRight",.SpriteName = "Wally2_Turn_Right" , .FrameInter = 0.05f, .Loop = false,.ScaleToTexture = true });
	BossRender->CreateAnimation({ .AnimationName = "TurnLeft",.SpriteName = "Wally2_Turn_Left" , .FrameInter = 0.05f, .Loop = false,.ScaleToTexture = true });


	BodyCollision = CreateComponent< GameEngineCollision>(CupHeadCollisionOrder::Enemy);
	BodyCollision->SetColType(ColType::SPHERE2D);
	BodyCollision->GetTransform()->SetLocalScale(float4(90, 0));
	BodyCollision->GetTransform()->SetLocalPosition(float4(0, -35));

	HeadCollision = CreateComponent< GameEngineCollision>(CupHeadCollisionOrder::Enemy);
	HeadCollision->SetColType(ColType::SPHERE2D);
	HeadCollision->GetTransform()->SetLocalScale(float4(90, 0));
	HeadCollision->GetTransform()->SetLocalPosition(float4(-30, 40));


	//INTRO
	StartFuncPtr[static_cast<int>(Wally2State::INTRO)] = std::bind(&Wally2::Intro_Start, this);
	UpdateFuncPtr[static_cast<int>(Wally2State::INTRO)] = std::bind(&Wally2::Intro_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(Wally2State::INTRO)] = std::bind(&Wally2::Intro_End, this);

	//IDLE
	StartFuncPtr[static_cast<int>(Wally2State::IDLE)] = std::bind(&Wally2::Idle_Start, this);
	UpdateFuncPtr[static_cast<int>(Wally2State::IDLE)] = std::bind(&Wally2::Idle_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(Wally2State::IDLE)] = std::bind(&Wally2::Idle_End, this);

	//SHOOT
	StartFuncPtr[static_cast<int>(Wally2State::SHOOT)] = std::bind(&Wally2::Shoot_Start, this);
	UpdateFuncPtr[static_cast<int>(Wally2State::SHOOT)] = std::bind(&Wally2::Shoot_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(Wally2State::SHOOT)] = std::bind(&Wally2::Shoot_End, this);

	//DEATH
	StartFuncPtr[static_cast<int>(Wally2State::DEATH)] = std::bind(&Wally2::Death_Start, this);
	UpdateFuncPtr[static_cast<int>(Wally2State::DEATH)] = std::bind(&Wally2::Death_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(Wally2State::DEATH)] = std::bind(&Wally2::Death_End, this);

	GetTransform()->SetLocalPosition(float4(100, 0, 600));


	std::shared_ptr<GameEngineActor> House = GetLevel()->CreateActor< Wally1_House_Death>(CupHeadActorOrder::EnemyEffect);
	float4 EffectPos = GetTransform()->GetWorldPosition();
	EffectPos.z = 450;
	House->GetTransform()->SetLocalPosition(EffectPos);
	Intro_Start();
	if (false == GameEngineInput::IsKey("PressF"))
	{
		GameEngineInput::CreateKey("PressF", 'F');
	}
	SettingEggs();
}

void Wally2::SettingEggs()
{
	EggController = GetLevel()->CreateActor<GameEngineActor>();
	EggController->GetTransform()->SetParent(GetTransform());
	EggController->GetTransform()->SetLocalPosition(float4::Zero);
	EggController->GetTransform()->SetWorldScale(float4::One);
	EggController->AccLiveTime(4.57421637f);
	//4.57421637
	float4 Pos = float4::Right * 100;
	for (int i = 0; i < 5; ++i)
	{
		std::shared_ptr<Wally2_Egg> Egg = GetLevel()->CreateActor<Wally2_Egg>();
		Egg->GetTransform()->SetParent(EggController->GetTransform());
		Egg->GetTransform()->SetLocalPosition(Pos.RotaitonZDegReturn(static_cast<float>(72 * i)) + float4(0, 0, -50));
		Eggs.push_back(Egg);
	}


}

void Wally2::Update(float _DeltaTime)
{
	if (GameEngineInput::IsPress("PressF"))
	{
		NextState = Wally2State::SHOOT;
	}
	EggController->GetTransform()->AddWorldRotation(float4(0, 0, _DeltaTime * 100));

	float4 Pos = float4::Right * 250 + float4::Right * 150 * sinf(EggController->GetLiveTime());
	for (int i = 0; i < 5; ++i)
	{
		Eggs[i]->GetTransform()->SetLocalPosition(Pos.RotaitonZDegReturn(static_cast<float>(72 * i))+ float4(0, 0, -50));
	}
	
	UpdateState(_DeltaTime);
}

void Wally2::UpdateState(float _DeltaTime)
{
	if (CurState != NextState)
	{
		// CurState에 대한 ending
		EndFuncPtr[static_cast<int>(CurState)]();

		// NextState에 대한 Start
		StartFuncPtr[static_cast<int>(NextState)]();

		// State변경
		CurState = NextState;
	}

	UpdateFuncPtr[static_cast<int>(CurState)](_DeltaTime);
}

void Wally2::MoveUpdate(float _DeltaTime)
{
	float4 CurPos = GetTransform()->GetLocalPosition();
	float4 NextPos = float4(100, 0, 600) + float4((sinf(MoveDuration * 1.0f)) * SpinSpeed * 2, -sinf(MoveDuration * 2.0f) * SpinSpeed);

	if (false == isTransAnimatioin && (NextPos.x - CurPos.x) * BeforDir < 0)
	{
		if (NextPos.x - CurPos.x > 0 && float4(-1, 1, 1, 1) != GetTransform()->GetLocalScale())
		{
			GetTransform()->SetLocalScale(float4(-1, 1, 1, 1));
			BossRender->ChangeAnimation("TurnLeft");
			isTransAnimatioin = true;

		}
		else if(NextPos.x - CurPos.x < 0 && float4::One != GetTransform()->GetLocalScale()) // 왼쪽에서 오른쪽으로
		{
			GetTransform()->SetLocalScale(float4::One);
			BossRender->ChangeAnimation("TurnLeft");
			isTransAnimatioin = true;
		}
	}
	BeforDir = (NextPos.x - CurPos.x) * 100;
	GetTransform()->SetLocalPosition(NextPos);
	MoveDuration += _DeltaTime;
}