#include "PrecompileHeader.h"
#include "WallyFore.h"
#include<GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>

WallyFore::WallyFore() 
{
}

WallyFore::~WallyFore() 
{
}


void WallyFore::Setting(const std::string_view& _TextureName, float _ZPos, float _InterVal, float _BackGroundMoveSpeed, WallyForeGroundSort _Sort)

{
	float4 WindowSize = GameEngineWindow::GetScreenSize();
	MainBack = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::ForeGround);
	MainBack->SetScaleToTexture(_TextureName);

	SubBack = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::ForeGround);
	SubBack->SetScaleToTexture(_TextureName);

	float YPos = 0.0f;
	if (WallyForeGroundSort::TOP == _Sort)
	{
		YPos = WindowSize.hy() - MainBack->GetTransform()->GetLocalScale().hy() + 30;
	}
	else if (WallyForeGroundSort::BOT == _Sort)
	{
		YPos = -(WindowSize.hy() - MainBack->GetTransform()->GetLocalScale().hy() + 30);

	}

	MainBack->GetTransform()->SetLocalPosition(float4(0, YPos));
	SubBack->GetTransform()->SetLocalPosition(float4(MainBack->GetTransform()->GetLocalScale().x, YPos));


	GetTransform()->AddLocalPosition(float4(0, 0, _ZPos));

	Interval = _InterVal;
	BackGroundMoveSpeed = _BackGroundMoveSpeed;
}



void WallyFore::Update(float _DeltaTime)
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