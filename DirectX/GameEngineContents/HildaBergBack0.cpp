#include "PrecompileHeader.h"
#include "HildaBergBack0.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

HildaBergBack0::HildaBergBack0() 
{
}

HildaBergBack0::~HildaBergBack0() 
{
}

void HildaBergBack0::Start()
{

	MainBack = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::BackGround);
	MainBack->SetScaleToTexture("blimp_sky.png");


	SubBack = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::BackGround);
	SubBack->SetScaleToTexture("blimp_sky.png");
	SubBack->GetTransform()->SetLocalPosition(float4(MainBack->GetTransform()->GetLocalScale().x, 0));


	GetTransform()->SetLocalPosition(float4(0, 0, 500));

}

void HildaBergBack0::Update(float _DeltaTime)
{
	GetTransform()->AddLocalPosition(float4(-50 * _DeltaTime, 0));

	if (nullptr == GetLevel()->GetMainCamera())
	{
		MsgAssert("ī�޶� �������� ���߽��ϴ�");
		return;
	}
	float CamX = (GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition()).x;
	float4 ScreenSize = GameEngineWindow::GetScreenSize();

	//���� ����� ������ ���� ȭ�� ������ ���� ���
	if (MainBack->GetTransform()->GetWorldPosition().x + MainBack->GetTransform()->GetLocalScale().hx() < CamX + ScreenSize.hx())
	{
		// ���ι��� �������� ��ü���ش�.
		std::shared_ptr<class GameEngineSpriteRenderer> tempBG = MainBack;
		MainBack = SubBack;
		SubBack = tempBG;
		tempBG = nullptr;
	}

	// ���� ����� ������ ���� ȭ������� ������ ���
	else if (SubBack->GetTransform()->GetWorldPosition().x + SubBack->GetTransform()->GetLocalScale().hx() < CamX - ScreenSize.hx())
	{
		SubBack->GetTransform()->AddLocalPosition(float4(MainBack->GetTransform()->GetLocalScale().x + SubBack->GetTransform()->GetLocalScale().x, 0));
	}


}