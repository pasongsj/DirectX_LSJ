#include "PrecompileHeader.h"
#include "PlayerOverWorldMode.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

PlayerOverWorldMode::PlayerOverWorldMode()
{
}

PlayerOverWorldMode::~PlayerOverWorldMode()
{
}

void PlayerOverWorldMode::Start()
{
	Player::Start();

	PlayerRender = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::Player);
	PlayerRender->CreateAnimation({ .AnimationName = "Down_Right_Idle", .SpriteName = "Diag_Down_Idle", .FrameInter = 0.05f, .Loop = true , .ScaleToTexture = true });
	PlayerRender->CreateAnimation({ .AnimationName = "Down_Right_Move", .SpriteName = "Diag_Down_Move", .FrameInter = 0.05f, .Loop = true , .ScaleToTexture = true });

	PlayerRender->CreateAnimation({ .AnimationName = "Up_Right_Idle", .SpriteName = "Diag_Up_Idle", .FrameInter = 0.05f, .Loop = true , .ScaleToTexture = true });
	PlayerRender->CreateAnimation({ .AnimationName = "Up_Right_Move", .SpriteName = "Diag_Up_Move", .FrameInter = 0.05f, .Loop = true , .ScaleToTexture = true });

	PlayerRender->CreateAnimation({ .AnimationName = "Right_Move", .SpriteName = "Side_Move", .FrameInter = 0.05f, .Loop = true , .ScaleToTexture = true });
	PlayerRender->CreateAnimation({ .AnimationName = "Right_Idle", .SpriteName = "Side_Idle", .FrameInter = 0.05f, .Loop = true , .ScaleToTexture = true });

	PlayerRender->CreateAnimation({ .AnimationName = "Up_Idle", .SpriteName = "Up_Idle", .FrameInter = 0.05f, .Loop = true , .ScaleToTexture = true });
	PlayerRender->CreateAnimation({ .AnimationName = "Up_Move", .SpriteName = "Up_Move", .FrameInter = 0.05f, .Loop = true , .ScaleToTexture = true });

	PlayerRender->CreateAnimation({ .AnimationName = "Down_Idle", .SpriteName = "Down_Idle", .FrameInter = 0.05f, .Loop = true , .ScaleToTexture = true });
	PlayerRender->CreateAnimation({ .AnimationName = "Down_Move", .SpriteName = "Down_Move", .FrameInter = 0.05f, .Loop = true , .ScaleToTexture = true });

	
	PlayerRender->CreateAnimation({ .AnimationName = "Down_Left_Idle", .SpriteName = "Diag_Down_Idle", .FrameInter = 0.05f, .Loop = true , .ScaleToTexture = true });
	PlayerRender->CreateAnimation({ .AnimationName = "Down_Left_Move", .SpriteName = "Diag_Down_Move", .FrameInter = 0.05f, .Loop = true , .ScaleToTexture = true });

	PlayerRender->CreateAnimation({ .AnimationName = "Up_Left_Idle", .SpriteName = "Diag_Up_Idle", .FrameInter = 0.05f, .Loop = true , .ScaleToTexture = true });
	PlayerRender->CreateAnimation({ .AnimationName = "Up_Left_Move", .SpriteName = "Diag_Up_Move", .FrameInter = 0.05f, .Loop = true , .ScaleToTexture = true });

	PlayerRender->CreateAnimation({ .AnimationName = "Left_Idle", .SpriteName = "Side_Idle", .FrameInter = 0.05f, .Loop = true , .ScaleToTexture = true });
	PlayerRender->CreateAnimation({ .AnimationName = "Left_Move", .SpriteName = "Side_Move", .FrameInter = 0.05f, .Loop = true , .ScaleToTexture = true });

	PlayerRender->CreateAnimation({ .AnimationName = "InterAction_Win", .SpriteName = "InterAction_Win", .FrameInter = 0.05f, .Loop = true , .ScaleToTexture = true });

	PlayerRender->ChangeAnimation("Down_Right_Idle");
	//PlayerRender->SetAnimationStartEvent()



	// FSM 실행함수 포인터

	//IDLE
	StartFuncPtr[static_cast<int>(PlayerOverWorldModeState::IDLE)] = std::bind(&PlayerOverWorldMode::Idle_Start, this);
	UpdateFuncPtr[static_cast<int>(PlayerOverWorldModeState::IDLE)] = std::bind(&PlayerOverWorldMode::Idle_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(PlayerOverWorldModeState::IDLE)] = std::bind(&PlayerOverWorldMode::Idle_End, this);

	//MOVE
	StartFuncPtr[static_cast<int>(PlayerOverWorldModeState::MOVE)] = std::bind(&PlayerOverWorldMode::MoveUp_Start, this);
	UpdateFuncPtr[static_cast<int>(PlayerOverWorldModeState::MOVE)] = std::bind(&PlayerOverWorldMode::MoveUp_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(PlayerOverWorldModeState::MOVE)] = std::bind(&PlayerOverWorldMode::MoveUp_End, this);

	//WIN
	StartFuncPtr[static_cast<int>(PlayerOverWorldModeState::WIN)] = std::bind(&PlayerOverWorldMode::Win_Start, this);
	UpdateFuncPtr[static_cast<int>(PlayerOverWorldModeState::WIN)] = std::bind(&PlayerOverWorldMode::Win_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(PlayerOverWorldModeState::WIN)] = std::bind(&PlayerOverWorldMode::Win_End, this);


}

