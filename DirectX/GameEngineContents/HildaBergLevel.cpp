#include "PrecompileHeader.h"
#include "HildaBergLevel.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>

#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>



#include "HildaBergBack.h"
#include "PlayerAirPlaneMode.h"
#include "Hilda.h"
#include "Zeppling.h"
#include "Taurus.h"
#include "Sagittarius.h"
#include "Gemini.h"
#include "Moon.h"
//
//
#include "HildaBergBossController.h"

HildaBergLevel::HildaBergLevel() 
{
}

HildaBergLevel::~HildaBergLevel() 
{

}

void HildaBergLevel::Start()
{

	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	//GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });


	BackGround = CreateActor<HildaBergBack>("HildaBergBack");

	//std::shared_ptr<Hilda> NewBoss = CreateActor<Hilda>("Hilda");
	//std::shared_ptr<Taurus> NextBoss = CreateActor<Taurus>("Taurus");
	//std::shared_ptr<Sagittarius> NextBoss = CreateActor<Sagittarius>("Sagittarius");
	//std::shared_ptr<Gemini> NextBoss = CreateActor<Gemini>("Gemini");
	//std::shared_ptr<Moon> NewBoss = CreateActor<Moon>("Moon");
	std::shared_ptr<Zeppling> NewMonster = CreateActor<Zeppling>("Zeppling");
	std::shared_ptr<HildaBergBossController> NewBoss = CreateActor<HildaBergBossController>("HildaBergBossController");
	std::shared_ptr<PlayerAirPlaneMode> NewPlayer = CreateActor<PlayerAirPlaneMode>("PlayerAirPlaneMode");

}

void HildaBergLevel::Update(float _DeltaTime)
{
	if (nullptr == BackGround)
	{
		MsgAssert("배경 엑터가 설정되지 않았습니다");
	}
	BackGround->GetTransform()->AddLocalPosition(float4(-50 * _DeltaTime, 0));
}


void HildaBergLevel::LevelChangeStart()
{
	//std::shared_ptr<Gemini> NextBoss = CreateActor<Gemini>("Gemini");
}

void HildaBergLevel::LevelChangeEnd()
{

}