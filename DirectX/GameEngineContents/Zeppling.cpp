#include "PrecompileHeader.h"
#include "Zeppling.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>


//std::vector<std::shared_ptr<Zeppling>> Zeppling::AllZepplings;

Zeppling::Zeppling() 
{
}

Zeppling::~Zeppling() 
{
}

void Zeppling::MakeSprite()
{
	if (nullptr == GameEngineSprite::Find("PurPle_Idle"))
	{

		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("stage1\\Boss\\Hilda\\BlimpEnemy");

		// idle
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Purple\\Idle").GetFullPath(), "PurPle_Idle");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Green\\Idle").GetFullPath(), "Green_Idle");
		// attack
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Purple\\Attack").GetFullPath(), "Purple_Attack");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Green\\Attack").GetFullPath(), "Green_Attack");
		// turn
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Purple\\Turn").GetFullPath(), "Purple_Turn");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Green\\Turn").GetFullPath(), "Green_Turn");

		// death
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Green\\Pieces\\A").GetFullPath(), "Green_Deah_A");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Green\\Pieces\\B").GetFullPath(), "Green_Deah_B");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Green\\Pieces\\C").GetFullPath(), "Green_Deah_C");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Green\\Pieces\\D").GetFullPath(), "Green_Deah_D");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Green\\Pieces\\E").GetFullPath(), "Green_Deah_E");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Green\\Pieces\\F").GetFullPath(), "Green_Deah_F");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Purple\\Pieces\\A").GetFullPath(), "Purple_Deah_A");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Purple\\Pieces\\B").GetFullPath(), "Purple_Deah_B");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Purple\\Pieces\\C").GetFullPath(), "Purple_Deah_C");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Purple\\Pieces\\D").GetFullPath(), "Purple_Deah_D");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Purple\\Pieces\\E").GetFullPath(), "Purple_Deah_E");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Purple\\Pieces\\F").GetFullPath(), "Purple_Deah_F");

	}
}



void Zeppling::Start()
{
	MakeSprite();
	// 위치
	GetTransform()->SetWorldPosition(float4(500.0f, 0));

	// 몬스터 이미지 랜더러
	Monster = CreateComponent<GameEngineSpriteRenderer>();

	Monster->CreateAnimation({ .AnimationName = "PurPle_Idle",  .SpriteName = "PurPle_Idle", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
	Monster->CreateAnimation({ .AnimationName = "PurPle_Back",  .SpriteName = "PurPle_Idle", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true ,.FlipX = true});
	Monster->CreateAnimation({ .AnimationName = "Green_Idle",  .SpriteName = "Green_Idle", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
	Monster->CreateAnimation({ .AnimationName = "Green_Back",  .SpriteName = "Green_Idle", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true ,.FlipX = true });

	Monster->CreateAnimation({ .AnimationName = "Purple_Attack",  .SpriteName = "Purple_Attack", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	Monster->CreateAnimation({ .AnimationName = "Green_Attack",  .SpriteName = "Green_Attack", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });

	Monster->CreateAnimation({ .AnimationName = "Purple_Turn",  .SpriteName = "Purple_Turn", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	Monster->CreateAnimation({ .AnimationName = "Green_Turn",  .SpriteName = "Green_Turn", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });

	Monster->CreateAnimation({ .AnimationName = "Green_Deah_A",  .SpriteName = "Green_Deah_A", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	Monster->CreateAnimation({ .AnimationName = "Green_Deah_B",  .SpriteName = "Green_Deah_B", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	Monster->CreateAnimation({ .AnimationName = "Green_Deah_C",  .SpriteName = "Green_Deah_C", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	Monster->CreateAnimation({ .AnimationName = "Green_Deah_D",  .SpriteName = "Green_Deah_D", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	Monster->CreateAnimation({ .AnimationName = "Green_Deah_E",  .SpriteName = "Green_Deah_E", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	Monster->CreateAnimation({ .AnimationName = "Green_Deah_F",  .SpriteName = "Green_Deah_F", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });

	Monster->CreateAnimation({ .AnimationName = "Purple_Deah_A",  .SpriteName = "Purple_Deah_A", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	Monster->CreateAnimation({ .AnimationName = "Purple_Deah_B",  .SpriteName = "Purple_Deah_B", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	Monster->CreateAnimation({ .AnimationName = "Purple_Deah_C",  .SpriteName = "Purple_Deah_C", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	Monster->CreateAnimation({ .AnimationName = "Purple_Deah_D",  .SpriteName = "Purple_Deah_D", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	Monster->CreateAnimation({ .AnimationName = "Purple_Deah_E",  .SpriteName = "Purple_Deah_E", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	Monster->CreateAnimation({ .AnimationName = "Purple_Deah_F",  .SpriteName = "Purple_Deah_F", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });


	Monster->ChangeAnimation(Mode + "Idle");
	//Monster->SetTexture("a_blimp_enemy_idle_0001.png");
	//Monster->SetScaleToTexture("a_blimp_enemy_idle_0001.png");
	// 위치,회전, 크기
	float4 Pos = float4(GameEngineWindow::GetScreenSize().hx(), 0);
	GetTransform()->SetLocalPosition(Pos);
	


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

void Zeppling::Reset()
{
	// 변수 reset
	CurState = ZepplingState::MOVE;
	NextState = ZepplingState::MOVE;
	MoveLen = 0.0f;

	// 이미지랜더 reset

	
}