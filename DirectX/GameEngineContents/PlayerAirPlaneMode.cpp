#include "PrecompileHeader.h"
#include "PlayerAirPlaneMode.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "PeaShooter.h"
#include "BoomEffect.h"

PlayerAirPlaneMode::PlayerAirPlaneMode() 
{
}

PlayerAirPlaneMode::~PlayerAirPlaneMode() 
{
}

void PlayerAirPlaneMode::MakeSprite()
{
	if (nullptr == GameEngineSprite::Find("Cuphead_AirPlane_Origin_Idle"))
	{

		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Cuphead_AirPlane\\Idle");



		// Origin
		// idle

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Idle").GetFullPath(), "Cuphead_AirPlane_Origin_Idle");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("up").GetFullPath(), "Cuphead_AirPlane_Origin_Idleup");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("down").GetFullPath(), "Cuphead_AirPlane_Origin_Idledown");

		// intro
		NewDir.Move("..\\Intros");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Regular").GetFullPath(), "Cuphead_AirPlane_Origin_intro");

		// trans
		NewDir.Move("..\\Transicion");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("transup").GetFullPath(), "Cuphead_AirPlane_Origin_transup");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("transdown").GetFullPath(), "Cuphead_AirPlane_Origin_transdown");

		// Super
		// idle
		NewDir.Move("..\\Super\\Idle");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Idle").GetFullPath(), "Cuphead_AirPlane_Super_Idle");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("up").GetFullPath(), "Cuphead_AirPlane_Super_Idleup");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("down").GetFullPath(), "Cuphead_AirPlane_Super_Idledown");

		// intro
		NewDir.MoveParent();
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("intro").GetFullPath(), "Cuphead_AirPlane_Super_intro");

		// trans
		NewDir.Move("trans");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("up").GetFullPath(), "Cuphead_AirPlane_Super_transup");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("down").GetFullPath(), "Cuphead_AirPlane_Super_transdown");

		// Shrink
		// idle
		NewDir.Move("..\\..\\Shrink\\idle");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Idle").GetFullPath(), "Cuphead_AirPlane_Shrink_Idle");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("up").GetFullPath(), "Cuphead_AirPlane_Shrink_Idleup");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("down").GetFullPath(), "Cuphead_AirPlane_Shrink_Idledown");

		// intro
		NewDir.MoveParent();
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("morph").GetFullPath(), "Cuphead_AirPlane_Shrink_intro");

		// trans
		NewDir.Move("trans");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("up").GetFullPath(), "Cuphead_AirPlane_Shrink_transup");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("down").GetFullPath(), "Cuphead_AirPlane_Shrink_transdown");


		//parry
		NewDir.Move("..\\..\\");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Parry").GetFullPath(), "Cuphead_AirPlane_Parry");
	}

	if (nullptr == GameEngineSprite::Find("Cuphead_AirPlane_Spark"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Cuphead_AirPlane\\effect");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Spark").GetFullPath(), "Cuphead_AirPlane_Spark");
	}
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
		GameEngineInput::CreateKey("PlayerOriginMode", VK_NUMPAD1);
		GameEngineInput::CreateKey("PlayerShmUpMode", VK_NUMPAD2);
		GameEngineInput::CreateKey("PlayerShrinkMode", VK_NUMPAD3);
	}

	MakeSprite();


	PlayerRender = CreateComponent<GameEngineSpriteRenderer>();
	//----------
	// 
	// idle mode
	PlayerRender->CreateAnimation({ .AnimationName = "OriginIntro", .SpriteName = "Cuphead_AirPlane_Origin_intro", .FrameInter = 0.05f, .Loop = false , .ScaleToImage = true });
									
	PlayerRender->CreateAnimation({ .AnimationName = "OriginIdle",  .SpriteName = "Cuphead_AirPlane_Origin_Idle", .FrameInter = 0.05f,.Loop = true , .ScaleToImage = true });
	PlayerRender->CreateAnimation({ .AnimationName = "OriginMoveUp",  .SpriteName = "Cuphead_AirPlane_Origin_Idleup", .FrameInter = 0.05f, .Loop = true , .ScaleToImage = true });
	PlayerRender->CreateAnimation({ .AnimationName = "OriginMoveUpTrans",  .SpriteName = "Cuphead_AirPlane_Origin_transup", .FrameInter = 0.01f, .Loop = false , .ScaleToImage = true });
	//									
	PlayerRender->CreateAnimation({ .AnimationName = "OriginMoveDown",  .SpriteName = "Cuphead_AirPlane_Origin_Idledown", .FrameInter = 0.05f, .Loop = true, .ScaleToImage = true });
	PlayerRender->CreateAnimation({ .AnimationName = "OriginMoveDownTrans",  .SpriteName = "Cuphead_AirPlane_Origin_transdown", .FrameInter = 0.01f, .Loop = false, .ScaleToImage = true });

	// parry
	PlayerRender->CreateAnimation({ .AnimationName = "Parry",  .SpriteName = "Cuphead_AirPlane_Parry",.FrameInter = 0.03f, .Loop = false });

	// shmup mode
	PlayerRender->CreateAnimation({ .AnimationName = "SuperIntro",  .SpriteName = "Cuphead_AirPlane_Super_intro", .FrameInter = 0.1f, .Loop = false , .ScaleToImage = true });
	PlayerRender->CreateAnimation({ .AnimationName = "SuperIdle",  .SpriteName = "Cuphead_AirPlane_Super_Idle", .Loop = true, .ScaleToImage = true });
	PlayerRender->CreateAnimation({ .AnimationName = "SuperMoveUp",  .SpriteName = "Cuphead_AirPlane_Super_Idleup",.FrameInter = 0.05f, .Loop = true, .ScaleToImage = true });
	PlayerRender->CreateAnimation({ .AnimationName = "SuperMoveUpTrans",  .SpriteName = "Cuphead_AirPlane_Super_transup",.FrameInter = 0.01f, .Loop = false, .ScaleToImage = true });
												
	PlayerRender->CreateAnimation({ .AnimationName = "SuperMoveDown",  .SpriteName = "Cuphead_AirPlane_Super_Idledown",.FrameInter = 0.05f, .Loop = true, .ScaleToImage = true });
	PlayerRender->CreateAnimation({ .AnimationName = "SuperMoveDownTrans",  .SpriteName = "Cuphead_AirPlane_Super_transdown",.FrameInter = 0.01f, .Loop = false, .ScaleToImage = true });

	// shrink mode
	PlayerRender->CreateAnimation({ .AnimationName = "ShrinkIntro",  .SpriteName = "Cuphead_AirPlane_Shrink_intro",.FrameInter = 0.1f, .Loop = false, .ScaleToImage = true });
	PlayerRender->CreateAnimation({ .AnimationName = "ShrinkIdle",  .SpriteName = "Cuphead_AirPlane_Shrink_Idle",  .Loop = true, .ScaleToImage = true });
	PlayerRender->CreateAnimation({ .AnimationName = "ShrinkMoveUp",  .SpriteName = "Cuphead_AirPlane_Shrink_Idleup",.FrameInter = 0.05f, .Loop = true, .ScaleToImage = true });
	PlayerRender->CreateAnimation({ .AnimationName = "ShrinkMoveUpTrans",  .SpriteName = "Cuphead_AirPlane_Shrink_transup",.FrameInter = 0.01f, .Loop = false, .ScaleToImage = true });
												
	PlayerRender->CreateAnimation({ .AnimationName = "ShrinkMoveDown",  .SpriteName = "Cuphead_AirPlane_Shrink_Idledown", .FrameInter = 0.05f, .Loop = true, .ScaleToImage = true });
	PlayerRender->CreateAnimation({ .AnimationName = "ShrinkMoveDownTrans",  .SpriteName = "Cuphead_AirPlane_Shrink_transdown", .FrameInter = 0.01f, .Loop = false, .ScaleToImage = true });


	PlayerRender->ChangeAnimation("OriginIntro");
	//PlayerRender->ChangeAnimation("Idle");

	Spark = CreateComponent<GameEngineSpriteRenderer>();
	Spark->CreateAnimation({ .AnimationName = "Spark", .SpriteName = "Cuphead_AirPlane_Spark", .FrameInter = 0.05f, .Loop = true,.ScaleToImage = true });
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
		ChangeMode("Super");

		NextState = PlayerAirPlaneModeState::INTRO;
	}
	if ("Super" == CurMode && true == GameEngineInput::IsDown("PlayerShmupSkill")) // 'V'
	{
		ChangeMode("Origin");
		NextState = PlayerAirPlaneModeState::IDLE;
	}

	if (true == GameEngineInput::IsDown("PlayerOriginMode"))
	{
		ChangeMode("Origin");
		NextState = PlayerAirPlaneModeState::INTRO;
	}
	if (true == GameEngineInput::IsDown("PlayerShmUpMode"))
	{
		ChangeMode("Super");
		NextState = PlayerAirPlaneModeState::INTRO;
	}
	if (true == GameEngineInput::IsDown("PlayerShrinkMode"))
	{
		ChangeMode("Shrink");
		NextState = PlayerAirPlaneModeState::INTRO;
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
	if (true == GameEngineInput::IsPress("PlayerAirPlaneParry") && CurMode == "Origin")
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
	PlayerRender->ChangeAnimation(CurMode + std::string(_Name));
}

void PlayerAirPlaneMode::CheckShoot(float _DeltaTime)
{
	if (true == GameEngineInput::IsPress("PlayerAttack")) // 'X'
	{
		Spark->On();
		if (0.0f > ShootInterVal)
		{
			std::shared_ptr<PeaShooter> bullet = GetLevel()->CreateActor<PeaShooter>();
			float4 _Pos = GetTransform()->GetWorldPosition() + float4(100, BulletYPos);
			bullet->GetTransform()->SetWorldPosition(_Pos);
			BulletYPos *= -1;
			ShootInterVal = 0.1f;
		}
	}
	else
	{
		Spark->Off();
	}
}

void PlayerAirPlaneMode::ChangeMode(const std::string_view& _Mode)
{
	if (CurMode == "Super"  && _Mode.data() != "Super")
	{
		std::shared_ptr<GameEngineActor> Effect = GetLevel()->CreateActor<BoomEffect>();
		Effect->GetTransform()->SetLocalPosition(GetTransform()->GetWorldPosition());
		CurMode = _Mode.data();
		ChangePlayerAnimation("Idle");
	}
	CurMode = _Mode.data();
}