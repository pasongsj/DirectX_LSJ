#include "PrecompileHeader.h"
#include "Wally1.h"

Wally1::Wally1()
{
}

Wally1::~Wally1()
{
}
void Wally1::Start()
{
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