void PlayerOverWorldMode::Update(float _DeltaTime)
{
	CheckInput();
	MoveUpdate(_DeltaTime);
	MainCameraMove(_DeltaTime);
}

void PlayerOverWorldMode::Render(float _DeltaTime)
{
}

void PlayerOverWorldMode::MoveUpdate(float _DeltaTime)
{
	GetTransform()->AddLocalPosition(MoveVec * MoveSpeed * _DeltaTime);
	MoveVec = float4::Zero;
}

void PlayerOverWorldMode::UpdateState(float _DeltaTime)
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

void PlayerOverWorldMode::CheckInput()
{
	std::string TmpDir = "";
	if (true == GameEngineInput::IsPress("PlayerAirPlaneMoveUp"))
	{
		GetTransform()->SetLocalScale(float4(1, 1, 1));
		MoveVec += float4::Up;
		TmpDir += "Up_";
	}
	else if (true == GameEngineInput::IsPress("PlayerAirPlaneMoveDown"))
	{
		GetTransform()->SetLocalScale(float4(1, 1, 1));
		MoveVec += float4::Down;
		TmpDir += "Down_";
	}
	

	if (true == GameEngineInput::IsPress("PlayerAirPlaneMoveLeft"))
	{
		GetTransform()->SetLocalScale(float4(-1, 1, 1));
		MoveVec += float4::Left;
		TmpDir += "Left_";
	}
	else if (true == GameEngineInput::IsPress("PlayerAirPlaneMoveRight"))
	{
		GetTransform()->SetLocalScale(float4(1, 1, 1));
		MoveVec += float4::Right;
		TmpDir += "Right_";
	}

	if (true == TmpDir.empty())
	{
		TmpDir = CurAnimation + "Idle";
	}
	else
	{
		CurAnimation = TmpDir;
		NextState = PlayerOverWorldModeState::MOVE;
		TmpDir += "Move";
	}
	PlayerRender->ChangeAnimation(TmpDir,false);
}



void PlayerOverWorldMode::MainCameraMove(float _DeltaTime)
{
	float4 CamPos = GetLevel()->GetMainCamera()->GetTransform()->GetWorldPosition();
	float4 NextPos = float4::Zero;
	GetLevel()->GetMainCamera()->GetTransform()->SetLocalPosition(NextPos.LerpClamp(CamPos, GetTransform()->GetWorldPosition(), 3.0f * _DeltaTime));
}
