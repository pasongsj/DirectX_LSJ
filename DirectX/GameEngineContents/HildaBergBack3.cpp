#include "PrecompileHeader.h"
#include "HildaBergBack3.h"
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

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
		std::shared_ptr<GameEngineSpriteRenderer> Hill = CreateComponent< GameEngineSpriteRenderer>();
		Hill->SetScaleToTexture(TextureName);
		if (true == LargeHill.empty())
		{
			float4 HillScale = Hill->GetTransform()->GetLocalScale();
			Hill->GetTransform()->SetLocalPosition(float4(0, -ScreenSize.hy() + HillScale.hy()));
			LastX = HillScale.hix();
		}
		else
		{
			float4 HillScale = Hill->GetTransform()->GetLocalScale();
			Hill->GetTransform()->SetLocalPosition(float4(static_cast<float>(LastX), -ScreenSize.hy()) + HillScale.half());
			LastX += HillScale.ix();
		}
		LargeHill.push(Hill);

	}
	TextureIndex = 0;
	GetTransform()->AddLocalPosition(float4(0, 0, 200));
}

void HildaBergBack3::Update(float _DeltaTime)
{
	GetTransform()->AddLocalPosition(float4(-300 * _DeltaTime, 0));
}

void HildaBergBack3::SetNextBackGround()
{

}

//void HildaBergBack0::Start()
//{
//	MainBack = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::BackGround);
//	MainBack->SetScaleToTexture("blimp_sky.png");
//
//	BGRange = MainBack->GetTransform()->GetLocalScale().ix();
//
//	SubBack = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::BackGround);
//	SubBack->SetScaleToTexture("blimp_sky.png");
//	SubBack->GetTransform()->SetLocalPosition(MainBack->GetTransform()->GetLocalPosition() + float4(static_cast<float>(BGRange), 0));
//
//	BGLimit = (BGRange - GameEngineWindow::GetScreenSize().ix()) / 2;
//
//	GetTransform()->AddLocalPosition(float4(0, 0, 500));
//
//}
//
//void HildaBergBack0::Update(float _DeltaTime)
//{
//	GetTransform()->AddLocalPosition(float4(-50 * _DeltaTime, 0));
//
//	if (nullptr == GetLevel()->GetMainCamera())
//	{
//		MsgAssert("카메라를 가져오지 못했습니다");
//		return;
//	}
//	int CamX = (GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition()).ix();
//
//	// MainBG와 SubBG를 교체해주는 작업
//	if ((SubBack->GetTransform()->GetWorldPosition().ix() - BGRange / 2) < CamX && CamX < (SubBack->GetTransform()->GetWorldPosition().ix() + BGRange / 2)) {
//
//		std::shared_ptr<class GameEngineSpriteRenderer> tempBG = MainBack;
//		MainBack = SubBack;
//		SubBack = tempBG;
//		tempBG = nullptr;
//	}
//
//	float4 WorldBGPos = MainBack->GetTransform()->GetWorldPosition();
//
//	float4 NextBGPos = MainBack->GetTransform()->GetLocalPosition();
//
//	if (CamX - WorldBGPos.ix() > BGLimit)
//	{
//		NextBGPos.x += BGRange;
//	}
//	else if (CamX - WorldBGPos.ix() < -BGLimit) {
//		NextBGPos.x -= BGRange;
//	}
//
//	if (NextBGPos != SubBack->GetTransform()->GetLocalPosition()) {
//		SubBack->GetTransform()->SetLocalPosition(NextBGPos);
//	}
//
//}