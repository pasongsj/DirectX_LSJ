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
	MainHill->GetTransform()->SetLocalPosition( float4(0,-WindowSize.hy()+ MainHill->GetTransform()->GetLocalScale().hy() - 30));

	SubHill	= CreateComponent<GameEngineSpriteRenderer>();
	SubHill->SetScaleToTexture("blimp_dark_hills.png");
	SubHill->GetTransform()->SetLocalPosition(float4(MainHill->GetTransform()->GetLocalScale().x , MainHill->GetTransform()->GetLocalPosition().y));


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
	float CamX = (GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition()).x;
	float4 ScreenSize = GameEngineWindow::GetScreenSize();

	//메인 배경의 오른쪽 끝이 화면 안으로 들어가는 경우
	if (MainHill->GetTransform()->GetWorldPosition().x + MainHill->GetTransform()->GetLocalScale().hx() < CamX + ScreenSize.hx())
	{
		// 메인배경과 서브배경을 교체해준다.
		std::shared_ptr<class GameEngineSpriteRenderer> tempBG = MainHill;
		MainHill = SubHill;
		SubHill = tempBG;
		tempBG = nullptr;
	}

	// 서브 배경의 오른쪽 끝이 화면밖으로 나가는 경우
	else if (SubHill->GetTransform()->GetWorldPosition().x + SubHill->GetTransform()->GetLocalScale().hx() < CamX - ScreenSize.hx())
	{
		SubHill->GetTransform()->AddLocalPosition(float4(MainHill->GetTransform()->GetLocalScale().x + SubHill->GetTransform()->GetLocalScale().x, 0));
	}

	
}