#include "PrecompileHeader.h"
#include "PlayerOverWorldMode.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "OverWorldInteractObject.h"

PlayerOverWorldMode::PlayerOverWorldMode()
{
}

PlayerOverWorldMode::~PlayerOverWorldMode()
{
}

void PlayerOverWorldMode::Start()
{
	Player::Start();
	if (nullptr != Player::MainPlayer)
	{
		MsgAssert("플레이어는 한개만 생성할 수 있습니다.");
	}

	Player::MainPlayer = DynamicThis<PlayerOverWorldMode>().get();
	
	PlayerRender = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::Player);
	ZRender = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::UI);
	SettingRender();


	PlayerCollision = CreateComponent<GameEngineCollision>(CupHeadCollisionOrder::Player);
	PlayerCollision->SetColType(ColType::SPHERE2D);
	PlayerCollision->GetTransform()->SetLocalScale(float4{ 100,0 });
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

	float4 Pos = float4{ 830, -830, 400 };
	GetTransform()->SetLocalPosition(Pos);
	Pos.z = -1000;
	GetLevel()->GetMainCamera()->GetTransform()->SetLocalPosition(Pos);

	if (false == GameEngineInput::IsKey("Press_I"))
	{
		GameEngineInput::CreateKey("Press_I", 'I');
	}
	if (false == GameEngineInput::IsKey("KeyZ_Interaction"))
	{
		GameEngineInput::CreateKey("KeyZ_Interaction", 'Z');
	}

	ColMapTexture = GameEngineTexture::Find("Overworld_ColMap.png");
}

void PlayerOverWorldMode::SettingRender()
{
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

	PlayerRender->CreateAnimation({ .AnimationName = "Down_Left_Idle", .SpriteName = "Diag_Down_Idle_Left", .FrameInter = 0.05f, .Loop = true , .ScaleToTexture = true });
	PlayerRender->CreateAnimation({ .AnimationName = "Down_Left_Move", .SpriteName = "Diag_Down_Move_Left", .FrameInter = 0.05f, .Loop = true , .ScaleToTexture = true });

	PlayerRender->CreateAnimation({ .AnimationName = "Up_Left_Idle", .SpriteName = "Diag_Up_Idle_Left", .FrameInter = 0.05f, .Loop = true , .ScaleToTexture = true });
	PlayerRender->CreateAnimation({ .AnimationName = "Up_Left_Move", .SpriteName = "Diag_Up_Move_Left", .FrameInter = 0.05f, .Loop = true , .ScaleToTexture = true });

	PlayerRender->CreateAnimation({ .AnimationName = "Left_Idle", .SpriteName = "Side_Idle_Left", .FrameInter = 0.05f, .Loop = true , .ScaleToTexture = true });
	PlayerRender->CreateAnimation({ .AnimationName = "Left_Move", .SpriteName = "Side_Move_Left", .FrameInter = 0.05f, .Loop = true , .ScaleToTexture = true });

	PlayerRender->CreateAnimation({ .AnimationName = "InterAction_Win", .SpriteName = "InterAction_Win", .FrameInter = 0.05f, .Loop = false , .ScaleToTexture = true });

	PlayerRender->ChangeAnimation("Down_Right_Idle");

	ZRender->SetScaleToTexture("interactionIcon.png");
	ZRender->GetTransform()->SetLocalPosition(float4{ 0,65,-300 });
	ZRender->Off();
}


void PlayerOverWorldMode::Update(float _DeltaTime)
{
	UpdateState(_DeltaTime);
	CheckInteract();
	if (true == GameEngineInput::IsPress("Press_I"))
	{
		NextState = PlayerOverWorldModeState::WIN;
	}
}

void PlayerOverWorldMode::CheckInteract()
{
	std::shared_ptr<GameEngineCollision> Obj = nullptr;
	if (nullptr != (Obj = PlayerCollision->Collision(CupHeadCollisionOrder::UI)))
	{
		ZRender->On();
		if (false == isZRenderOn)
		{
			GameEngineSound::Play("WorldMap_LevelSelect_BubbleAppear.wav");
			isZRenderOn = true;
		}
	}
	else
	{
		ZRender->Off();
		if (true == isZRenderOn)
		{
			GameEngineSound::Play("WorldMap_LevelSelect_BubbleDisappear.wav");
			isZRenderOn = false;
		}
	}

}


void PlayerOverWorldMode::MoveUpdate(float _DeltaTime)
{
	float4 PlayerPos = GetTransform()->GetLocalPosition() + MoveVec * MoveSpeed * _DeltaTime;
	GameEnginePixelColor Color = ColMapTexture->GetPixel(PlayerPos.ix(), -(PlayerPos.iy()));
	GameEnginePixelColor BC(static_cast<char>(0), static_cast<char>(0), static_cast<char>(0), static_cast<char>(255));
	if (BC != ColMapTexture->GetPixel(PlayerPos.ix(), -(PlayerPos.iy()), GameEnginePixelColor(0, 0, 0, 255)))
	{
		MoveVec.Normalize();
		GetTransform()->AddLocalPosition(MoveVec * MoveSpeed * _DeltaTime);
	}
	MoveVec = float4::Zero;
	MainCameraMove(_DeltaTime);
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
		//GetTransform()->SetLocalScale(float4(1, 1, 1));ㄴ
		MoveVec += float4::Up;
		TmpDir += "Up_";
	}
	else if (true == GameEngineInput::IsPress("PlayerAirPlaneMoveDown"))
	{
		//GetTransform()->SetLocalScale(float4(1, 1, 1));
		MoveVec += float4::Down;
		TmpDir += "Down_";
	}
	

	if (true == GameEngineInput::IsPress("PlayerAirPlaneMoveLeft"))
	{
		//GetTransform()->SetLocalScale(float4(-1, 1, 1));
		MoveVec += float4::Left;
		TmpDir += "Left_";
	}
	else if (true == GameEngineInput::IsPress("PlayerAirPlaneMoveRight"))
	{
		//GetTransform()->SetLocalScale(float4(1, 1, 1));
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
	float4 PlayerPos = GetTransform()->GetWorldPosition();
	PlayerPos.y = PlayerPos.y > -375 ? -375 : PlayerPos.y;
	float4 NextPos = float4::Zero.LerpClamp(CamPos, PlayerPos, 3.0f * _DeltaTime);
	NextPos.z = -1000.0f;
	GetLevel()->GetMainCamera()->GetTransform()->SetLocalPosition(NextPos);
}
