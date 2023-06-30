#include "PrecompileHeader.h"
#include "Wally3.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "GameContentsEnemyRenderer.h"
#include "Wally3_LeftBird.h"
#include "Wally3_RightBird.h"

#include "Wally3_Salt.h"
#include "Wally3_Pepper.h"
#include "Wally3_Garbages.h"

Wally3::Wally3()
{
}

Wally3::~Wally3()
{
}

void Wally3::MakeSprite()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentResources");
	Dir.Move("ContentResources\\Texture\\stage2\\Boss\\Wally\\Phase 3");


	if (nullptr == GameEngineSprite::Find("Wally3_Idle"))
	{
		// Garbage
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Garbage\\Intro").GetFullPath(), "Wally3_Garbage_Intro");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Garbage\\Loop").GetFullPath(), "Wally3_Garbage_Loop");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Garbage\\Outro").GetFullPath(), "Wally3_Garbage_Outro");
		// Idle
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Idle").GetFullPath(), "Wally3_Idle");
		// Dead
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Death\\Death").GetFullPath(), "Wally3_Death");
		// Regurgitate
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Regurgitate\\Intro").GetFullPath(), "Wally3_Regurgitate_Intro");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Regurgitate\\Loop").GetFullPath(), "Wally3_Regurgitate_Loop");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Regurgitate\\Outro").GetFullPath(), "Wally3_Regurgitate_Outro");
	}

}


