#include "PrecompileHeader.h"
#include "Wally1.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>


#include "GameContentsEnemyRenderer.h"
#include "ContentsSortRenderer.h"

#include "WallyEggSpin.h"


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

	GameEngineSprite::ReLoad(Dir.GetPlusFileName("House").GetFullPath(), "Wally1_House");
	// cuckoo intro
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Intro\\Feet\\Pendulum").GetFullPath(), "Wally1_Feet_Pendulum");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Intro\\Cuckoo").GetFullPath(), "Wally1_Cuckoo");
	// intro
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Intro\\Head").GetFullPath(), "Wally1_Head_Intro");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Intro\\Feet\\Morph").GetFullPath(), "Wally1_Feet_Morph");
	// idle
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Feet").GetFullPath(), "Wally1_Feet_Idle");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Head\\Idle\\Idle").GetFullPath(), "Wally1_Head_Idle");
	// barf
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Barf\\bird_barf_feet").GetFullPath(), "Wally1_Feet_Barf");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Barf\\bird_barf_head").GetFullPath(), "Wally1_Head_Barf");
	// handgun
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Handgun\\bird_handgun_head").GetFullPath(), "Wally1_Head_HandGun");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Feather Attack\\Steam").GetFullPath(), "Wally1_Head_Steam");
	// flap
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Feather Attack\\Flap\\Intro").GetFullPath(), "Wally1_Flap_Intro");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Feather Attack\\Flap\\Loop").GetFullPath(), "Wally1_Flap_Loop");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Feather Attack\\Flap\\Outro").GetFullPath(), "Wally1_Flap_Outro");
	// pant
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Feather Attack\\Pant").GetFullPath(), "Wally1_Head_Pant");
	// change phase - death
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Death\\bird_large_death").GetFullPath(), "Wally1_Dead");

}

