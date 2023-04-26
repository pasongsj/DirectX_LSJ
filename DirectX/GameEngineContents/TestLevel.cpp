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
}


void TestLevel::Start()
{
	//{
	//	GameEngineDirectory NewDir;
	//	NewDir.MoveParentToDirectory("ContentResources");
	//	NewDir.Move("ContentResources\\Texture");/*\\Cuphead_AirPlane");*/

	//	//\ContentResources\Texture\Cuphead_AirPlane

	//	std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });


	//	for (size_t i = 0; i < File.size(); i++)
	//	{
	//		GameEngineTexture::Load(File[i].GetFullPath());
	//	}

	//}


	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	//GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });



	std::shared_ptr<PlayerAirPlaneMode> NewPlayer = CreateActor<PlayerAirPlaneMode>("PlayerAirPlaneMode");
	std::shared_ptr<Hilda> NewBoss = CreateActor<Hilda>("Hilda");
	std::shared_ptr<Zeppling> NewMonster = CreateActor<Zeppling>("Zeppling");


}