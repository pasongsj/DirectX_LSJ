#include "PrecompileHeader.h"
#include "ResultBoard.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "NumberRenderObject.h"

float ResultBoard::ResultTime = 200.0f;
int ResultBoard::ResultHPCount = 3;
int ResultBoard::ResultParryCount = 3;
int ResultBoard::ResultSuperMeter = 3;
int ResultBoard::ResultSkillLevel = 2;
std::string_view ResultBoard::Rank = "RankB";

ResultBoard::ResultBoard() 
{
}

ResultBoard::~ResultBoard() 
{
}

void ResultBoard::MakeSprite()
{

}


void ResultBoard::Start()
{
	// º¸µå
	std::shared_ptr<GameEngineSpriteRenderer> BoardBG = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::UI);
	BoardBG->SetScaleToTexture("winscreen_board_letter.png");
	

	RankStars.reserve(3);
	float4 StarPos = float4(115, -30, -100);
	for (int i = 0; i < 3;i++)
	{
		std::shared_ptr<GameEngineSpriteRenderer> StarRender = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::UI);
		StarRender->SetScaleToTexture("winscreen_grey_star_a.png");
		StarRender->GetTransform()->SetLocalPosition(StarPos);
		RankStars.push_back(StarRender);
		StarPos.x += 30;
	}
	GetTransform()->SetLocalPosition(float4(150, -70, 900));

	TimeMinRender = GetLevel()->CreateActor< NumberRenderObject>(CupHeadActorOrder::UI);
	TimeMinRender->GetTransform()->SetLocalPosition(float4{ 275, 75, 0 });
	TimeMinRender->SetValue("00");

	TimeSecRender = GetLevel()->CreateActor< NumberRenderObject>(CupHeadActorOrder::UI);
	TimeSecRender->GetTransform()->SetLocalPosition(float4{ 317, 75, 0 });
	TimeSecRender->SetValue("00");

	HPRender = GetLevel()->CreateActor< NumberRenderObject>(CupHeadActorOrder::UI);
	HPRender->GetTransform()->SetLocalPosition(float4{ 297, 30, 0 });

	ParryRender = GetLevel()->CreateActor< NumberRenderObject>(CupHeadActorOrder::UI);
	ParryRender->GetTransform()->SetLocalPosition(float4{ 297, -14, 0 });

	SuperMeterRender = GetLevel()->CreateActor< NumberRenderObject>(CupHeadActorOrder::UI);
	SuperMeterRender->GetTransform()->SetLocalPosition(float4{ 297, -58, 0 });
	SuperMeterRender->SetColorOption(NumberColor::YELLOW);

}

void ResultBoard::Update(float _DeltaTime)
{
	if (CurLocalTime < ResultTime)
	{
		CurLocalTime += _DeltaTime*100;
		int Min = static_cast<int>(CurLocalTime) / 60;
		int Sec = static_cast<int>(CurLocalTime) % 60;
		if (Min < 10)
		{
			TimeMinRender->SetValue("0" + std::to_string(Min));
		}
		else
		{
		TimeMinRender->SetValue(std::to_string(Min));
		}
		if (Sec < 10)
		{
			TimeSecRender->SetValue("0" + std::to_string(Sec));
		}
		else
		{
			TimeSecRender->SetValue(std::to_string(Sec));
		}
		return;

	}
	else if (ChangeInterval > 0)
	{
		ChangeInterval -= _DeltaTime;
		return;
	}
	if(CurHPCount < ResultHPCount)
	{
		HPRender->SetValue(std::to_string(++CurHPCount));
		ChangeInterval = 0.3f;
		return;
	}
	else if (CurParryCount < ResultParryCount)
	{
		ParryRender->SetValue(std::to_string(++CurParryCount));
		ChangeInterval = 0.3f;
		return;
	}
	else if (CurSuperMeter < ResultSuperMeter)
	{
		SuperMeterRender->SetValue(std::to_string(++CurSuperMeter));
		ChangeInterval = 0.3f;
		return;
	}
	else if (StarIndex < 3)
	{
		RankStars[StarIndex++]->SetScaleToTexture("winscreen_main_star_a.png");
		ChangeInterval = 0.3f;
		return;
	}
}