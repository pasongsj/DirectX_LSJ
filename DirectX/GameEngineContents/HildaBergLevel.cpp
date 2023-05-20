#include "PrecompileHeader.h"
#include "HildaBergLevel.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>



// BackGround
#include "HildaBergBack0.h"
#include "HildaBergBack1.h"
#include "HildaBergBack2.h"
#include "HildaBergBack3.h"

// Player
#include "PlayerAirPlaneMode.h"

// Boss
#include "Hilda.h"
#include "Zeppling.h"
#include "Taurus.h"
#include "Sagittarius.h"
#include "Gemini.h"
#include "Moon.h"

#include "HildaBoss.h"

// Test
#include "HIldaMoonUFO.h"
#include "ZepplingBullet.h"
#include "PlayerAirPlaneSmokeEffect.h"


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
	GetMainCamera()->isZsort = true;

	if (false == GameEngineInput::IsKey("NextBoss"))
	{
		GameEngineInput::CreateKey("NextBoss", VK_F2);
	}


}

void HildaBergLevel::Update(float _DeltaTime)
{
	if (GetLiveTime() > NextSponeTime)
	{
		//std::shared_ptr<Zeppling> NewMonster = CreateActor<Zeppling>(CupHeadActorOrder::Enemy);
		//std::shared_ptr<HIldaMoonUFO> NewMonster = CreateActor<HIldaMoonUFO>(CupHeadActorOrder::Enemy);
		NextSponeTime += 5.0f;
	}

	if (nullptr == Boss)
	{
		++Phase;
		switch (Phase)
		{
		case 1:
		{
			Boss = CreateActor<Hilda>(CupHeadActorOrder::Boss);
			break;
		}
		case 2:
		{
			Boss = CreateActor<Taurus>(CupHeadActorOrder::Boss);
			break;
		}
		case 3:
		{
			Boss = CreateActor<Hilda>(CupHeadActorOrder::Boss);
			Boss->SetPhase(3);

			break;
		}
		case 4:
		{
			int RandomNum = GameEngineRandom::MainRandom.RandomInt(0, 9);
			if (1 == (RandomNum & 1))
			{
				Boss = GetLevel()->CreateActor<Sagittarius>(CupHeadActorOrder::Boss);
			}
			else
			{
				Boss = CreateActor<Gemini>(CupHeadActorOrder::Boss);
			}
			break;
		}
		case 5:
		{
			Boss = CreateActor<Hilda>(CupHeadActorOrder::Boss);
			Boss->SetPhase(5);
			//std::shared_ptr<Hilda> HildaTmp = DynamicThis<Hilda>();
			//HildaTmp->SetHildaPhase(5);
			break;
		}
		case 6:
		{
			Boss = CreateActor<Moon>(CupHeadActorOrder::Boss);
			break;
		}
		default:
			break;
		}
	}

	if (nullptr != Boss && true == GameEngineInput::IsDown("NextBoss"))
	{
		Boss->Death();
		Boss = nullptr;
	}
}


void HildaBergLevel::LevelChangeStart()
{
	ResetLiveTime();

	// BackGround 이미지 로드
	if (nullptr == GameEngineTexture::Find("blimp_clouds_0001.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources\\Texture\\stage1\\Boss\\Hilda\\Level");
		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });
		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}

	CreateActor<HildaBergBack0>(CupHeadActorOrder::BackGround);
	CreateActor<HildaBergBack1>(CupHeadActorOrder::BackGround);
	CreateActor<HildaBergBack2>(CupHeadActorOrder::BackGround);
	CreateActor<HildaBergBack3>(CupHeadActorOrder::BackGround);
	CreateActor<PlayerAirPlaneSmokeEffect>(CupHeadActorOrder::PlayerEffect);



	//std::shared_ptr<Gemini> NextBoss = CreateActor<Gemini>("Gemini");
	//std::shared_ptr<Hilda> NewBoss0 = CreateActor<Hilda>(CupHeadActorOrder::Boss);
	//std::shared_ptr<Taurus> NextBoss1 = CreateActor<Taurus>(CupHeadActorOrder::Boss);
	//std::shared_ptr<Sagittarius> NextBoss2 = CreateActor<Sagittarius>(CupHeadActorOrder::Boss);
	//std::shared_ptr<Gemini> NextBoss3 = CreateActor<Gemini>(CupHeadActorOrder::Boss);
	//std::shared_ptr<Moon> NewBoss4 = CreateActor<Moon>(CupHeadActorOrder::Boss);
	//std::shared_ptr<Zeppling> NewMonster5 = CreateActor<Zeppling>(CupHeadActorOrder::Boss);
	//std::shared_ptr<HIldaMoonUFO> NewMonster6 = CreateActor<HIldaMoonUFO>(CupHeadActorOrder::Enemy);
	//std::shared_ptr<ZepplingBullet> NewMonster = CreateActor<ZepplingBullet>(CupHeadActorOrder::Enemy);
	//std::shared_ptr<HildaBergBossController> NewBoss = CreateActor<HildaBergBossController>(CupHeadActorOrder::Boss);
	std::shared_ptr<PlayerAirPlaneMode> NewPlayer7 = CreateActor<PlayerAirPlaneMode>(CupHeadActorOrder::Player);
}

void HildaBergLevel::LevelChangeEnd()
{
	
}