#include "PrecompileHeader.h"
#include "PlayerAirPlaneMode.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>


#include "PeaShooter.h"
#include "BoomEffect.h"
#include "PlayerAirPlaneSmokeEffect.h"


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
		NewDir.Move("Cuphead_AirPlane");



		// Origin
		// idle

		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Origin_Idle", NewDir.GetPlusFileName("Idle\\Idle").GetFullPath());
		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Origin_Idleup", NewDir.GetPlusFileName("Idle\\up").GetFullPath());
		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Origin_Idledown", NewDir.GetPlusFileName("Idle\\down").GetFullPath());

		// intro
		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Origin_intro", NewDir.GetPlusFileName("Intros\\Regular").GetFullPath() );

		// trans
		//NewDir.Move("..\\Transicion");
		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Origin_transup",NewDir.GetPlusFileName("Transicion\\transup").GetFullPath());
		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Origin_transdown", NewDir.GetPlusFileName("Transicion\\transdown").GetFullPath());

		// Super
		// idle
		//NewDir.Move("..\\Super\\Idle");
		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Super_Idle", NewDir.GetPlusFileName("Super\\Idle\\Idle").GetFullPath());
		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Super_Idleup", NewDir.GetPlusFileName("Super\\Idle\\up").GetFullPath());
		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Super_Idledown",NewDir.GetPlusFileName("Super\\Idle\\down").GetFullPath());

		// intro
		//NewDir.MoveParent();
		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Super_intro", NewDir.GetPlusFileName("Super\\intro").GetFullPath());

		// trans
		//NewDir.Move("trans");
		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Super_transup", NewDir.GetPlusFileName("Super\\trans\\up").GetFullPath());
		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Super_transdown", NewDir.GetPlusFileName("Super\\trans\\down").GetFullPath());

		// Shrink
		// idle
		//NewDir.Move("..\\..\\Shrink\\idle");
		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Shrink_Idle", NewDir.GetPlusFileName("Shrink\\idle\\Idle").GetFullPath());
		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Shrink_Idleup", NewDir.GetPlusFileName("Shrink\\idle\\up").GetFullPath());
		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Shrink_Idledown", NewDir.GetPlusFileName("Shrink\\idle\\down").GetFullPath());

		// intro
		//NewDir.MoveParent();
		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Shrink_intro", NewDir.GetPlusFileName("Shrink\\morph").GetFullPath());

		// trans
		//NewDir.Move("trans");
		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Shrink_transup", NewDir.GetPlusFileName("Shrink\\trans\\up").GetFullPath());
		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Shrink_transdown", NewDir.GetPlusFileName("Shrink\\trans\\down").GetFullPath());


		//parry
		//NewDir.Move("..\\..\\");
		GameEngineSprite::LoadFolder( "Cuphead_AirPlane_Parry", NewDir.GetPlusFileName("Parry").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Cuphead_AirPlane_Spark"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Cuphead_AirPlane\\effect");

		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Spark", NewDir.GetPlusFileName("Spark").GetFullPath());
	}
}

