#include "PrecompileHeader.h"
#include "PlayerAirPlaneMode.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

//weapon
#include "PeaShooter.h"
#include "ExBullet.h"
//effect
#include "BoomEffect.h"
#include "PlayerAirPlaneSmokeEffect.h"
#include "ChangeSuperModeEffect.h"
#include "SupermodeShadowEffect.h"

#include "GameEnemy.h"

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

		//shoot
		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("Shoot\\Up").GetFullPath(), "Cuphead_AirPlane_Shoot_Up");
		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("Shoot\\Down").GetFullPath(), "Cuphead_AirPlane_Shoot_Down");

		//dead
		GameEngineSprite::LoadFolder( "Cuphead_AirPlane_Ghost", NewDir.GetPlusFileName("Ghost").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("Cuphead_AirPlane_Spark"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources\\Texture\\Cuphead_AirPlane\\effect");

		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Spark", NewDir.GetPlusFileName("Spark").GetFullPath());
	}
}
void PlayerAirPlaneMode::CreateRenderAnimation()
{
	// Player
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

	// shoot
	PlayerRender->CreateAnimation({ .AnimationName = "Shoot_Up",  .SpriteName = "Cuphead_AirPlane_Shoot_Up",.FrameInter = 0.03f, .Loop = false, .ScaleToTexture = true });
	PlayerRender->SetAnimationStartEvent("Shoot_Up", 15, [this] {
		std::shared_ptr<GameEngineActor> Bullet = GetLevel()->CreateActor< ExBullet>(CupHeadActorOrder::PlayerWepaon);
		float4 Pos = GetTransform()->GetWorldPosition() + float4{0, -10};
		Bullet->GetTransform()->SetLocalPosition(Pos);
		});
	// shmup mode
	PlayerRender->CreateAnimation({ .AnimationName = "SuperIntro",  .SpriteName = "Cuphead_AirPlane_Super_intro", .FrameInter = 0.1f, .Loop = false , .ScaleToTexture = true });
	PlayerRender->CreateAnimation({ .AnimationName = "SuperIdle",  .SpriteName = "Cuphead_AirPlane_Super_Idle", .Loop = true, .ScaleToTexture = true });
	PlayerRender->CreateAnimation({ .AnimationName = "SuperMoveUp",  .SpriteName = "Cuphead_AirPlane_Super_Idleup",.FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
	PlayerRender->CreateAnimation({ .AnimationName = "SuperMoveUpTrans",  .SpriteName = "Cuphead_AirPlane_Super_transup",.FrameInter = 0.01f, .Loop = false, .ScaleToTexture = true });

	PlayerRender->CreateAnimation({ .AnimationName = "SuperMoveDown",  .SpriteName = "Cuphead_AirPlane_Super_Idledown",.FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
	PlayerRender->CreateAnimation({ .AnimationName = "SuperMoveDownTrans",  .SpriteName = "Cuphead_AirPlane_Super_transdown",.FrameInter = 0.01f, .Loop = false, .ScaleToTexture = true });

	// shrink mode
	PlayerRender->CreateAnimation({ .AnimationName = "ShrinkIntro",  .SpriteName = "Cuphead_AirPlane_Shrink_intro",.FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	PlayerRender->CreateAnimation({ .AnimationName = "ShrinkIdle",  .SpriteName = "Cuphead_AirPlane_Shrink_Idle",  .Loop = true, .ScaleToTexture = true });
	PlayerRender->CreateAnimation({ .AnimationName = "ShrinkMoveUp",  .SpriteName = "Cuphead_AirPlane_Shrink_Idleup",.FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
	PlayerRender->CreateAnimation({ .AnimationName = "ShrinkMoveUpTrans",  .SpriteName = "Cuphead_AirPlane_Shrink_transup",.FrameInter = 0.01f, .Loop = false, .ScaleToTexture = true });

	PlayerRender->CreateAnimation({ .AnimationName = "ShrinkMoveDown",  .SpriteName = "Cuphead_AirPlane_Shrink_Idledown", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
	PlayerRender->CreateAnimation({ .AnimationName = "ShrinkMoveDownTrans",  .SpriteName = "Cuphead_AirPlane_Shrink_transdown", .FrameInter = 0.01f, .Loop = false, .ScaleToTexture = true });
	//
	PlayerRender->CreateAnimation({ .AnimationName = "Dead",  .SpriteName = "Cuphead_AirPlane_Ghost", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });

	PlayerRender->SetAnimationStartEvent("SuperIntro", 1, [this] {
		std::shared_ptr< ChangeSuperModeEffect> effect = GetLevel()->CreateActor< ChangeSuperModeEffect>(CupHeadActorOrder::PlayerBackGround);
		effect->GetTransform()->SetLocalPosition(GetTransform()->GetWorldPosition() + float4(0, 0, 1));
		});
	PlayerRender->ChangeAnimation("OriginIntro");
	//PlayerRender->ChangeAnimation("Idle");

	//Spark
	Spark = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::PlayerEffect);
	Spark->CreateAnimation({ .AnimationName = "Spark", .SpriteName = "Cuphead_AirPlane_Spark", .FrameInter = 0.05f, .Loop = true,.ScaleToTexture = true });
	Spark->ChangeAnimation("Spark");
	Spark->Off();
}

void PlayerAirPlaneMode::CreateStateFunc()
{
	// FSM 실행함수 포인터

	//INTRO
	StartFuncPtr[static_cast<int>(PlayerAirPlaneModeState::INTRO)] = std::bind(&PlayerAirPlaneMode::Intro_Start, this);
	UpdateFuncPtr[static_cast<int>(PlayerAirPlaneModeState::INTRO)] = std::bind(&PlayerAirPlaneMode::Intro_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(PlayerAirPlaneModeState::INTRO)] = std::bind(&PlayerAirPlaneMode::Intro_End, this);

	//IDLE
	StartFuncPtr[static_cast<int>(PlayerAirPlaneModeState::IDLE)] = std::bind(&PlayerAirPlaneMode::Idle_Start, this);
	UpdateFuncPtr[static_cast<int>(PlayerAirPlaneModeState::IDLE)] = std::bind(&PlayerAirPlaneMode::Idle_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(PlayerAirPlaneModeState::IDLE)] = std::bind(&PlayerAirPlaneMode::Idle_End, this);

	//MOVE_UP
	StartFuncPtr[static_cast<int>(PlayerAirPlaneModeState::MOVE_UP)] = std::bind(&PlayerAirPlaneMode::MoveUp_Start, this);
	UpdateFuncPtr[static_cast<int>(PlayerAirPlaneModeState::MOVE_UP)] = std::bind(&PlayerAirPlaneMode::MoveUp_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(PlayerAirPlaneModeState::MOVE_UP)] = std::bind(&PlayerAirPlaneMode::MoveUp_End, this);

	//MOVE_DOWN
	StartFuncPtr[static_cast<int>(PlayerAirPlaneModeState::MOVE_DOWN)] = std::bind(&PlayerAirPlaneMode::MoveDown_Start, this);
	UpdateFuncPtr[static_cast<int>(PlayerAirPlaneModeState::MOVE_DOWN)] = std::bind(&PlayerAirPlaneMode::MoveDown_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(PlayerAirPlaneModeState::MOVE_DOWN)] = std::bind(&PlayerAirPlaneMode::MoveDown_End, this);

	//PARRY
	StartFuncPtr[static_cast<int>(PlayerAirPlaneModeState::PARRY)] = std::bind(&PlayerAirPlaneMode::Parry_Start, this);
	UpdateFuncPtr[static_cast<int>(PlayerAirPlaneModeState::PARRY)] = std::bind(&PlayerAirPlaneMode::Parry_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(PlayerAirPlaneModeState::PARRY)] = std::bind(&PlayerAirPlaneMode::Parry_End, this);

	//SHOOT
	StartFuncPtr[static_cast<int>(PlayerAirPlaneModeState::SHOOT)] = std::bind(&PlayerAirPlaneMode::Shoot_Start, this);
	UpdateFuncPtr[static_cast<int>(PlayerAirPlaneModeState::SHOOT)] = std::bind(&PlayerAirPlaneMode::Shoot_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(PlayerAirPlaneModeState::SHOOT)] = std::bind(&PlayerAirPlaneMode::Shoot_End, this);

	//DEAD
	StartFuncPtr[static_cast<int>(PlayerAirPlaneModeState::DEAD)] = std::bind(&PlayerAirPlaneMode::Dead_Start, this);
	UpdateFuncPtr[static_cast<int>(PlayerAirPlaneModeState::DEAD)] = std::bind(&PlayerAirPlaneMode::Dead_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(PlayerAirPlaneModeState::DEAD)] = std::bind(&PlayerAirPlaneMode::Dead_End, this);
}


void PlayerAirPlaneMode::Start()
{
	Player::Start();

	if (nullptr != Player::MainPlayer)
	{
		MsgAssert("플레이어는 한개만 생성할 수 있습니다.");
	}

	Player::MainPlayer = DynamicThis<PlayerAirPlaneMode>().get();
	PlayerRender = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::Player);


	MakeSprite();
	CreateRenderAnimation();

	
	// 이펙트
	ShadowEffect = GetLevel()->CreateActor <SupermodeShadowEffect>(CupHeadActorOrder::PlayerBackGround);
	ShadowEffect->Off();

	// 플레이어 콜리전
	PlayerCollision = CreateComponent<GameEngineCollision>(CupHeadCollisionOrder::Player);
	PlayerCollision->GetTransform()->SetLocalScale(float4(100, 0));
	PlayerCollision->SetColType(ColType::SPHERE2D);

	// 패리 콜리전
	ParryCollision = CreateComponent<GameEngineCollision>(CupHeadCollisionOrder::PlayerWepaon);
	ParryCollision->SetColType(ColType::SPHERE2D);
	ParryCollision->GetTransform()->SetLocalScale(float4(170, 170, 1));
	ParryCollision->Off();


	GetTransform()->SetLocalPosition(float4( -500, 0, 400));


	// state
	CurState = PlayerAirPlaneModeState::INTRO;
	NextState = PlayerAirPlaneModeState::INTRO;
	CreateStateFunc();


}


void PlayerAirPlaneMode::Update(float _DeltaTime)
{
	if ("Super" == CurMode && true == GameEngineInput::IsDown("PlayerShmupSkill")) // SuperMode억지로 풀기용
	{
		ChangeMode("Origin");
		NextState = PlayerAirPlaneModeState::IDLE;
	}

	// 강제 state변환
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


	BlinkEffect(_DeltaTime);
	
	// state
	UpdateState(_DeltaTime);
	MoveUpdate(_DeltaTime);
}

void PlayerAirPlaneMode::BlinkEffect(float _DeltaTime)
{
	//defeat interval
	InvincibleTime -= _DeltaTime;
	BlinkInterval -= _DeltaTime;
	if (InvincibleTime > 0)
	{
		if (BlinkInterval < 0)
		{
			BlinkInterval = 0.1f;
			PlayerRender->ColorOptionValue.MulColor = float4(1, 1, 1, 0.1f);
		}
		else
		{
			PlayerRender->ColorOptionValue.MulColor = float4(1, 1, 1, 1);

		}
	}
	else
	{
		PlayerRender->ColorOptionValue.MulColor = float4(1, 1, 1, 1);

	}
}

void PlayerAirPlaneMode::CheckPink()
{

	std::vector<std::shared_ptr<GameEngineCollision>> Cols;
	if (true == ParryCollision->CollisionAll(CupHeadCollisionOrder::EnemyWeapon, Cols))
	{
		for (std::shared_ptr<GameEngineCollision> _Col : Cols)
		{
			std::shared_ptr<GameEnemy> ColActor = _Col->GetActor()->DynamicThis<GameEnemy>();
			if (true == ColActor->IsPink())
			{
				_Col->GetActor()->Death();
				SuperModeEnergy += 100;

			}
		}
	}
	
}

void PlayerAirPlaneMode::MoveUpdate(float _DeltaTime)
{
	float4 CamPos = GetLevel()->GetMainCamera()->GetTransform()->GetWorldPosition();
	float4 ScreenSize = GameEngineWindow::GetScreenSize() - MaxPlayerSize;

	float4 PlayerNextPos = GetTransform()->GetWorldPosition() + MoveVec * MoveSpeed * _DeltaTime;
	if (abs(PlayerNextPos.x - CamPos.x) < ScreenSize.hx() && abs(PlayerNextPos.y - CamPos.y) < ScreenSize.hy())
	{
		GetTransform()->AddLocalPosition(MoveVec * MoveSpeed * _DeltaTime);
	}
	MoveVec = float4::Zero;
}

void PlayerAirPlaneMode::CheckInput()
{
	if (true == GameEngineInput::IsPress("PlayerShmupSkill") && CurMode == "Origin")
	{
		if (SuperModeEnergy >= 500)
		{
			ChangeMode("Super");
			NextState = PlayerAirPlaneModeState::INTRO;
			SuperModeEnergy = 0;
		}
		else if (SuperModeEnergy >= 100)
		{
			NextState = PlayerAirPlaneModeState::SHOOT;
			SuperModeEnergy -= 100;
		}
		return;
	}
	if (true == GameEngineInput::IsPress("PlayerAirPlaneParry") && CurMode == "Origin")
	{
		NextState = PlayerAirPlaneModeState::PARRY;
		return;
	}


	if (true == GameEngineInput::IsPress("PlayerAirPlaneMoveLeft"))
	{
		MoveVec += float4::Left;
	}
	else if (true == GameEngineInput::IsPress("PlayerAirPlaneMoveRight"))
	{
		MoveVec += float4::Right;
	}
	if (true == GameEngineInput::IsPress("PlayerAirPlaneMoveUp"))
	{
		MoveVec += float4::Up;
		NextState = PlayerAirPlaneModeState::MOVE_UP;
	}
	else if (true == GameEngineInput::IsPress("PlayerAirPlaneMoveDown"))
	{
		MoveVec += float4::Down;
		NextState = PlayerAirPlaneModeState::MOVE_DOWN;
	}
	else
	{
		NextState = PlayerAirPlaneModeState::IDLE;

	}

	if ("Origin" == CurMode && true == GameEngineInput::IsPress("PlayerShrinkMode"))
	{

		ChangeMode("Shrink");
		return;

	}
	else if ("Shrink" == CurMode && false == GameEngineInput::IsPress("PlayerShrinkMode"))
	{

		ChangeMode("Origin");
		return;
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
	ShootInterVal -= _DeltaTime;

	if (true == GameEngineInput::IsPress("PlayerAttack")) // 'X'
	{
		Spark->On();
		if (0.0f > ShootInterVal)
		{
			std::shared_ptr<PeaShooter> bullet = GetLevel()->CreateActor<PeaShooter>(CupHeadActorOrder::PlayerWepaon);
			float4 _Pos = GetTransform()->GetWorldPosition() + float4(100, BulletYPos);
			_Pos.z = 350;
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
		std::shared_ptr<GameEngineActor> Effect = GetLevel()->CreateActor<BoomEffect>(CupHeadActorOrder::PlayerEffect);
		float4 Pos = GetTransform()->GetWorldPosition();
		Pos.z = 300;
		Effect->GetTransform()->SetLocalPosition(Pos);
		SuperModeBoomAttack();
		CurMode = _Mode.data();
	}
	CurMode = _Mode.data();
	ChangePlayerAnimation("Idle");
}

void PlayerAirPlaneMode::MakeSmoke(float _DeltaTime)
{

	SmokeInterval -= _DeltaTime;
	if (SmokeInterval < 0.0f)
	{
		SmokeInterval = 0.2f;
		std::shared_ptr< PlayerAirPlaneSmokeEffect> Smoke = GetLevel()->CreateActor< PlayerAirPlaneSmokeEffect>(CupHeadActorOrder::PlayerEffect);
		float4 Pos = GetTransform()->GetWorldPosition();
		Pos.x -= PlayerRender->GetTransform()->GetLocalScale().hx();
		Pos.y -= 15;
		Pos.z = 310;
		Smoke->GetTransform()->SetLocalPosition(Pos);
	}

}

void PlayerAirPlaneMode::TimeStop()
{
	GameEngineTime::GlobalTime.SetAllUpdateOrderTimeScale(0.0f);
	GameEngineTime::GlobalTime.SetAllRenderOrderTimeScale(0.0f);

	GameEngineTime::GlobalTime.SetUpdateOrderTimeScale(CupHeadActorOrder::Player, 1.0f);
	GameEngineTime::GlobalTime.SetRenderOrderTimeScale(CupHeadActorOrder::Player, 1.0f);
	GameEngineTime::GlobalTime.SetUpdateOrderTimeScale(CupHeadActorOrder::PlayerBackGround, 1.0f);
	GameEngineTime::GlobalTime.SetRenderOrderTimeScale(CupHeadActorOrder::PlayerBackGround, 1.0f);
}

void PlayerAirPlaneMode::TimePlay()
{
	GameEngineTime::GlobalTime.SetAllUpdateOrderTimeScale(1.0f);
	GameEngineTime::GlobalTime.SetAllRenderOrderTimeScale(1.0f);
}

void PlayerAirPlaneMode::Attack(int _Dmg)
{
	if ("Super" == CurMode)
	{
		ChangeMode("Origin");
		NextState = PlayerAirPlaneModeState::IDLE;
		InvincibleTime = 2.0f;
	}
	else
	{
		Player::Attack(_Dmg);
	}
}


void PlayerAirPlaneMode::SuperModeBoomAttack()
{
	float4 PlayerPos = GetTransform()->GetWorldPosition();
	for (std::shared_ptr<GameEngineCollision> _Col : GetLevel()->GetCollisionGroup(CupHeadCollisionOrder::Enemy))
	{
		std::shared_ptr<GameEnemy> ColActor = _Col->GetActor()->DynamicThis<GameEnemy>();
		if (PlayerPos.XYDistance(ColActor->GetTransform()->GetWorldPosition()) < 640.0f)
		{
			ColActor->Attack(20);
		}
	}
}