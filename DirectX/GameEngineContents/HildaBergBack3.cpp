#include "PrecompileHeader.h"
#include "HildaBergBack3.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

HildaBergBack3::HildaBergBack3() 
{
}

HildaBergBack3::~HildaBergBack3() 
{
}

void HildaBergBack3::Start()
{
	float4 ScreenSize = GameEngineWindow::GetScreenSize();

	for (int i = 1; i <= 4; i++)
	{
		std::string TextureName = "blimp_large_forest_000" + std::to_string(i) + ".png";
		std::shared_ptr<GameEngineSpriteRenderer> Hill = CreateComponent< GameEngineSpriteRenderer>(CupHeadRendererOrder::BackGround);
		Hill->SetScaleToTexture(TextureName);
		float4 HillScale = Hill->GetTransform()->GetLocalScale();
		IntervalX += HillScale.x;
		if (true == LargeHill.empty())
		{
			Hill->GetTransform()->SetLocalPosition(float4(0, -ScreenSize.hy() + HillScale.hy() - 10));
			SettingX += HillScale.hx();
		}
		else
		{
			SettingX += HillScale.hx();
			Hill->GetTransform()->SetLocalPosition(float4(SettingX, -ScreenSize.hy() + HillScale.hy() - 10) /*+ HillScale.half()*/);
			SettingX += HillScale.hx();
		}
		LargeHill.push(Hill);

	}

	GetTransform()->AddLocalPosition(float4(0, 0, 200));
}

void HildaBergBack3::Update(float _DeltaTime)
{
	GetTransform()->AddLocalPosition(float4(-300 * _DeltaTime, 0));

	if (nullptr == GetLevel()->GetMainCamera())
	{
		MsgAssert("카메라를 가져오지 못했습니다");
		return;
	}
	float CamX = (GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition()).x;
	float4 ScreenSize = GameEngineWindow::GetScreenSize();


	// 서브 배경의 오른쪽 끝이 화면밖으로 나가는 경우
	std::shared_ptr<GameEngineSpriteRenderer> MainRender = LargeHill.front();
	if (MainRender->GetTransform()->GetWorldPosition().x + MainRender->GetTransform()->GetLocalScale().hx() < CamX - ScreenSize.hx())
	{
		LargeHill.pop();
		MainRender->GetTransform()->AddLocalPosition(float4(IntervalX, 0));
		LargeHill.push(MainRender);
	}

}

void HildaBergBack3::ChangeNight()
{
	float4 ScreenSize = GameEngineWindow::GetScreenSize();

	for (int i = 1; i <= 4; i++)
	{
		std::string TextureName = "blimp_large_forest_night_000" + std::to_string(i) + ".png";
		std::shared_ptr<GameEngineSpriteRenderer> Hill = CreateComponent< GameEngineSpriteRenderer>(CupHeadRendererOrder::BackGround);
		Hill->SetScaleToTexture(TextureName);
		float4 HillScale = Hill->GetTransform()->GetLocalScale();
		IntervalX += HillScale.x;
		if (true == LargeHill.empty())
		{
			Hill->GetTransform()->SetLocalPosition(float4(0, -ScreenSize.hy() + HillScale.hy() - 10));
			SettingX += HillScale.hx();
		}
		else
		{
			SettingX += HillScale.hx();
			Hill->GetTransform()->SetLocalPosition(float4(SettingX, -ScreenSize.hy() + HillScale.hy() - 10) /*+ HillScale.half()*/);
			SettingX += HillScale.hx();
		}
		LargeHill.push(Hill);

	}
}