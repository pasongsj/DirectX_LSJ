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
	if (nullptr == Boss || true == Boss->IsDeath())
	{
		++Phase;
		switch (Phase)
		{
		case 1:
		{
			Boss = GetLevel()->CreateActor<Hilda>();
			break;
		}
		case 2:
		{
			Boss = GetLevel()->CreateActor<Taurus>();
			break;
		}
		case 3:
		{
			Boss = GetLevel()->CreateActor<Hilda>();
			break;
		}
		case 4:
		{
			int RandomNum = GameEngineRandom::MainRandom.RandomInt(0, 9);
			if (1 == (RandomNum & 1))
			{
				Boss = GetLevel()->CreateActor<Sagittarius>();
			}
			else
			{
				Boss = GetLevel()->CreateActor<Gemini>();
			}
			break;
		}
		case 5:
		{
			Boss = GetLevel()->CreateActor<Hilda>();
			break;
		}
		case 6:
		{
			Boss = GetLevel()->CreateActor<Moon>();
			break;
		}
		default:
			break;
		}
	}

	if (true == GameEngineInput::IsDown("NextBoss"))
	{
		Boss->Death();
	}
}