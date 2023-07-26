#include "PrecompileHeader.h"
#include "ResultDeathCupheadCard.h"
#include <GameEngineCore/GameEngineUIRenderer.h>

ResultDeathCupheadCard::ResultDeathCupheadCard() 
{
}

ResultDeathCupheadCard::~ResultDeathCupheadCard() 
{
}

void ResultDeathCupheadCard::Start()
{
	CupheadRender = CreateComponent<GameEngineUIRenderer>(CupHeadRendererOrder::UI);
	CupheadRender->CreateAnimation({ .AnimationName = "Idle",.SpriteName = "deathcard_ch_run",.FrameInter = 0.05f,.Loop = true,.ScaleToTexture = true });
	CupheadRender->ChangeAnimation("Idle");
}
