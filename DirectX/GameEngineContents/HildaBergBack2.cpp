#include "PrecompileHeader.h"
#include "HildaBergBack2.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

HildaBergBack2::HildaBergBack2() 
{
}

HildaBergBack2::~HildaBergBack2() 
{
}


void HildaBergBack2::Start()
{
	float4 WindowSize = GameEngineWindow::GetScreenSize();

	MainGround = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::BackGround);
	MainGround->SetScaleToTexture("blimp_main_ground_0001.png");
	MainGround->GetTransform()->SetLocalPosition(float4(0,-WindowSize.hy()+ MainGround->GetTransform()->GetLocalScale().hy()-10));

	BGRange = MainGround->GetTransform()->GetLocalScale().ix();

	SubGround = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::BackGround);
	SubGround->SetScaleToTexture("blimp_main_ground_0002.png");
	SubGround->GetTransform()->SetLocalPosition(float4(static_cast<float>(BGRange), -WindowSize.hy() + SubGround->GetTransform()->GetLocalScale().hy()-10));

	BGLimit = (BGRange - GameEngineWindow::GetScreenSize().ix()) / 2;

	GetTransform()->AddLocalPosition(float4(0, 0, 300));

}

void HildaBergBack2::Update(float _DeltaTime)
{
	GetTransform()->AddLocalPosition(float4(-200 * _DeltaTime, 0));


	if (nullptr == GetLevel()->GetMainCamera())
	{
		MsgAssert("ī�޶� �������� ���߽��ϴ�");
		return;
	}
	float CamX = (GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition()).x;
	float4 ScreenSize = GameEngineWindow::GetScreenSize();

	//���� ����� ������ ���� ȭ�� ������ ���� ���
	if (MainGround->GetTransform()->GetWorldPosition().x + MainGround->GetTransform()->GetLocalScale().hx() < CamX + ScreenSize.hx())
	{
		// ���ι��� �������� ��ü���ش�.
		std::shared_ptr<class GameEngineSpriteRenderer> tempBG = MainGround;
		MainGround = SubGround;
		SubGround = tempBG;
		tempBG = nullptr;
	}

	// ���� ����� ������ ���� ȭ������� ������ ���
	else if (SubGround->GetTransform()->GetWorldPosition().x + SubGround->GetTransform()->GetLocalScale().hx() < CamX - ScreenSize.hx())
	{
		SubGround->GetTransform()->AddLocalPosition(float4(MainGround->GetTransform()->GetLocalScale().x + SubGround->GetTransform()->GetLocalScale().x, 0));
	}

}