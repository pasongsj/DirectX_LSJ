#include "PrecompileHeader.h"
#include "HildaBergBack.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

HildaBergBack::HildaBergBack() 
{
}

HildaBergBack::~HildaBergBack() 
{
}

void HildaBergBack::Start()
{
	MainBG = CreateComponent<GameEngineSpriteRenderer>();
	MainBG->SetOrder(-100);
	MainBG->SetScaleToTexture("blimp_sky.png");

	BGRange = MainBG->GetTransform()->GetLocalScale().ix();

	SubBG = CreateComponent<GameEngineSpriteRenderer>();
	SubBG->SetOrder(-100);
	SubBG->SetScaleToTexture("blimp_sky.png");
	SubBG->GetTransform()->SetLocalPosition(MainBG->GetTransform()->GetLocalPosition() + float4(static_cast<float>(BGRange),0));

	BGLimit = (BGRange - GameEngineWindow::GetScreenSize().ix()) / 2;



	MainHill= CreateComponent<GameEngineSpriteRenderer>();
	MainHill->SetOrder(-99);
	MainHill->SetScaleToTexture("blimp_dark_hills.png");
	MainHill->GetTransform()->SetLocalPosition( float4(0,134 - GameEngineWindow::GetScreenSize().hy()));

	HillRange = MainHill->GetTransform()->GetLocalScale().ix();

	SubHill	= CreateComponent<GameEngineSpriteRenderer>();
	SubHill->SetOrder(-99);
	SubHill->SetScaleToTexture("blimp_dark_hills.png");
	SubHill->GetTransform()->SetLocalPosition(MainHill->GetTransform()->GetLocalPosition() + float4(static_cast<float>(HillRange), 0));

	HillLimit = (HillRange - GameEngineWindow::GetScreenSize().ix()) / 2;


}

void HildaBergBack::Update(float _DeltaTime)
{
	int CamX = (GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition()).ix();

	// MainBG와 SubBG를 교체해주는 작업
	if ((SubBG->GetTransform()->GetWorldPosition().ix() - BGRange / 2) < CamX && CamX < (SubBG->GetTransform()->GetWorldPosition().ix() + BGRange / 2)) {

		std::shared_ptr<class GameEngineSpriteRenderer> tempBG = MainBG;
		MainBG = SubBG;
		SubBG = tempBG;
	}

	// MainHill과 SubHill을 교체해주는 작업
	if ((SubHill->GetTransform()->GetWorldPosition().ix() - HillRange / 2) < CamX && CamX < (SubHill->GetTransform()->GetWorldPosition().ix() + HillRange / 2)) {

		std::shared_ptr<class GameEngineSpriteRenderer> tempHill = MainHill;
		MainHill = SubHill;
		SubHill = tempHill;
	}



	float4 NextBGPos = MainBG->GetTransform()->GetWorldPosition();
	if (CamX - NextBGPos.ix() > BGLimit)
	{
		NextBGPos.x += BGRange;
	}
	else if (CamX - NextBGPos.ix() < -BGLimit) {
		NextBGPos.x -= BGRange;
	}

	if (NextBGPos != SubBG->GetTransform()->GetLocalPosition()) {
		SubBG->GetTransform()->SetLocalPosition(NextBGPos-GetTransform()->GetLocalPosition());
	}



	float4 NextHillPos = MainHill->GetTransform()->GetWorldPosition();
	if (CamX - NextHillPos.ix() > HillLimit)
	{
		NextHillPos.x += HillRange;
	}
	else if (CamX - NextHillPos.ix() < -HillLimit) {
		NextHillPos.x -= HillRange;
	}

	if (NextHillPos != SubHill->GetTransform()->GetLocalPosition()) {
		SubHill->GetTransform()->SetLocalPosition(NextHillPos - GetTransform()->GetLocalPosition());
	}
}