void PlayerAirPlaneMode::Start()
{
	if (nullptr != Player::MainPlayer)
	{
		MsgAssert("플레이어는 한개만 생성할 수 있습니다.");
	}

	Player::MainPlayer = DynamicThis<PlayerAirPlaneMode>().get();

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
	PlayerRender->CreateAnimation({ .AnimationName = "OriginIntro", .SpriteName = "Cuphead_AirPlane_Origin_intro", .FrameInter = 0.05f, .Loop = false , .ScaleToTexture = true });
									
	PlayerRender->CreateAnimation({ .AnimationName = "OriginIdle",  .SpriteName = "Cuphead_AirPlane_Origin_Idle", .FrameInter = 0.05f,.Loop = true , .ScaleToTexture = true });
	PlayerRender->CreateAnimation({ .AnimationName = "OriginMoveUp",  .SpriteName = "Cuphead_AirPlane_Origin_Idleup", .FrameInter = 0.05f, .Loop = true , .ScaleToTexture = true });
	PlayerRender->CreateAnimation({ .AnimationName = "OriginMoveUpTrans",  .SpriteName = "Cuphead_AirPlane_Origin_transup", .FrameInter = 0.01f, .Loop = false , .ScaleToTexture = true });
	//									
	PlayerRender->CreateAnimation({ .AnimationName = "OriginMoveDown",  .SpriteName = "Cuphead_AirPlane_Origin_Idledown", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
	PlayerRender->CreateAnimation({ .AnimationName = "OriginMoveDownTrans",  .SpriteName = "Cuphead_AirPlane_Origin_transdown", .FrameInter = 0.01f, .Loop = false, .ScaleToTexture = true });

	// parry
	PlayerRender->CreateAnimation({ .AnimationName = "Parry",  .SpriteName = "Cuphead_AirPlane_Parry",.FrameInter = 0.03f, .Loop = false, .ScaleToTexture = true });

	// shmup mode
	PlayerRender->CreateAnimation({ .AnimationName = "SuperIntro",  .SpriteName = "Cuphead_AirPlane_Super_intro", .FrameInter = 0.1f, .Loop = false , .ScaleToTexture = true });
	PlayerRender->CreateAnimation({ .AnimationName = "SuperIdle",  .SpriteName = "Cuphead_AirPlane_Super_Idle", .Loop = true, .ScaleToTexture = true });
	PlayerRender->CreateAnimation({ .AnimationName = "SuperMoveUp",  .SpriteName = "Cuphead_AirPlane_Super_Idleup",.FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
	PlayerRender->CreateAnimation({ .AnimationName = "SuperMoveUpTrans",  .SpriteName = "Cuphead_AirPlane_Super_transup",.FrameInter = 0.01f, .Loop = false, .ScaleToTexture = true });
												
	PlayerRender->CreateAnimation({ .AnimationName = "SuperMoveDown",  .SpriteName = "Cuphead_AirPlane_Super_Idledown",.FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
	PlayerRender->CreateAnimation({ .AnimationName = "SuperMoveDownTrans",  .SpriteName = "Cuphead_AirPlane_Super_transdown",.FrameInter = 0.01f, .Loop = false, .ScaleToTexture = true });

	// shrink mode
	PlayerRender->CreateAnimation({ .AnimationName = "ShrinkIntro",  .SpriteName = "Cuphead_AirPlane_Shrink_intro",.FrameInter = 0.1f, .Loop = false, .ScaleToTexture = true });
	PlayerRender->CreateAnimation({ .AnimationName = "ShrinkIdle",  .SpriteName = "Cuphead_AirPlane_Shrink_Idle",  .Loop = true, .ScaleToTexture = true });
	PlayerRender->CreateAnimation({ .AnimationName = "ShrinkMoveUp",  .SpriteName = "Cuphead_AirPlane_Shrink_Idleup",.FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
	PlayerRender->CreateAnimation({ .AnimationName = "ShrinkMoveUpTrans",  .SpriteName = "Cuphead_AirPlane_Shrink_transup",.FrameInter = 0.01f, .Loop = false, .ScaleToTexture = true });
												
	PlayerRender->CreateAnimation({ .AnimationName = "ShrinkMoveDown",  .SpriteName = "Cuphead_AirPlane_Shrink_Idledown", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
	PlayerRender->CreateAnimation({ .AnimationName = "ShrinkMoveDownTrans",  .SpriteName = "Cuphead_AirPlane_Shrink_transdown", .FrameInter = 0.01f, .Loop = false, .ScaleToTexture = true });


	PlayerRender->ChangeAnimation("OriginIntro");
	//PlayerRender->ChangeAnimation("Idle");

	Spark = CreateComponent<GameEngineSpriteRenderer>(CupHeadActorOrder::PlayerEffect);
	Spark->CreateAnimation({ .AnimationName = "Spark", .SpriteName = "Cuphead_AirPlane_Spark", .FrameInter = 0.05f, .Loop = true,.ScaleToTexture = true });
	Spark->ChangeAnimation("Spark");
	Spark->Off();



	
	PlayerCollision = CreateComponent<GameEngineCollision>(CupHeadCollisionOrder::Player);
	PlayerCollision->SetColType(ColType::SPHERE2D);
	/*PlayerCollsion->GetTransform()->SetLocalScale(PlayerRender->GetTransform()->GetLocalScale());*/
	//PlayerCollsion->SetOrder(CupHeadCollisionOrder::Player);



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
	PlayerCollision->SetRenderScaleToCollision(PlayerRender);
	SuperModeEnergy += _DeltaTime*10;

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
	//CheckShoot(_DeltaTime);

	// state
	UpdateState(_DeltaTime);
	MoveUpdate(_DeltaTime);
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
			std::shared_ptr<PeaShooter> bullet = GetLevel()->CreateActor<PeaShooter>(CupHeadActorOrder::Player);
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
		std::shared_ptr<GameEngineActor> Effect = GetLevel()->CreateActor<BoomEffect>(CupHeadActorOrder::Player);
		Effect->GetTransform()->SetLocalPosition(GetTransform()->GetWorldPosition());
		CurMode = _Mode.data();
		ChangePlayerAnimation("Idle");
	}
	CurMode = _Mode.data();
}

void PlayerAirPlaneMode::MakeSmoke(float _DeltaTime)
{

	SmokeInterval -= _DeltaTime;
	if (SmokeInterval < 0.0f)
	{
		SmokeInterval = 0.2f;
		std::shared_ptr< PlayerAirPlaneSmokeEffect> Smoke = GetLevel()->CreateActor< PlayerAirPlaneSmokeEffect>(CupHeadActorOrder::PlayerEffect);
		Smoke->GetTransform()->SetLocalPosition(GetTransform()->GetWorldPosition() + float4(-PlayerRender->GetTransform()->GetLocalScale().hx(), 0));
	}

}