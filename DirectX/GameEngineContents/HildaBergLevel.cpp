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

HildaBergLevel::HildaBergLevel() 
{
}

HildaBergLevel::~HildaBergLevel() 
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

void HildaBergLevel::Start()
{
	//{
	//	GameEngineDirectory NewDir;
	//	NewDir.MoveParentToDirectory("ContentResources");
	//	NewDir.Move("ContentResources");

	//	std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });


	//	for (size_t i = 0; i < File.size(); i++)
	//	{
	//		GameEngineTexture::Load(File[i].GetFullPath());
	//	}

	//}

	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	//GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });


	BackGround = CreateActor<HildaBergBack>("HildaBergBack");
	std::shared_ptr<Hilda> NewBoss = CreateActor<Hilda>("Hilda");
	//std::shared_ptr<Taurus> NextBoss = CreateActor<Taurus>("Taurus");
	//std::shared_ptr<Sagittarius> NextBoss = CreateActor<Sagittarius>("Sagittarius");
	//std::shared_ptr<Gemini> NextBoss = CreateActor<Gemini>("Gemini");
	//std::shared_ptr<Zeppling> NewMonster = CreateActor<Zeppling>("Zeppling");
	std::shared_ptr<PlayerAirPlaneMode> NewPlayer = CreateActor<PlayerAirPlaneMode>("PlayerAirPlaneMode");

}

void HildaBergLevel::Update(float _DeltaTime)
{
	BackGround->GetTransform()->AddLocalPosition(float4(-50 * _DeltaTime, 0));
}