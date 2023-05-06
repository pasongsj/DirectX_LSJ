#include "PrecompileHeader.h"
#include "PlayerAirPlaneMode.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

PlayerAirPlaneMode::PlayerAirPlaneMode() 
{
}

PlayerAirPlaneMode::~PlayerAirPlaneMode() 
{
}

void PlayerAirPlaneMode::Start()
{

	if (false == GameEngineInput::IsKey("PlayerAirPlaneMoveLeft"))
	{
		GameEngineInput::CreateKey("PlayerAirPlaneMoveLeft", 'A');
		GameEngineInput::CreateKey("PlayerAirPlaneMoveRight", 'D');
		GameEngineInput::CreateKey("PlayerAirPlaneMoveUp", 'W');
		GameEngineInput::CreateKey("PlayerAirPlaneMoveDown", 'S');
		GameEngineInput::CreateKey("PlayerAirPlaneParry", VK_SPACE);
		GameEngineInput::CreateKey("PlayerAirPlaneSuperSkill", 'X');
	}

	PlayerRender = CreateComponent<GameEngineSpriteRenderer>();
	PlayerRender->SetScaleToTexture("cuphead_plane_idle_straight_0001.png");
	PlayerRender->CreateAnimation({ .AnimationName = "Intro",  .TextureName = "cuphead_plane_intro_00", .Start = 1, .End = 41,.InterTime = 0.05f, .Loop = false });
	PlayerRender->CreateAnimation({ .AnimationName = "Idle",  .TextureName = "cuphead_plane_idle_straight_000", .Start = 1, .End = 4, .Loop = true });
	PlayerRender->CreateAnimation({ .AnimationName = "MoveUp",  .TextureName = "cuphead_plane_idle_up_000", .Start = 1, .End = 4,.InterTime = 0.05f, .Loop = true });
	PlayerRender->CreateAnimation({ .AnimationName = "MoveDown",  .TextureName = "cuphead_plane_idle_down_000", .Start = 1, .End = 4,.InterTime = 0.05f, .Loop = true });
	PlayerRender->CreateAnimation({ .AnimationName = "Parry",  .TextureName = "cuphead_plane_parry_00", .Start = 1, .End = 20,.InterTime = 0.03f, .Loop = false });

	PlayerRender->ChangeAnimation("Intro");

	GetTransform()->SetLocalPosition(float4( - 300, 0, 0));
	/*Player = CreateComponent<GameEngineRenderer>();
	Player->SetPipeLine("2DTexture");
	Player->GetShaderResHelper().SetTexture("DiffuseTex", "cuphead_plane_idle_straight_0001.png");
	Player->GetTransform()->SetLocalScale({ 100.0f, 100.0f , 100.0f });*/

	CurState = PlayerAirPlaneModeState::INTRO;
	NextState = PlayerAirPlaneModeState::INTRO;



	// FSM 실행함수 포인터

	//INTRO
	StartFuncPtr[static_cast<int>(PlayerAirPlaneModeState::INTRO)]	= std::bind(&PlayerAirPlaneMode::Intro_Start ,	this);
	UpdateFuncPtr[static_cast<int>(PlayerAirPlaneModeState::INTRO)] = std::bind(&PlayerAirPlaneMode::Intro_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(PlayerAirPlaneModeState::INTRO)]	 = std::bind(&PlayerAirPlaneMode::Intro_End, this);

	//IDLE
	StartFuncPtr[static_cast<int>(PlayerAirPlaneModeState::IDLE)]	= std::bind(&PlayerAirPlaneMode::Idle_Start, this);
	UpdateFuncPtr[static_cast<int>(PlayerAirPlaneModeState::IDLE)] = std::bind(&PlayerAirPlaneMode::Idle_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(PlayerAirPlaneModeState::IDLE)]	= std::bind(&PlayerAirPlaneMode::Idle_End, this);

	//MOVE_UP
	StartFuncPtr[static_cast<int>(PlayerAirPlaneModeState::MOVE_UP)]	= std::bind(&PlayerAirPlaneMode::MoveUp_Start, this);
	UpdateFuncPtr[static_cast<int>(PlayerAirPlaneModeState::MOVE_UP)] = std::bind(&PlayerAirPlaneMode::MoveUp_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(PlayerAirPlaneModeState::MOVE_UP)]	= std::bind(&PlayerAirPlaneMode::MoveUp_End, this);

	//MOVE_DOWN
	StartFuncPtr[static_cast<int>(PlayerAirPlaneModeState::MOVE_DOWN)]	= std::bind(&PlayerAirPlaneMode::MoveDown_Start, this);
	UpdateFuncPtr[static_cast<int>(PlayerAirPlaneModeState::MOVE_DOWN)] = std::bind(&PlayerAirPlaneMode::MoveDown_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(PlayerAirPlaneModeState::MOVE_DOWN)]	= std::bind(&PlayerAirPlaneMode::MoveDown_End, this);

	//PARRY
	StartFuncPtr[static_cast<int>(PlayerAirPlaneModeState::PARRY)]	= std::bind(&PlayerAirPlaneMode::Parry_Start, this);
	UpdateFuncPtr[static_cast<int>(PlayerAirPlaneModeState::PARRY)] = std::bind(&PlayerAirPlaneMode::Parry_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(PlayerAirPlaneModeState::PARRY)]	= std::bind(&PlayerAirPlaneMode::Parry_End, this);

	//SUPER_SKILL
	StartFuncPtr[static_cast<int>(PlayerAirPlaneModeState::SUPER_SKILL)]	= std::bind(&PlayerAirPlaneMode::SuperSkill_Start, this);
	UpdateFuncPtr[static_cast<int>(PlayerAirPlaneModeState::SUPER_SKILL)] = std::bind(&PlayerAirPlaneMode::SuperSkill_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(PlayerAirPlaneModeState::SUPER_SKILL)]	= std::bind(&PlayerAirPlaneMode::SuperSkill_End, this);
}


