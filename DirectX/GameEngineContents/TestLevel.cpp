#include "PrecompileHeader.h"
#include "TestLevel.h"

#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>

#include "PlayerAirPlaneMode.h"
#include "Hilda.h"
#include "Zeppling.h"


TestLevel::TestLevel() 
{
}

TestLevel::~TestLevel() 
{
	//for (int i = 0; i < Zeppling::AllZepplings.size(); i++)
	//{
	//	if (nullptr != Zeppling::AllZepplings[i])
	//	{
	//		Zeppling::AllZepplings[i]->Death();
	//		Zeppling::AllZepplings[i] = nullptr;
	//	}
	//}
}


void TestLevel::Start()
{


	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	//GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });



	//std::shared_ptr<PlayerAirPlaneMode> NewPlayer = CreateActor<PlayerAirPlaneMode>("PlayerAirPlaneMode");
	//std::shared_ptr<Hilda> NewBoss = CreateActor<Hilda>("Hilda");
	//std::shared_ptr<Zeppling> NewMonster = CreateActor<Zeppling>("Zeppling");


}