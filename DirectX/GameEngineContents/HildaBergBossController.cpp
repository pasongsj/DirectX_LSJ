#include "PrecompileHeader.h"
#include "HildaBergBossController.h"
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include "Hilda.h"
#include "Zeppling.h"
#include "Taurus.h"
#include "Sagittarius.h"
#include "Gemini.h"
#include "Moon.h"

HildaBergBossController::HildaBergBossController() 
{
}

HildaBergBossController::~HildaBergBossController() 
{
	//Boss = nullptr;
}

void HildaBergBossController::Start()
{
	if (false == GameEngineInput::IsKey("NextBoss"))
	{
		GameEngineInput::CreateKey("NextBoss", VK_F2);
	}
}

void HildaBergBossController::Update(float _DeltaTime) 
{
	//if (nullptr == Boss || true == Boss->IsDeath())
	//{
	//	++Phase;
	//	switch (Phase)
	//	{
	//	case 1:
	//	{
	//		Boss = GetLevel()->CreateActor<Hilda>(CupHeadActorOrder::Boss);
	//		//std::shared_ptr<Hilda> HildaTmp = DynamicThis<Hilda>();
	//		//HildaTmp->SetHildaPhase(1);
	//		break;
	//	}
	//	case 2:
	//	{
	//		Boss = GetLevel()->CreateActor<Taurus>(CupHeadActorOrder::Boss);
	//		break;
	//	}
	//	case 3:
	//	{
	//		Boss = GetLevel()->CreateActor<Hilda>(CupHeadActorOrder::Boss);
	//		//std::shared_ptr<Hilda> HildaTmp = DynamicThis<Hilda>();
	//		//HildaTmp->SetHildaPhase(3);
	//		break;
	//	}
	//	case 4:
	//	{
	//		Boss = GetLevel()->CreateActor<Gemini>(CupHeadActorOrder::Boss);/*
	//		int RandomNum = GameEngineRandom::MainRandom.RandomInt(0, 9);
	//		if (1 == (RandomNum & 1))
	//		{
	//			Boss = GetLevel()->CreateActor<Sagittarius>(CupHeadActorOrder::Boss);
	//		}
	//		else
	//		{
	//		}*/
	//		break;
	//	}
	//	case 5:
	//	{
	//		Boss = GetLevel()->CreateActor<Hilda>(CupHeadActorOrder::Boss);
	//		//std::shared_ptr<Hilda> HildaTmp = DynamicThis<Hilda>();
	//		//HildaTmp->SetHildaPhase(5);
	//		break;
	//	}
	//	case 6:
	//	{
	//		Boss = GetLevel()->CreateActor<Moon>(CupHeadActorOrder::Boss);
	//		break;
	//	}
	//	default:
	//		Death();
	//		break;
	//	}
	//}

	//if (true == GameEngineInput::IsDown("NextBoss"))
	//{
	//	Boss->BossDeath();
	//}
}