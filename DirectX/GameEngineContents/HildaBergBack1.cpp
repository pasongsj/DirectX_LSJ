#include "PrecompileHeader.h"
#include "HildaBergBack1.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineResource.h>

HildaBergBack1::HildaBergBack1() 
{
}

HildaBergBack1::~HildaBergBack1() 
{
}


void HildaBergBack1::Start()
{
	float4 WindowSize = GameEngineWindow::GetScreenSize();

	MainHill= CreateComponent<GameEngineSpriteRenderer>();
	MainHill->SetScaleToTexture("blimp_dark_hills.png");
	MainHill->GetTransform()->SetLocalPosition( float4(0,-WindowSize.hy()+ MainHill->GetTransform()->GetLocalScale().hy()));

	HillRange = MainHill->GetTransform()->GetLocalScale().ix();

	SubHill	= CreateComponent<GameEngineSpriteRenderer>();
	SubHill->SetScaleToTexture("blimp_dark_hills.png");
	SubHill->GetTransform()->SetLocalPosition(MainHill->GetTransform()->GetLocalPosition() + float4(static_cast<float>(HillRange)-70, 0));

	HillLimit = (HillRange - GameEngineWindow::GetScreenSize().ix()) / 2;

	GetTransform()->AddLocalPosition(float4(0, 0, 400));
}

void HildaBergBack1::Update(float _DeltaTime)
{

	GetTransform()->AddLocalPosition(float4(-100 * _DeltaTime, 0));

	if (nullptr == GetLevel()->GetMainCamera())
	{
		MsgAssert("카메라를 가져오지 못했습니다");
		return;
	}
	int CamX = (GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition()).ix();

	// MainHill과 SubHill을 교체해주는 작업
	if ((SubHill->GetTransform()->GetWorldPosition().ix() - HillRange / 2) < CamX && CamX < (SubHill->GetTransform()->GetWorldPosition().ix() + HillRange / 2)) {

		std::shared_ptr<class GameEngineSpriteRenderer> tempHill = MainHill;
		MainHill = SubHill;
		SubHill = tempHill;
		tempHill = nullptr;
	}




	float4 WorldHillPos = MainHill->GetTransform()->GetWorldPosition();

	float4 NextHillPos = MainHill->GetTransform()->GetLocalPosition();
	if (CamX - WorldHillPos.ix() > HillLimit)
	{
		NextHillPos.x += HillRange;
	}
	else if (CamX - WorldHillPos.ix() < -HillLimit) {
		NextHillPos.x -= HillRange;
	}

	if (NextHillPos != SubHill->GetTransform()->GetLocalPosition()) {
		SubHill->GetTransform()->SetLocalPosition(NextHillPos);
	}
}