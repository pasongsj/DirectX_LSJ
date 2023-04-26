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



void Zeppling::Start()
{
	// 위치
	GetTransform()->SetLocalPosition(float4(500.0f, 0));

	// 몬스터 이미지 랜더러
	Monster = CreateComponent<GameEngineSpriteRenderer>();
	Monster->SetTexture("a_blimp_enemy_idle_0001.png");
	// 위치,회전, 크기
	Monster->GetTransform()->SetLocalScale(float4(156, 94)*0.8f);
	


	//FSM
	
	//MOVE
	StartFuncPtr[static_cast<int>(ZepplingState::MOVE)] = std::bind(&Zeppling::Move_Start, this);
	UpdateFuncPtr[static_cast<int>(ZepplingState::MOVE)] = std::bind(&Zeppling::Move_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(ZepplingState::MOVE)] = std::bind(&Zeppling::Move_End, this);

	//SHOOT
	StartFuncPtr[static_cast<int>(ZepplingState::SHOOT)] = std::bind(&Zeppling::Shoot_Start, this);
	UpdateFuncPtr[static_cast<int>(ZepplingState::SHOOT)] = std::bind(&Zeppling::Shoot_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(ZepplingState::SHOOT)] = std::bind(&Zeppling::Shoot_End, this);

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