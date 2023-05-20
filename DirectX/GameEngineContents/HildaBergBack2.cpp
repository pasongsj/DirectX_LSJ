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
	MainGround->GetTransform()->SetLocalPosition(float4(0,-WindowSize.hy()+ MainGround->GetTransform()->GetLocalScale().hy()));

	BGRange = MainGround->GetTransform()->GetLocalScale().ix();

	SubGround = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::BackGround);
	SubGround->SetScaleToTexture("blimp_main_ground_0002.png");
	SubGround->GetTransform()->SetLocalPosition(float4(static_cast<float>(BGRange), -WindowSize.hy() + SubGround->GetTransform()->GetLocalScale().hy()));

	BGLimit = (BGRange - GameEngineWindow::GetScreenSize().ix()) / 2;

	GetTransform()->AddLocalPosition(float4(0, 0, 300));

}

void HildaBergBack2::Update(float _DeltaTime)
{
	GetTransform()->AddLocalPosition(float4(-200 * _DeltaTime, 0));

	if (nullptr == GetLevel()->GetMainCamera())
	{
		MsgAssert("카메라를 가져오지 못했습니다");
		return;
	}
	int CamX = (GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition()).ix();

	// MainBG와 SubBG를 교체해주는 작업
	if ((SubGround->GetTransform()->GetWorldPosition().ix() - BGRange / 2) < CamX && CamX < (SubGround->GetTransform()->GetWorldPosition().ix() + BGRange / 2)) {

		std::shared_ptr<class GameEngineSpriteRenderer> tempBG = MainGround;
		MainGround = SubGround;
		SubGround = tempBG;
		tempBG = nullptr;
	}

	float4 WorldBGPos = MainGround->GetTransform()->GetWorldPosition();

	float4 NextBGPos = MainGround->GetTransform()->GetLocalPosition();

	if (CamX - WorldBGPos.ix() > BGLimit)
	{
		NextBGPos.x += BGRange;
	}
	else if (CamX - WorldBGPos.ix() < -BGLimit) {
		NextBGPos.x -= BGRange;
	}

	if (NextBGPos.x != SubGround->GetTransform()->GetLocalPosition().x) {
		SubGround->GetTransform()->SetLocalPosition(NextBGPos);
	}

}