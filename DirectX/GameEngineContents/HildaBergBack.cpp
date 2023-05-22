#include "PrecompileHeader.h"
#include "HildaBergBack.h"
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include<GameEngineCore/GameEngineSpriteRenderer.h>

HildaBergBack::HildaBergBack() 
{
}

HildaBergBack::~HildaBergBack() 
{
}




void HildaBergBack::Update(float _DeltaTime)
{
	GetTransform()->AddLocalPosition(float4(-BackGroundMoveSpeed * _DeltaTime, 0));
	if (nullptr == MainBack || nullptr == SubBack)
	{
		MsgAssert("��� �ؽ��ĸ� ���������� �ʾҽ��ϴ�");
	}

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
	if (SubBack->GetTransform()->GetWorldPosition().x + SubBack->GetTransform()->GetLocalScale().hx() < CamX - ScreenSize.hx())
	{
		SubBack->GetTransform()->AddLocalPosition(float4(MainBack->GetTransform()->GetLocalScale().x + SubBack->GetTransform()->GetLocalScale().x + Interval, 0));
	}


}