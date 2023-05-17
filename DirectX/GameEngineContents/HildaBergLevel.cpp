#include "PrecompileHeader.h"
#include "HildaBergLevel.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>

#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>



// BackGround
#include "HildaBergBack1.h"
#include "HildaBergBack0.h"

// Player
#include "PlayerAirPlaneMode.h"

// Boss
#include "Hilda.h"
#include "Zeppling.h"
#include "Taurus.h"
#include "Sagittarius.h"
#include "Gemini.h"
#include "Moon.h"
#include "HildaBergBossController.h"

// Test
#include "HIldaMoonUFO.h"
#include "ZepplingBullet.h"


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


}

void HildaBergLevel::Update(float _DeltaTime)
{
	if (GetLiveTime() > NextSponeTime)
	{
		//std::shared_ptr<Zeppling> NewMonster = CreateActor<Zeppling>(CupHeadActorOrder::Enemy);
		std::shared_ptr<HIldaMoonUFO> NewMonster = CreateActor<HIldaMoonUFO>(CupHeadActorOrder::Enemy);
		NextSponeTime += 5.0f;
	}
}


void HildaBergLevel::LevelChangeStart()
{
	ResetLiveTime();


	GameEngineDirectory NewDir;
	NewDir.MoveParentToDirectory("ContentResources");
	NewDir.Move("ContentResources\\Texture\\stage1\\Boss\\Hilda\\Level");
	std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });
	for (size_t i = 0; i < File.size(); i++)
	{
		GameEngineTexture::Load(File[i].GetFullPath());
	}

	//std::shared_ptr<Gemini> NextBoss = CreateActor<Gemini>("Gemini");

	CreateActor<HildaBergBack0>(CupHeadActorOrder::BackGround);
	CreateActor<HildaBergBack1>(CupHeadActorOrder::BackGround);

	//std::shared_ptr<Hilda> NewBoss = CreateActor<Hilda>("Hilda");
	//std::shared_ptr<Taurus> NextBoss = CreateActor<Taurus>("Taurus");
	//std::shared_ptr<Sagittarius> NextBoss = CreateActor<Sagittarius>("Sagittarius");
	//std::shared_ptr<Gemini> NextBoss = CreateActor<Gemini>(CupHeadActorOrder::Boss);
	//std::shared_ptr<Moon> NewBoss = CreateActor<Moon>("Moon");
	//std::shared_ptr<Zeppling> NewMonster = CreateActor<Zeppling>("Zeppling");
	//std::shared_ptr<HIldaMoonUFO> NewMonster = CreateActor<HIldaMoonUFO>("HIldaMoonUFO");
	//std::shared_ptr<ZepplingBullet> NewMonster = CreateActor<ZepplingBullet>(CupHeadActorOrder::Enemy);
	//std::shared_ptr<HildaBergBossController> NewBoss = CreateActor<HildaBergBossController>(CupHeadActorOrder::Boss);
	std::shared_ptr<PlayerAirPlaneMode> NewPlayer = CreateActor<PlayerAirPlaneMode>(CupHeadActorOrder::Player);
}

void HildaBergLevel::LevelChangeEnd()
{
	
}