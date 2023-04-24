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

	if (false == GameEngineInput::IsKey("PlayerMoveLeft"))
	{
		GameEngineInput::CreateKey("PlayerMoveLeft", 'A');
		GameEngineInput::CreateKey("PlayerMoveRight", 'D');
		GameEngineInput::CreateKey("PlayerMoveUp", 'W');
		GameEngineInput::CreateKey("PlayerMoveDown", 'S');
	}

	PlayerRender = CreateComponent<GameEngineSpriteRenderer>();
	PlayerRender->SetTexture("cuphead_plane_idle_straight_0001.png");
	PlayerRender->GetTransform()->SetLocalScale({ 100, 100 , 100 });


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
	CheckInput();
	MoveUpdate(_DeltaTime);
	UpdateState(_DeltaTime);
}

void PlayerAirPlaneMode::MoveUpdate(float _DeltaTime)
{
	GetTransform()->AddLocalPosition(MoveVec * MoveSpeed * _DeltaTime);
	MoveVec = float4::Zero;
}

void PlayerAirPlaneMode::CheckInput()
{
	if (true == GameEngineInput::IsPress("PlayerMoveLeft"))
	{
		MoveVec += float4::Left;
	}
	if (true == GameEngineInput::IsPress("PlayerMoveRight"))
	{
		MoveVec += float4::Right;
	}
	if (true == GameEngineInput::IsPress("PlayerMoveUp"))
	{
		MoveVec += float4::Up;
		NextState = PlayerAirPlaneModeState::MOVE_UP;
	}
	if (true == GameEngineInput::IsPress("PlayerMoveDown"))
	{
		MoveVec += float4::Down;
		NextState = PlayerAirPlaneModeState::MOVE_DOWN;
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