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