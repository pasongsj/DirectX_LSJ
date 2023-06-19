#include "PrecompileHeader.h"
#include "HildaBergBack5.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
HildaBergBack5::HildaBergBack5() 
{
}

HildaBergBack5::~HildaBergBack5() 
{
}


void HildaBergBack5::Start()
{
	float4 ScreenSize = GameEngineWindow::GetScreenSize();

	for (int i = 1; i <= 3; i++)
	{
		std::string TextureName = "blimp_clouds_000" + std::to_string(i) + ".png";
		std::shared_ptr<GameEngineSpriteRenderer> Cloud = CreateComponent< GameEngineSpriteRenderer>(CupHeadRendererOrder::BackGround);
		Cloud->SetScaleToTexture(TextureName);
		float4 CloudScale = Cloud->GetTransform()->GetLocalScale();

		if (true == Clouds.empty())
		{
			Cloud->GetTransform()->SetLocalPosition(float4(0, ScreenSize.hy() - CloudScale.hy() - 10));
			NextStartXPos += CloudScale.hx();
			//SettingX += CloudScale.hx();
		}
		else
		{
			NextStartXPos += CloudScale.hx();
			Cloud->GetTransform()->SetLocalPosition(float4(NextStartXPos, ScreenSize.hy() - CloudScale.hy() - 10) /*+ HillScale.half()*/);
			NextStartXPos += CloudScale.hx();
		}
		Clouds.push(Cloud);

	}

	GetTransform()->AddLocalPosition(float4(0, 0, 700));
	BackGroundMoveSpeed = 50.0f;
}

void HildaBergBack5::Update(float _DeltaTime)
{
	GetTransform()->AddLocalPosition(float4(-BackGroundMoveSpeed * _DeltaTime, 0));

	if (nullptr == GetLevel()->GetMainCamera())
	{
		MsgAssert("카메라를 가져오지 못했습니다");
		return;
	}
	float CamX = (GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition()).x;
	float4 ScreenSize = GameEngineWindow::GetScreenSize();


	// 서브 배경의 오른쪽 끝이 화면밖으로 나가는 경우
	std::shared_ptr<GameEngineSpriteRenderer> MainRender = Clouds.front();
	if (MainRender->GetTransform()->GetWorldPosition().x + MainRender->GetTransform()->GetLocalScale().hx() < CamX - ScreenSize.hx())
	{
		Clouds.pop();
		MainRender->GetTransform()->AddLocalPosition(float4(NextStartXPos, 0));
		Clouds.push(MainRender);
	}
}

void HildaBergBack5::ChangeNight()
{
}