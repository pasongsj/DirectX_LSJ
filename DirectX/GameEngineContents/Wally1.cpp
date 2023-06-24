#include "PrecompileHeader.h"
#include "Wally1.h"
#include "GameContentsEnemyRenderer.h"

Wally1::Wally1()
{
}

Wally1::~Wally1()
{
}
void Wally1::MakeSprite()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentResources");
	Dir.Move("ContentResources\\Texture\\stage2\\Boss\\Wally\\Phase 1");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("House").GetFullPath(), "WallyHouse");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Intro\\Feet\\Pendulum").GetFullPath(), "Feet_Pendulum");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Intro\\Cuckoo").GetFullPath(), "Cuckoo");

}

void Wally1::Start()
{
	MakeSprite();
	FeetRender = CreateComponent< GameContentsEnemyRenderer>(CupHeadRendererOrder::Boss);
	FeetRender->CreateAnimation({ .AnimationName = "Feet_Idle",.SpriteName = "Feet_Pendulum",.FrameInter = 0.05f,.Loop = true,.ScaleToTexture = true });
	FeetRender->ChangeAnimation("Feet_Idle");
	FeetRender->GetTransform()->SetLocalPosition(float4(0, -150));

	HouseRender = CreateComponent< GameContentsEnemyRenderer>(CupHeadRendererOrder::Boss);
	HouseRender->CreateAnimation({ .AnimationName = "House_Idle",.SpriteName = "WallyHouse",.FrameInter = 0.05f,.Loop = true,.ScaleToTexture = true });
	HouseRender->ChangeAnimation("House_Idle");

	HeadRender = CreateComponent< GameContentsEnemyRenderer>(CupHeadRendererOrder::Boss);
	HeadRender->CreateAnimation({ .AnimationName = "Head_Idle",.SpriteName = "Cuckoo",.FrameInter = 0.05f,.Loop = true,.ScaleToTexture = true });
	HeadRender->ChangeAnimation("Head_Idle");


	//INTRO
	StartFuncPtr[static_cast<int>(Wally1State::INTRO)] = std::bind(&Wally1::Intro_Start, this);
	UpdateFuncPtr[static_cast<int>(Wally1State::INTRO)] = std::bind(&Wally1::Intro_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(Wally1State::INTRO)] = std::bind(&Wally1::Intro_End, this);

	//IDLE
	StartFuncPtr[static_cast<int>(Wally1State::IDLE)] = std::bind(&Wally1::Idle_Start, this);
	UpdateFuncPtr[static_cast<int>(Wally1State::IDLE)] = std::bind(&Wally1::Idle_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(Wally1State::IDLE)] = std::bind(&Wally1::Idle_End, this);

	//SHOOT
	StartFuncPtr[static_cast<int>(Wally1State::SHOOT)] = std::bind(&Wally1::Shoot_Start, this);
	UpdateFuncPtr[static_cast<int>(Wally1State::SHOOT)] = std::bind(&Wally1::Shoot_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(Wally1State::SHOOT)] = std::bind(&Wally1::Shoot_End, this);

	//CHANGEPHASE
	StartFuncPtr[static_cast<int>(Wally1State::CHANGEPHASE)] = std::bind(&Wally1::ChangePhase_Start, this);
	UpdateFuncPtr[static_cast<int>(Wally1State::CHANGEPHASE)] = std::bind(&Wally1::ChangePhase_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(Wally1State::CHANGEPHASE)] = std::bind(&Wally1::ChangePhase_End, this);

	//STEAM
	StartFuncPtr[static_cast<int>(Wally1State::STEAM)] = std::bind(&Wally1::Steam_Start, this);
	UpdateFuncPtr[static_cast<int>(Wally1State::STEAM)] = std::bind(&Wally1::Steam_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(Wally1State::STEAM)] = std::bind(&Wally1::Steam_End, this);
}

void Wally1::Update(float _DeltaTime)
{
}
