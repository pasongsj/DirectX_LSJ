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
		MsgAssert("ī�޶� �������� ���߽��ϴ�");
		return;
	}
	float CamX = (GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition()).x;
	float4 ScreenSize = GameEngineWindow::GetScreenSize();

	//���� ����� ������ ���� ȭ�� ������ ���� ���
	if (MainHill->GetTransform()->GetWorldPosition().x + MainHill->GetTransform()->GetLocalScale().hx() < CamX + ScreenSize.hx())
	{
		// ���ι��� �������� ��ü���ش�.
		std::shared_ptr<class GameEngineSpriteRenderer> tempBG = MainHill;
		MainHill = SubHill;
		SubHill = tempBG;
		tempBG = nullptr;
	}

	// ���� ����� ������ ���� ȭ������� ������ ���
	else if (SubHill->GetTransform()->GetWorldPosition().x + SubHill->GetTransform()->GetLocalScale().hx() < CamX - ScreenSize.hx())
	{
		SubHill->GetTransform()->AddLocalPosition(float4(MainHill->GetTransform()->GetLocalScale().x + SubHill->GetTransform()->GetLocalScale().x, 0));
	}

	
}