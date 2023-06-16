#include "PrecompileHeader.h"
#include "ResultBoard.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
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
	BoardBG->SetScaleToTexture("winscreen_board.png");
	
	// 구분선
	std::shared_ptr<GameEngineSpriteRenderer> Line = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::UI);
	Line->SetScaleToTexture("winscreen_line.png");
	Line->GetTransform()->SetLocalPosition(float4(0, -70, -100));


	RankStars.reserve(3);
	float4 StarPos = float4(110, -30, -100);
	for (int i = 0; i < 3;i++)
	{
		std::shared_ptr<GameEngineSpriteRenderer> StarRender = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::UI);
		StarRender->SetScaleToTexture("winscreen_grey_star_a.png");
		StarRender->GetTransform()->SetLocalPosition(StarPos);
		RankStars.push_back(StarRender);
		StarPos.x += 30;
	}
	GetTransform()->SetLocalPosition(float4(150, -70, 900));
}

void ResultBoard::Update(float _DeltaTime)
{

}