#include "PrecompileHeader.h"
#include "PlayerAirPlaneMode.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "PeaShooter.h"

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
		GameEngineInput::CreateKey("PlayerAirPlaneMoveLeft", VK_LEFT);
		GameEngineInput::CreateKey("PlayerAirPlaneMoveRight", VK_RIGHT);
		GameEngineInput::CreateKey("PlayerAirPlaneMoveUp", VK_UP);
		GameEngineInput::CreateKey("PlayerAirPlaneMoveDown", VK_DOWN);
		GameEngineInput::CreateKey("PlayerAirPlaneParry", 'Z');
		GameEngineInput::CreateKey("PlayerShmupSkill", 'V');
		GameEngineInput::CreateKey("PlayerAttack", 'X');
		GameEngineInput::CreateKey("PlayerShmUpModeSwitch", VK_SPACE);
	}

	PlayerRender = CreateComponent<GameEngineSpriteRenderer>();
	// PlayerRender->SetScaleToTexture("cuphead_plane_idle_straight_0001.png");
	// 
	// idle mode
	PlayerRender->CreateAnimation({ .AnimationName = "Intro",  .TextureName = "cuphead_plane_intro_00", .Start = 1, .End = 41,.InterTime = 0.05f, .Loop = false });

	PlayerRender->CreateAnimation({ .AnimationName = "Idle",  .TextureName = "cuphead_plane_idle_straight_000", .Start = 1, .End = 4, .Loop = true });
	PlayerRender->CreateAnimation({ .AnimationName = "MoveUp",  .TextureName = "cuphead_plane_idle_up_000", .Start = 1, .End = 4,.InterTime = 0.05f, .Loop = true });
	PlayerRender->CreateAnimation({ .AnimationName = "MoveUpTrans",  .TextureName = "cuphead_plane_trans_up_00", .Start = 1, .End = 11,.InterTime = 0.01f, .Loop = false });

	PlayerRender->CreateAnimation({ .AnimationName = "MoveDown",  .TextureName = "cuphead_plane_idle_down_000", .Start = 1, .End = 4,.InterTime = 0.05f, .Loop = true });
	PlayerRender->CreateAnimation({ .AnimationName = "MoveDownTrans",  .TextureName = "cuphead_plane_trans_down_00", .Start = 1, .End = 11,.InterTime = 0.01f, .Loop = false });

	// parry
	PlayerRender->CreateAnimation({ .AnimationName = "Parry",  .TextureName = "cuphead_plane_parry_00", .Start = 1, .End = 20,.InterTime = 0.03f, .Loop = false });

	// shmup mode
	PlayerRender->CreateAnimation({ .AnimationName = "ShmUpIntro",  .TextureName = "ch_shmup_super_intro_00", .Start = 1, .End = 14,.InterTime = 0.1f, .Loop = false });
	PlayerRender->CreateAnimation({ .AnimationName = "ShmUpIdle",  .TextureName = "ch_shmup_super_idle_straight_000", .Start = 1, .End = 4, .Loop = true });
	PlayerRender->CreateAnimation({ .AnimationName = "ShmUpMoveUp",  .TextureName = "ch_shmup_super_idle_up_000", .Start = 1, .End = 4,.InterTime = 0.05f, .Loop = true });
	PlayerRender->CreateAnimation({ .AnimationName = "ShmUpMoveUpTrans",  .TextureName = "ch_shmup_super_trans_up_00", .Start = 1, .End = 12,.InterTime = 0.01f, .Loop = false });

	PlayerRender->CreateAnimation({ .AnimationName = "ShmUpMoveDown",  .TextureName = "ch_shmup_super_idle_down_000", .Start = 1, .End = 4,.InterTime = 0.05f, .Loop = true });
	PlayerRender->CreateAnimation({ .AnimationName = "ShmUpMoveDownTrans",  .TextureName = "ch_shmup_super_trans_down_00", .Start = 1, .End = 10,.InterTime = 0.01f, .Loop = false });


	//PlayerRender->ChangeAnimation("Intro");
	PlayerRender->ChangeAnimation("Idle");

	Spark = CreateComponent<GameEngineSpriteRenderer>();
	Spark->CreateAnimation({ .AnimationName = "Spark", .TextureName = "plane_shoot_spark_000", .Start = 1, .End = 4, .InterTime = 0.05f, .Loop = true });
	Spark->ChangeAnimation("Spark");

	GetTransform()->SetLocalPosition(float4( - 300, 0, 0));


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


}


void PlayerAirPlaneMode::Update(float _DeltaTime)
{

	// 임시 체크용
	if (true == GameEngineInput::IsDown("PlayerShmUpModeSwitch")) // VK_SPACE
	{
		isShmUpMode = !isShmUpMode;
		NextState = PlayerAirPlaneModeState::INTRO;
	}
	if (true == GameEngineInput::IsDown("PlayerShmupSkill")) // 'V'
	{
		isShmUpMode = false;
		ChangePlayerAnimation("Idle");
		NextState = PlayerAirPlaneModeState::IDLE;
	}

	// shoot
	ShootInterVal -= _DeltaTime;
	CheckShoot(_DeltaTime);

	// state
	UpdateState(_DeltaTime);
	MoveUpdate(_DeltaTime);

	// for test
	//GetLevel()->GetMainCamera()->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition() + (float4::Back * 100.0f));
}

void PlayerAirPlaneMode::MoveUpdate(float _DeltaTime)
{
	GetTransform()->AddLocalPosition(MoveVec * MoveSpeed * _DeltaTime);
	MoveVec = float4::Zero;
}

void PlayerAirPlaneMode::CheckInput()
{
	bool isPressKey = false;
	if (true == GameEngineInput::IsPress("PlayerAirPlaneParry"))
	{
		NextState = PlayerAirPlaneModeState::PARRY;
		isPressKey = true;
	}
	else
	{
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

	UpdateFuncPtr[static_cast<int>(CurState)](_DeltaTime);

}

void PlayerAirPlaneMode::ChangePlayerAnimation(const std::string_view& _Name)
{
	if (true == isShmUpMode)
	{
		PlayerRender->ChangeAnimation("ShmUp" + std::string(_Name));
	}
	else
	{
		PlayerRender->ChangeAnimation(_Name);
	}
}

void PlayerAirPlaneMode::CheckShoot(float _DeltaTime)
{
	if (true == GameEngineInput::IsPress("PlayerAttack")) // 'X'
	{
		Spark->On();
		if (0.0f > ShootInterVal)
		{
			std::shared_ptr<PeaShooter> bullet = GetLevel()->CreateActor<PeaShooter>();
			bullet->GetTransform()->SetLocalPosition(GetTransform()->GetWorldPosition() + float4(100, BulletYPos));
			BulletYPos *= -1;
			ShootInterVal = 0.1f;
		}
	}
	else
	{
		Spark->Off();
	}
}