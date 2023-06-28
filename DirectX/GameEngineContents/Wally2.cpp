#include "PrecompileHeader.h"
#include "Wally2.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

Wally2::Wally2()
{
}

Wally2::~Wally2()
{
}

void Wally2::MakeSprite()
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


void Wally2::Start()
{
	MakeSprite();

	BossRender = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::Boss);
	BossRender->CreateAnimation({ .AnimationName = "Idle",.SpriteName = "Wally2_Idle" , .FrameInter = 0.05f, .Loop = true,.ScaleToTexture = true });
	BossRender->CreateAnimation({ .AnimationName = "Blink",.SpriteName = "Wally2_Blink" , .FrameInter = 0.05f, .Loop = true,.ScaleToTexture = true });

	BossRender->CreateAnimation({ .AnimationName = "Shoot",.SpriteName = "Wally2_Shoot" , .FrameInter = 0.05f, .Loop = false,.ScaleToTexture = true });

	BossRender->CreateAnimation({ .AnimationName = "Death_Trans",.SpriteName = "Wally2_Death_Trans" , .FrameInter = 0.05f, .Loop = false,.ScaleToTexture = true });
	BossRender->CreateAnimation({ .AnimationName = "Death_Loop",.SpriteName = "Wally2_Death_Loop" , .FrameInter = 0.05f, .Loop = true,.ScaleToTexture = true });
	BossRender->SetAnimationStartEvent("Death_Loop", 3, [this] {++DeathLoopCount; });

	BossRender->CreateAnimation({ .AnimationName = "TurnRight",.SpriteName = "Wally2_Turn_Right" , .FrameInter = 0.05f, .Loop = false,.ScaleToTexture = true });
	BossRender->CreateAnimation({ .AnimationName = "TurnLeft",.SpriteName = "Wally2_Turn_Left" , .FrameInter = 0.05f, .Loop = false,.ScaleToTexture = true });
	Intro_Start();

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

	GetTransform()->SetLocalPosition(float4(100, 0));

	if (false == GameEngineInput::IsKey("PressF"))
	{
		GameEngineInput::CreateKey("PressF", 'F');
	}
}

void Wally2::Update(float _DeltaTime)
{
	if (GameEngineInput::IsPress("PressF"))
	{
		NextState = Wally2State::SHOOT;
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
	float4 NextPos = float4(100, 0) + float4((sinf(MoveDuration * 1.0f)) * SpinSpeed * 2, -sinf(MoveDuration * 2.0f) * SpinSpeed);

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