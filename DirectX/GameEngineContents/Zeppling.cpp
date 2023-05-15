#include "PrecompileHeader.h"
#include "Zeppling.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>


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
		GameEngineSprite::LoadFolder("PurPle_Idle", NewDir.GetPlusFileName("Purple\\Idle").GetFullPath());
		GameEngineSprite::LoadFolder("Green_Idle", NewDir.GetPlusFileName("Green\\Idle").GetFullPath());
		// attack
		GameEngineSprite::LoadFolder("Purple_Attack", NewDir.GetPlusFileName("Purple\\Attack").GetFullPath());
		GameEngineSprite::LoadFolder("Green_Attack", NewDir.GetPlusFileName("Green\\Attack").GetFullPath());
		// turn
		GameEngineSprite::LoadFolder("Purple_Turn", NewDir.GetPlusFileName("Purple\\Turn").GetFullPath());
		GameEngineSprite::LoadFolder("Green_Turn", NewDir.GetPlusFileName("Green\\Turn").GetFullPath());

		// death
		GameEngineSprite::LoadFolder("Green_Death_A", NewDir.GetPlusFileName("Green\\Pieces\\A").GetFullPath());
		GameEngineSprite::LoadFolder("Green_Death_B", NewDir.GetPlusFileName("Green\\Pieces\\B").GetFullPath());
		GameEngineSprite::LoadFolder("Green_Death_C", NewDir.GetPlusFileName("Green\\Pieces\\C").GetFullPath());
		GameEngineSprite::LoadFolder("Green_Death_D", NewDir.GetPlusFileName("Green\\Pieces\\D").GetFullPath());
		GameEngineSprite::LoadFolder("Green_Death_E", NewDir.GetPlusFileName("Green\\Pieces\\E").GetFullPath());
		GameEngineSprite::LoadFolder("Green_Death_F", NewDir.GetPlusFileName("Green\\Pieces\\F").GetFullPath());

		GameEngineSprite::LoadFolder("Purple_Death_A", NewDir.GetPlusFileName("Purple\\Pieces\\A").GetFullPath());
		GameEngineSprite::LoadFolder("Purple_Death_B", NewDir.GetPlusFileName("Purple\\Pieces\\B").GetFullPath());
		GameEngineSprite::LoadFolder("Purple_Death_C", NewDir.GetPlusFileName("Purple\\Pieces\\C").GetFullPath());
		GameEngineSprite::LoadFolder("Purple_Death_D", NewDir.GetPlusFileName("Purple\\Pieces\\D").GetFullPath());
		GameEngineSprite::LoadFolder("Purple_Death_E", NewDir.GetPlusFileName("Purple\\Pieces\\E").GetFullPath());
		GameEngineSprite::LoadFolder("Purple_Death_F", NewDir.GetPlusFileName("Purple\\Pieces\\F").GetFullPath());

	}
}



void Zeppling::Start()
{
	MakeSprite();
	Enemy = CreateComponent<GameEngineSpriteRenderer>();
	float4x4 tmpmatrix1 = GetTransform()->GetWorldMatrix();
	float4x4 Enemytmpmatrix0 = Enemy->GetTransform()->GetLocalWorldMatrix();
	float4x4 Enemytmpmatrix1 = Enemy->GetTransform()->GetWorldMatrix();


	// 몬스터 이미지 랜더러

	Enemy->CreateAnimation({ .AnimationName = "Purple_Idle",  .SpriteName = "PurPle_Idle", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
	Enemy->CreateAnimation({ .AnimationName = "Purple_Back",  .SpriteName = "PurPle_Idle", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true/* ,.FlipX = true*/});
	Enemy->CreateAnimation({ .AnimationName = "Green_Idle",  .SpriteName = "Green_Idle", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
	Enemy->CreateAnimation({ .AnimationName = "Green_Back",  .SpriteName = "Green_Idle", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true /*,.FlipX = true */});

	Enemy->CreateAnimation({ .AnimationName = "Purple_Attack",  .SpriteName = "Purple_Attack", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	Enemy->CreateAnimation({ .AnimationName = "Green_Attack",  .SpriteName = "Green_Attack", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });

	Enemy->CreateAnimation({ .AnimationName = "Purple_Turn",  .SpriteName = "Purple_Turn", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	Enemy->CreateAnimation({ .AnimationName = "Green_Turn",  .SpriteName = "Green_Turn", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });

	Enemy->CreateAnimation({ .AnimationName = "Green_Death_A",  .SpriteName = "Green_Death_A", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	Enemy->CreateAnimation({ .AnimationName = "Green_Death_B",  .SpriteName = "Green_Death_B", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	Enemy->CreateAnimation({ .AnimationName = "Green_Death_C",  .SpriteName = "Green_Death_C", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	Enemy->CreateAnimation({ .AnimationName = "Green_Death_D",  .SpriteName = "Green_Death_D", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	Enemy->CreateAnimation({ .AnimationName = "Green_Death_E",  .SpriteName = "Green_Death_E", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	Enemy->CreateAnimation({ .AnimationName = "Green_Death_F",  .SpriteName = "Green_Death_F", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });

	Enemy->CreateAnimation({ .AnimationName = "Purple_Death_A",  .SpriteName = "Purple_Death_A", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	Enemy->CreateAnimation({ .AnimationName = "Purple_Death_B",  .SpriteName = "Purple_Death_B", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	Enemy->CreateAnimation({ .AnimationName = "Purple_Death_C",  .SpriteName = "Purple_Death_C", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	Enemy->CreateAnimation({ .AnimationName = "Purple_Death_D",  .SpriteName = "Purple_Death_D", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	Enemy->CreateAnimation({ .AnimationName = "Purple_Death_E",  .SpriteName = "Purple_Death_E", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	Enemy->CreateAnimation({ .AnimationName = "Purple_Death_F",  .SpriteName = "Purple_Death_F", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });


	Enemy->ChangeAnimation(Mode + "Idle");
	// 위치,회전, 크기

	ScreenSize = GameEngineWindow::GetScreenSize();
	float4 Pos = float4(ScreenSize.hx(), GameEngineRandom::MainRandom.RandomFloat(-ScreenSize.hy() / 2, ScreenSize.hy() - 50));
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