void PlayerAirPlaneMode::Update(float _DeltaTime)
{
	//CheckInput();
	UpdateState(_DeltaTime);
	MoveUpdate(_DeltaTime);
	if (true == GameEngineInput::IsPress("PlayerAirPlaneParry"))
	{
		NextState = PlayerAirPlaneModeState::PARRY;
	}
	//else if (true == GameEngineInput::IsPress("PlayerAirPlaneSuperSkill"))
	//{
	//	NextState = PlayerAirPlaneModeState::SUPER_SKILL;
	//}
}

void PlayerAirPlaneMode::MoveUpdate(float _DeltaTime)
{
	GetTransform()->AddLocalPosition(MoveVec * MoveSpeed * _DeltaTime);
	MoveVec = float4::Zero;
}

void PlayerAirPlaneMode::CheckInput()
{
	bool isPressKey = false;
	if (true == GameEngineInput::IsPress("PlayerAirPlaneMoveLeft"))
	{
		MoveVec += float4::Left;
		isPressKey = true;
	}
	if (true == GameEngineInput::IsPress("PlayerAirPlaneMoveRight"))
	{
		MoveVec += float4::Right;
		isPressKey = true;
	}
	if (true == GameEngineInput::IsPress("PlayerAirPlaneMoveUp"))
	{
		MoveVec += float4::Up;
		NextState = PlayerAirPlaneModeState::MOVE_UP;
		isPressKey = true;
	}
	if (true == GameEngineInput::IsPress("PlayerAirPlaneMoveDown"))
	{
		MoveVec += float4::Down;
		NextState = PlayerAirPlaneModeState::MOVE_DOWN;
		isPressKey = true;
	}
	if(false == isPressKey)
	{
		NextState = PlayerAirPlaneModeState::IDLE;
	}
}

void PlayerAirPlaneMode::Render(float _DeltaTime)
{
	
}

void PlayerAirPlaneMode::UpdateState(float _DeltaTime)
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

	if (true == isStartAnimationDone)
	{
		// CurState에 대한 Update
		UpdateFuncPtr[static_cast<int>(CurState)](_DeltaTime);
	}

}