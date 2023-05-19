#include "PrecompileHeader.h"
#include "Hilda.h"
#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "Constellation.h"

Hilda::Hilda() 
{
}																				 
																				 
Hilda::~Hilda() 																 
{
}		

void Hilda::MakeSprite()
{
	if (nullptr == GameEngineSprite::Find("Hilda_Intro"))
	{

		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources\\Texture\\stage1\\Boss\\Hilda\\HildaBerg\\Normal");

		
		// intro
		GameEngineSprite::LoadFolder("Hilda_Intro",NewDir.GetPlusFileName("Intro\\Hilda").GetFullPath());
		// idle
		GameEngineSprite::LoadFolder("Hilda_Idle", NewDir.GetPlusFileName("Idle").GetFullPath());
		// shoot
		GameEngineSprite::LoadFolder("Hilda_Shoot", NewDir.GetPlusFileName("Laugh\\Hilda").GetFullPath());
		// Dash
		GameEngineSprite::LoadFolder("Hilda_Dash", NewDir.GetPlusFileName("ChangePhase\\Dash\\Dash").GetFullPath());
		// DashBack
		GameEngineSprite::LoadFolder("Hilda_DashBack", NewDir.GetPlusFileName("ChangePhase\\Dash\\DashBack").GetFullPath());
		// Summon
		GameEngineSprite::LoadFolder("Hilda_Summon", NewDir.GetPlusFileName("ChangePhase\\Summon").GetFullPath());
		// Tornato
		GameEngineSprite::LoadFolder("Hilda_Tornado", NewDir.GetPlusFileName("Tornado\\Hilda").GetFullPath());

	}
}
																				
void Hilda::Start()																
{
	SetPhase(1);
	MakeSprite();
	// 랜더러 설정				

	//PlayerRender->CreateAnimation({ .AnimationName = "OriginIntro", .SpriteName = "Cuphead_AirPlane_Origin_intro", .FrameInter = 0.05f, .Loop = false , .ScaleToTexture = true });

	Boss = CreateComponent<GameEngineSpriteRenderer>();		
	Boss->CreateAnimation({ .AnimationName = "Intro",  .SpriteName = "Hilda_Intro", .FrameInter = 0.05f, .Loop = false , .ScaleToTexture = true });
	Boss->CreateAnimation({ .AnimationName = "Idle",  .SpriteName = "Hilda_Idle",.FrameInter = 0.05f, .Loop = true , .ScaleToTexture = true });
	Boss->CreateAnimation({ .AnimationName = "shoot",  .SpriteName = "Hilda_Shoot",.FrameInter = 0.05f, .Loop = false , .ScaleToTexture = true });
	Boss->CreateAnimation({ .AnimationName = "Dash",  .SpriteName = "Hilda_Dash", .FrameInter = 0.05f, .Loop = false , .ScaleToTexture = true });
	Boss->CreateAnimation({ .AnimationName = "DashBack",  .SpriteName = "Hilda_DashBack", .FrameInter = 0.05f, .Loop = false , .ScaleToTexture = true });
	Boss->CreateAnimation({ .AnimationName = "Summon",  .SpriteName = "Hilda_Summon", .FrameInter = 0.1f, .Loop = false , .ScaleToTexture = true });
	Boss->CreateAnimation({ .AnimationName = "Tornato",  .SpriteName = "Hilda_Tornado",.FrameInter = 0.05f, .Loop = false , .ScaleToTexture = true });
	Boss->ChangeAnimation("Intro");
	
	Boss->SetAnimationUpdateEvent("DashBack", 3, [this]
		{
			GetLevel()->CreateActor<Constellation>(CupHeadActorOrder::Enemy);
		});
																				
	GetTransform()->SetLocalPosition(float4(300.0f,0));							
																				

	//FSM

	//INTRO
	StartFuncPtr[static_cast<int>(HildaState::INTRO)] = std::bind(&Hilda::Intro_Start, this);
	UpdateFuncPtr[static_cast<int>(HildaState::INTRO)] = std::bind(&Hilda::Intro_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(HildaState::INTRO)] = std::bind(&Hilda::Intro_End, this);

	//IDLE
	StartFuncPtr[static_cast<int>(HildaState::IDLE)] = std::bind(&Hilda::Idle_Start, this);
	UpdateFuncPtr[static_cast<int>(HildaState::IDLE)] = std::bind(&Hilda::Idle_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(HildaState::IDLE)] = std::bind(&Hilda::Idle_End, this);

	//SHOOT
	StartFuncPtr[static_cast<int>(HildaState::SHOOT)] = std::bind(&Hilda::Shoot_Start, this);
	UpdateFuncPtr[static_cast<int>(HildaState::SHOOT)] = std::bind(&Hilda::Shoot_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(HildaState::SHOOT)] = std::bind(&Hilda::Shoot_End, this);

	//CHANGEPHASE
	StartFuncPtr[static_cast<int>(HildaState::CHANGEPHASE)] = std::bind(&Hilda::ChangePhase_Start, this);
	UpdateFuncPtr[static_cast<int>(HildaState::CHANGEPHASE)] = std::bind(&Hilda::ChangePhase_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(HildaState::CHANGEPHASE)] = std::bind(&Hilda::ChangePhase_End, this);

	//TORNADO
	StartFuncPtr[static_cast<int>(HildaState::TORNADO)] = std::bind(&Hilda::Tornado_Start, this);
	UpdateFuncPtr[static_cast<int>(HildaState::TORNADO)] = std::bind(&Hilda::Tornado_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(HildaState::TORNADO)] = std::bind(&Hilda::Tornado_End, this);
	


	// TestCode
	if (false == GameEngineInput::IsKey("TestT"))
	{
		GameEngineInput::CreateKey("TestT", 'T');
		GameEngineInput::CreateKey("TestH", 'H');
		GameEngineInput::CreateKey("TestG", 'G');
	}

}

void Hilda::Update(float _DeltaTime)
{
	if (nullptr == Boss)
	{
		MsgAssert("Hilda 랜더러가 제대로 생성되지 않았습니다.");
		return;
	}

	UpdateState(_DeltaTime);


	// 임시 테스트용
	if (true == GameEngineInput::IsPress("TestT"))
	{
		NextState = HildaState::TORNADO;
	}
	if (true == GameEngineInput::IsPress("TestH"))
	{
		NextState = HildaState::SHOOT;
	}
	if (true == GameEngineInput::IsPress("TestG"))
	{
		NextState = HildaState::CHANGEPHASE;
	}
	


}

void Hilda::Render(float _DeltaTime)
{

}

void Hilda::UpdateState(float _DeltaTime)
{
	if (CurState != NextState)
	{
		// CurState에 대한 ending
		EndFuncPtr[static_cast<int>(CurState)]();

		// NextState에 대한 Start
		StartFuncPtr[static_cast<int>(NextState)]();

		// State변경
		CurState = NextState;
		return;
	}

	UpdateFuncPtr[static_cast<int>(CurState)](_DeltaTime);
}