void Wally3::Start()
{
	MakeSprite();
	BossRender = CreateComponent<GameContentsEnemyRenderer>(CupHeadRendererOrder::Boss);
	BossRender->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "Wally3_Idle",.FrameInter = 0.05f,.Loop = true, .ScaleToTexture = true });

	BossRender->CreateAnimation({ .AnimationName = "Garbage_Intro", .SpriteName = "Wally3_Garbage_Intro",.FrameInter = 0.05f,.Loop = false, .ScaleToTexture = true });
	BossRender->CreateAnimation({ .AnimationName = "Garbage_Loop", .SpriteName = "Wally3_Garbage_Loop",.FrameInter = 0.05f,.Loop = true, .ScaleToTexture = true });
	BossRender->SetAnimationStartEvent("Garbage_Loop", 15, [this] {++GarbageCount; });
	BossRender->SetAnimationStartEvent("Garbage_Loop", 10, [this] {
		std::shared_ptr< Wally3_Garbages> Garbage = GetLevel()->CreateActor< Wally3_Garbages>(CupHeadActorOrder::EnemyWeapon);
		Garbage->GetTransform()->SetLocalPosition(GetTransform()->GetWorldPosition() + float4(200, 150));
		Garbage->Setting(GameEngineRandom::MainRandom.RandomInt(1,3));
		if (2 == GarbageCount)
		{
			Garbage->Setting(0);
		}
		});
	BossRender->CreateAnimation({ .AnimationName = "Garbage_Outro", .SpriteName = "Wally3_Garbage_Outro",.FrameInter = 0.05f,.Loop = false, .ScaleToTexture = true });

	BossRender->CreateAnimation({ .AnimationName = "Regurgitate_Intro", .SpriteName = "Wally3_Regurgitate_Intro",.FrameInter = 0.05f,.Loop = false, .ScaleToTexture = true });
	BossRender->CreateAnimation({ .AnimationName = "Regurgitate_Loop", .SpriteName = "Wally3_Regurgitate_Loop",.FrameInter = 0.05f,.Loop = true, .ScaleToTexture = true });
	BossRender->SetAnimationStartEvent("Regurgitate_Loop", 4, [this] {++RegurgitateCount; });
	BossRender->CreateAnimation({ .AnimationName = "Regurgitate_Outro", .SpriteName = "Wally3_Regurgitate_Outro",.FrameInter = 0.05f,.Loop = false, .ScaleToTexture = true });
	
	BossRender->CreateAnimation({ .AnimationName = "Death", .SpriteName = "Wally3_Death",.FrameInter = 0.05f,.Loop = true, .ScaleToTexture = true });
	BossRender->SetAnimationStartEvent("Death", 8, [this]
		{
			std::shared_ptr<GameEngineActor> salt = GetLevel()->CreateActor< Wally3_Salt>(CupHeadActorOrder::EnemyEffect);
			salt->GetTransform()->SetLocalPosition(GetTransform()->GetWorldPosition() + float4(-230,90));
			std::shared_ptr<GameEngineActor> pepper = GetLevel()->CreateActor< Wally3_Pepper>(CupHeadActorOrder::EnemyEffect);
			pepper->GetTransform()->SetLocalPosition(GetTransform()->GetWorldPosition() + float4(200, 90));

		});	
	BossRender->SetAnimationStartEvent("Death", 0, [this]
		{
			std::shared_ptr<GameEngineActor> salt = GetLevel()->CreateActor< Wally3_Salt>(CupHeadActorOrder::EnemyEffect);
			salt->GetTransform()->SetLocalPosition(GetTransform()->GetWorldPosition() + float4(-230,90));
			std::shared_ptr<GameEngineActor> pepper = GetLevel()->CreateActor< Wally3_Pepper>(CupHeadActorOrder::EnemyEffect);
			pepper->GetTransform()->SetLocalPosition(GetTransform()->GetWorldPosition() + float4(200, 90));

		});
	Intro_Start();

	//INTRO
	StartFuncPtr[static_cast<int>(Wally3State::INTRO)] = std::bind(&Wally3::Intro_Start, this);
	UpdateFuncPtr[static_cast<int>(Wally3State::INTRO)] = std::bind(&Wally3::Intro_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(Wally3State::INTRO)] = std::bind(&Wally3::Intro_End, this);

	//IDLE
	StartFuncPtr[static_cast<int>(Wally3State::IDLE)] = std::bind(&Wally3::Idle_Start, this);
	UpdateFuncPtr[static_cast<int>(Wally3State::IDLE)] = std::bind(&Wally3::Idle_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(Wally3State::IDLE)] = std::bind(&Wally3::Idle_End, this);

	//GARBAGE
	StartFuncPtr[static_cast<int>(Wally3State::GARBAGE)] = std::bind(&Wally3::Garbage_Start, this);
	UpdateFuncPtr[static_cast<int>(Wally3State::GARBAGE)] = std::bind(&Wally3::Garbage_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(Wally3State::GARBAGE)] = std::bind(&Wally3::Garbage_End, this);
	//REGURGITATE
	StartFuncPtr[static_cast<int>(Wally3State::REGURGITATE)] = std::bind(&Wally3::Regurgitate_Start, this);
	UpdateFuncPtr[static_cast<int>(Wally3State::REGURGITATE)] = std::bind(&Wally3::Regurgitate_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(Wally3State::REGURGITATE)] = std::bind(&Wally3::Regurgitate_End, this);

	//DEATH
	StartFuncPtr[static_cast<int>(Wally3State::DEATH)] = std::bind(&Wally3::Death_Start, this);
	UpdateFuncPtr[static_cast<int>(Wally3State::DEATH)] = std::bind(&Wally3::Death_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(Wally3State::DEATH)] = std::bind(&Wally3::Death_End, this);

	GetTransform()->SetLocalPosition(float4(100, 0));

	if (false == GameEngineInput::IsKey("PressF"))
	{
		GameEngineInput::CreateKey("PressF", 'F');
	}
}

void Wally3::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("PressF"))
	{
		if(Wally3State::IDLE == CurState)
		{
			NextState = Wally3State::GARBAGE;
		}
		else
		{
			NextState = Wally3State::IDLE;
		}
	}
	UpdateState(_DeltaTime);
}


void Wally3::UpdateState(float _DeltaTime)
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

void Wally3::MakeBirds()
{
	if (nullptr == LeftBird)
	{
		LeftBird = GetLevel()->CreateActor<Wally3_LeftBird>(CupHeadRendererOrder::Boss);
		LeftBird->GetTransform()->SetParent(GetTransform());
		LeftBird->GetTransform()->SetLocalPosition(float4(-385, 125));

	}
	if (nullptr == RightBird)
	{
		RightBird = GetLevel()->CreateActor<Wally3_RightBird>(CupHeadRendererOrder::Boss);
		RightBird->GetTransform()->SetParent(GetTransform());
		RightBird->GetTransform()->SetLocalPosition(float4(390, 130));

	}
}


void Wally3::MoveUpdate(float _DeltaTime)
{
	GetTransform()->SetLocalPosition(float4(sinf(MoveDuration / 2) * 250, -210, 0));
	MoveDuration += _DeltaTime;
}
