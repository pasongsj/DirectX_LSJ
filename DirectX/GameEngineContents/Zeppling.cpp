#include "PrecompileHeader.h"
#include "Zeppling.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>


//std::vector<std::shared_ptr<Zeppling>> Zeppling::AllZepplings;

Zeppling::Zeppling() 
{
}

Zeppling::~Zeppling() 
{
}

void Zeppling::MakeSprite()
{
	if (nullptr == GameEngineSprite::Find("BlimpEnemy_PurPle_Idle"))
	{

		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");;
		NewDir.Move("ContentResources\\Texture\\stage1\\Boss\\Hilda\\BlimpEnemy");

		// idle
		GameEngineSprite::LoadFolder("BlimpEnemy_PurPle_Idle", NewDir.GetPlusFileName("Purple\\Idle").GetFullPath());
		GameEngineSprite::LoadFolder("BlimpEnemy_Green_Idle", NewDir.GetPlusFileName("Green\\Idle").GetFullPath());
		// attack				
		GameEngineSprite::LoadFolder("BlimpEnemy_Purple_Attack", NewDir.GetPlusFileName("Purple\\Attack").GetFullPath());
		GameEngineSprite::LoadFolder("BlimpEnemy_Green_Attack", NewDir.GetPlusFileName("Green\\Attack").GetFullPath());
		// turn						
		GameEngineSprite::LoadFolder("BlimpEnemy_Purple_Turn", NewDir.GetPlusFileName("Purple\\Turn").GetFullPath());
		GameEngineSprite::LoadFolder("BlimpEnemy_Green_Turn", NewDir.GetPlusFileName("Green\\Turn").GetFullPath());


	}
}



void Zeppling::Start()
{
	MakeSprite();
	EnemyRender = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::Enemy);
	float4x4 tmpmatrix1 = GetTransform()->GetWorldMatrix();
	float4x4 Enemytmpmatrix0 = EnemyRender->GetTransform()->GetLocalWorldMatrix();
	float4x4 Enemytmpmatrix1 = EnemyRender->GetTransform()->GetWorldMatrix();


	// 몬스터 이미지 랜더러

	EnemyRender->CreateAnimation({ .AnimationName = "Purple_Idle",  .SpriteName = "BlimpEnemy_PurPle_Idle", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
	EnemyRender->CreateAnimation({ .AnimationName = "Purple_Back",  .SpriteName = "BlimpEnemy_PurPle_Idle", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true/* ,.FlipX = true*/});
	EnemyRender->CreateAnimation({ .AnimationName = "Green_Idle",  .SpriteName = "BlimpEnemy_Green_Idle", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
	EnemyRender->CreateAnimation({ .AnimationName = "Green_Back",  .SpriteName = "BlimpEnemy_Green_Idle", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true /*,.FlipX = true */});

	EnemyRender->CreateAnimation({ .AnimationName = "Purple_Attack",  .SpriteName = "BlimpEnemy_Purple_Attack", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	EnemyRender->CreateAnimation({ .AnimationName = "Green_Attack",  .SpriteName = "BlimpEnemy_Green_Attack", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	
	EnemyRender->CreateAnimation({ .AnimationName = "Purple_Turn",  .SpriteName = "BlimpEnemy_Purple_Turn", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	EnemyRender->CreateAnimation({ .AnimationName = "Green_Turn",  .SpriteName = "BlimpEnemy_Green_Turn", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	

	EnemyRender->ChangeAnimation(Mode + "Idle");
	// 위치,회전, 크기

	EnemyCollision = CreateComponent<GameEngineCollision>(CupHeadCollisionOrder::Enemy);
	EnemyCollision->GetTransform()->SetLocalScale(float4(100, 100));
	EnemyCollision->SetColType(ColType::SPHERE2D);
	
	HP = 10;

	ScreenSize = GameEngineWindow::GetScreenSize();
	float4 Pos = float4(ScreenSize.hx(), GameEngineRandom::MainRandom.RandomFloat(-ScreenSize.hy() / 2, ScreenSize.hy() - 50));
	GetTransform()->SetLocalPosition(Pos);

	SetName("Zeppling");

	//FSM
	
	//MOVE
	StartFuncPtr[static_cast<int>(ZepplingState::MOVE)] = std::bind(&Zeppling::Move_Start, this);
	UpdateFuncPtr[static_cast<int>(ZepplingState::MOVE)] = std::bind(&Zeppling::Move_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(ZepplingState::MOVE)] = std::bind(&Zeppling::Move_End, this);

	//SHOOT
	StartFuncPtr[static_cast<int>(ZepplingState::SHOOT)] = std::bind(&Zeppling::Shoot_Start, this);
	UpdateFuncPtr[static_cast<int>(ZepplingState::SHOOT)] = std::bind(&Zeppling::Shoot_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(ZepplingState::SHOOT)] = std::bind(&Zeppling::Shoot_End, this);

	//TURN
	StartFuncPtr[static_cast<int>(ZepplingState::TURN)] = std::bind(&Zeppling::Turn_Start, this);
	UpdateFuncPtr[static_cast<int>(ZepplingState::TURN)] = std::bind(&Zeppling::Turn_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(ZepplingState::TURN)] = std::bind(&Zeppling::Turn_End, this);

	//BACK
	StartFuncPtr[static_cast<int>(ZepplingState::BACK)] = std::bind(&Zeppling::Back_Start, this);
	UpdateFuncPtr[static_cast<int>(ZepplingState::BACK)] = std::bind(&Zeppling::Back_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(ZepplingState::BACK)] = std::bind(&Zeppling::Back_End, this);

	//DEAD
	StartFuncPtr[static_cast<int>(ZepplingState::DEAD)] = std::bind(&Zeppling::Dead_Start, this);
	UpdateFuncPtr[static_cast<int>(ZepplingState::DEAD)] = std::bind(&Zeppling::Dead_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(ZepplingState::DEAD)] = std::bind(&Zeppling::Dead_End, this);

	//AllZepplings.emplace_back(this);

}

void Zeppling::Update(float _DeltaTime)
{
	UpdateState(_DeltaTime);
}

void Zeppling::Render(float _DeltaTime)
{

}


void Zeppling::UpdateState(float _DeltaTime)
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


void Zeppling::CheckDeath()
{
	if (HP <= 0)
	{
		NextState = ZepplingState::DEAD;
	}
}