#include "PrecompileHeader.h"
#include "WallyBack.h"
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include<GameEngineCore/GameEngineSpriteRenderer.h>

WallyBack::WallyBack()
{
}

WallyBack::~WallyBack()
{
}

void WallyBack::Setting(const std::string_view& _TextureName, float _ZPos, float _InterVal, float _BackGroundMoveSpeed, WallyBackGroundSort _Sort)

{
	float4 WindowSize = GameEngineWindow::GetScreenSize();
	MainBack = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::BackGround);
	MainBack->SetScaleToTexture(_TextureName);

	SubBack = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::BackGround);
	SubBack->SetScaleToTexture(_TextureName);

	float YPos = 0.0f;
	if (WallyBackGroundSort::TOP == _Sort)
	{
		YPos = WindowSize.hy() - MainBack->GetTransform()->GetLocalScale().hy() + 30;
	}
	else if (WallyBackGroundSort::BOT == _Sort)
	{
		YPos = -(WindowSize.hy() - MainBack->GetTransform()->GetLocalScale().hy() + 30);

	}

	MainBack->GetTransform()->SetLocalPosition(float4(0, YPos));
	SubBack->GetTransform()->SetLocalPosition(float4(MainBack->GetTransform()->GetLocalScale().x, YPos));


	GetTransform()->AddLocalPosition(float4(0, 0, _ZPos));

	Interval = _InterVal;
	BackGroundMoveSpeed = _BackGroundMoveSpeed;
}



void WallyBack::Update(float _DeltaTime)
{
	GetTransform()->AddLocalPosition(float4(-BackGroundMoveSpeed * _DeltaTime, 0));
	if (nullptr == MainBack || nullptr == SubBack)
	{
		MsgAssert("배경 텍스쳐를 설정해주지 않았습니다");
	}

	if (nullptr == GetLevel()->GetMainCamera())
	{
		MsgAssert("카메라를 가져오지 못했습니다");
		return;
	}
	float CamX = (GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition()).x;
	float4 ScreenSize = GameEngineWindow::GetScreenSize();

	//메인 배경의 오른쪽 끝이 화면 안으로 들어가는 경우
	if (MainBack->GetTransform()->GetWorldPosition().x + MainBack->GetTransform()->GetLocalScale().hx() < CamX + ScreenSize.hx())
	{
		// 메인배경과 서브배경을 교체해준다.
		std::shared_ptr<class GameEngineSpriteRenderer> tempBG = MainBack;
		MainBack = SubBack;
		SubBack = tempBG;
		tempBG = nullptr;
	}

	// 서브 배경의 오른쪽 끝이 화면밖으로 나가는 경우
	if (SubBack->GetTransform()->GetWorldPosition().x + SubBack->GetTransform()->GetLocalScale().hx() < CamX - ScreenSize.hx())
	{
		SubBack->GetTransform()->AddLocalPosition(float4(MainBack->GetTransform()->GetLocalScale().x + SubBack->GetTransform()->GetLocalScale().x + Interval, 0));
	}


}