#include "PrecompileHeader.h"
#include "ResultBoard.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "NumberRenderObject.h"

float ResultBoard::Time = 0.0f;
int ResultBoard::HPCount = 3;
int ResultBoard::ParryCount = 0;
int ResultBoard::SuperMeter = 0;
int ResultBoard::SkillLevel = 2;
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
	// 보드
	std::shared_ptr<GameEngineSpriteRenderer> BoardBG = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::UI);
	BoardBG->SetScaleToTexture("winscreen_board_letter.png");
	
	//// 구분선
	//std::shared_ptr<GameEngineSpriteRenderer> Line = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::UI);
	//Line->SetScaleToTexture("winscreen_line.png");
	//Line->GetTransform()->SetLocalPosition(float4(0, -70, -100));


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
	HPRender->GetTransform()->SetLocalPosition(float4{ 297, 31, 0 });

	ParryRender = GetLevel()->CreateActor< NumberRenderObject>(CupHeadActorOrder::UI);
	ParryRender->GetTransform()->SetLocalPosition(float4{ 297, -14, 0 });

	SuperMeterRender = GetLevel()->CreateActor< NumberRenderObject>(CupHeadActorOrder::UI);
	SuperMeterRender->GetTransform()->SetLocalPosition(float4{ 297, -58, 0 });
	SuperMeterRender->SetColorOption(NumberColor::YELLOW);

}

void ResultBoard::Update(float _DeltaTime)
{

}