void Wally1::Start()
{
	MakeSprite();
	// feet
	FeetRender = CreateComponent< ContentsSortRenderer>(CupHeadRendererOrder::Boss);
	FeetRender->CreateAnimation({ .AnimationName = "Feet_Pendulum_Intro",.SpriteName = "Wally1_Feet_Pendulum",.FrameInter = 0.05f,.Loop = true,.ScaleToTexture = true });
	FeetRender->CreateAnimation({ .AnimationName = "Feet_Intro",.SpriteName = "Wally1_Feet_Morph",.FrameInter = 0.05f,.Loop = false,.ScaleToTexture = true });
	FeetRender->CreateAnimation({ .AnimationName = "Feet_Idle",.SpriteName = "Wally1_Feet_Idle",.FrameInter = 0.05f,.Loop = true,.ScaleToTexture = true });
	FeetRender->CreateAnimation({ .AnimationName = "Feet_Barf",.SpriteName = "Wally1_Feet_Barf",.FrameInter = 0.05f,.Loop = false,.ScaleToTexture = true });


	//House
	HouseRender = CreateComponent< ContentsSortRenderer>(CupHeadRendererOrder::Boss);
	HouseRender->CreateAnimation({ .AnimationName = "House_Intro",.SpriteName = "Wally1_House",.FrameInter = 0.05f,.Loop = true,.ScaleToTexture = true });
	HouseRender->CreateAnimation({ .AnimationName = "Flap_Intro",.SpriteName = "Wally1_Flap_Intro",.FrameInter = 0.05f,.Loop = false,.ScaleToTexture = true });
	HouseRender->CreateAnimation({ .AnimationName = "Flap_Loop",.SpriteName = "Wally1_Flap_Loop",.FrameInter = 0.05f,.Loop = true,.ScaleToTexture = true });
	HouseRender->SetAnimationStartEvent("Flap_Loop", 7, [this] {FlapLoopCout++; });
	HouseRender->CreateAnimation({ .AnimationName = "Flap_Outro",.SpriteName = "Wally1_Flap_Outro",.FrameInter = 0.05f,.Loop = false,.ScaleToTexture = true });
	HouseRender->CreateAnimation({ .AnimationName = "Dead",.SpriteName = "Wally1_Dead",.FrameInter = 0.05f,.Loop = false,.ScaleToTexture = true });


	//Head
	HeadRender = CreateComponent< ContentsSortRenderer>(CupHeadRendererOrder::Boss);
	HeadRender->CreateAnimation({ .AnimationName = "Head_Cuckoo_Intro",.SpriteName = "Wally1_Cuckoo",.FrameInter = 0.05f,.Loop = true,.ScaleToTexture = true });
	HeadRender->SetAnimationStartEvent("Head_Cuckoo_Intro", 17, [this] { ++IntroCount; });
	HeadRender->CreateAnimation({ .AnimationName = "Head_Intro",.SpriteName = "Wally1_Head_Intro",.FrameInter = 0.05f,.Loop = false,.ScaleToTexture = true });
	HeadRender->CreateAnimation({ .AnimationName = "Head_Idle",.SpriteName = "Wally1_Head_Idle",.FrameInter = 0.05f,.Loop = true,.ScaleToTexture = true });
	HeadRender->CreateAnimation({ .AnimationName = "Head_Barf",.SpriteName = "Wally1_Head_Barf",.FrameInter = 0.05f,.Loop = false,.ScaleToTexture = true });
	HeadRender->SetAnimationStartEvent("Head_Barf", 7, [this] {
		std::shared_ptr<GameEngineActor> Egg = GetLevel()->CreateActor< WallyEggSpin>(CupHeadActorOrder::EnemyWeapon);
		Egg->GetTransform()->SetLocalPosition(HeadRender->GetTransform()->GetWorldPosition() + float4(-120, -30));
		});
	HeadRender->CreateAnimation({ .AnimationName = "Head_HandGun",.SpriteName = "Wally1_Head_HandGun",.FrameInter = 0.05f,.Loop = false,.ScaleToTexture = true });
	HeadRender->CreateAnimation({ .AnimationName = "Head_Steam",.SpriteName = "Wally1_Head_Steam",.FrameInter = 0.05f,.Loop = false,.ScaleToTexture = true });
	HeadRender->CreateAnimation({ .AnimationName = "Head_Pant",.SpriteName = "Wally1_Head_Pant",.FrameInter = 0.05f,.Loop = true,.ScaleToTexture = true });
	HeadRender->SetAnimationStartEvent("Head_Pant", 11, [this] {PantLoopCount++; });



	CuckooIntro_Start();
	//Intro_Start();

	//CUCKOOINTRO
	StartFuncPtr[static_cast<int>(Wally1State::CUCKOOINTRO)] = std::bind(&Wally1::CuckooIntro_Start, this);
	UpdateFuncPtr[static_cast<int>(Wally1State::CUCKOOINTRO)] = std::bind(&Wally1::CuckooIntro_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(Wally1State::CUCKOOINTRO)] = std::bind(&Wally1::CuckooIntro_End, this);

	//INTRO
	StartFuncPtr[static_cast<int>(Wally1State::INTRO)] = std::bind(&Wally1::Intro_Start, this);
	UpdateFuncPtr[static_cast<int>(Wally1State::INTRO)] = std::bind(&Wally1::Intro_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(Wally1State::INTRO)] = std::bind(&Wally1::Intro_End, this);

	//IDLE
	StartFuncPtr[static_cast<int>(Wally1State::IDLE)] = std::bind(&Wally1::Idle_Start, this);
	UpdateFuncPtr[static_cast<int>(Wally1State::IDLE)] = std::bind(&Wally1::Idle_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(Wally1State::IDLE)] = std::bind(&Wally1::Idle_End, this);

	//BARF
	StartFuncPtr[static_cast<int>(Wally1State::BARF)] = std::bind(&Wally1::Barf_Start, this);
	UpdateFuncPtr[static_cast<int>(Wally1State::BARF)] = std::bind(&Wally1::Barf_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(Wally1State::BARF)] = std::bind(&Wally1::Barf_End, this);

	//HANDGUN
	StartFuncPtr[static_cast<int>(Wally1State::HANDGUN)] = std::bind(&Wally1::HandGun_Start, this);
	UpdateFuncPtr[static_cast<int>(Wally1State::HANDGUN)] = std::bind(&Wally1::HandGun_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(Wally1State::HANDGUN)] = std::bind(&Wally1::HandGun_End, this);

	//CHANGEPHASE
	StartFuncPtr[static_cast<int>(Wally1State::CHANGEPHASE)] = std::bind(&Wally1::ChangePhase_Start, this);
	UpdateFuncPtr[static_cast<int>(Wally1State::CHANGEPHASE)] = std::bind(&Wally1::ChangePhase_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(Wally1State::CHANGEPHASE)] = std::bind(&Wally1::ChangePhase_End, this);

	//STEAM
	StartFuncPtr[static_cast<int>(Wally1State::STEAM)] = std::bind(&Wally1::Steam_Start, this);
	UpdateFuncPtr[static_cast<int>(Wally1State::STEAM)] = std::bind(&Wally1::Steam_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(Wally1State::STEAM)] = std::bind(&Wally1::Steam_End, this);
	
	//FEATHERS
	StartFuncPtr[static_cast<int>(Wally1State::FLAP)] = std::bind(&Wally1::Flap_Start, this);
	UpdateFuncPtr[static_cast<int>(Wally1State::FLAP)] = std::bind(&Wally1::Flap_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(Wally1State::FLAP)] = std::bind(&Wally1::Flap_End, this);
	
	//PANT
	StartFuncPtr[static_cast<int>(Wally1State::PANT)] = std::bind(&Wally1::Pant_Start, this);
	UpdateFuncPtr[static_cast<int>(Wally1State::PANT)] = std::bind(&Wally1::Pant_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(Wally1State::PANT)] = std::bind(&Wally1::Pant_End, this);

	GetTransform()->SetLocalPosition({ 420, 0 });

	if (false == GameEngineInput::IsKey("PressF"))
	{
		GameEngineInput::CreateKey("PressF", 'F');
	}
}

void Wally1::Update(float _DeltaTime)
{
	if (GameEngineInput::IsPress("PressF"))
	{
		NextState = Wally1State::BARF;
	}
	UpdateState(_DeltaTime);
}


void Wally1::UpdateState(float _DeltaTime)
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

void Wally1::MoveUpdate(float _DeltaTime)
{
	MoveDuration += _DeltaTime;
	float4 ReturnValue = float4(420, sinf(MoveDuration * 2.5f) * MoveRange);
	GetTransform()->SetLocalPosition(ReturnValue);
}
