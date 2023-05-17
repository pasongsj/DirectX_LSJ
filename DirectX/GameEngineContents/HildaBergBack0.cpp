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
	MainBack = CreateComponent<GameEngineSpriteRenderer>();
	MainBack->SetScaleToTexture("blimp_sky.png");

	BGRange = MainBack->GetTransform()->GetLocalScale().ix();

	SubBack = CreateComponent<GameEngineSpriteRenderer>();
	SubBack->SetScaleToTexture("blimp_sky.png");
	SubBack->GetTransform()->SetLocalPosition(MainBack->GetTransform()->GetLocalPosition() + float4(static_cast<float>(BGRange), 0));

	BGLimit = (BGRange - GameEngineWindow::GetScreenSize().ix()) / 2;

	GetTransform()->AddLocalPosition(float4(0, 0, 100));

}

void HildaBergBack0::Update(float _DeltaTime)
{
	GetTransform()->AddLocalPosition(float4(-50 * _DeltaTime, 0));

	if (nullptr == GetLevel()->GetMainCamera())
	{
		MsgAssert("카메라를 가져오지 못했습니다");
		return;
	}
	int CamX = (GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition()).ix();

	// MainBG와 SubBG를 교체해주는 작업
	if ((SubBack->GetTransform()->GetWorldPosition().ix() - BGRange / 2) < CamX && CamX < (SubBack->GetTransform()->GetWorldPosition().ix() + BGRange / 2)) {

		std::shared_ptr<class GameEngineSpriteRenderer> tempBG = MainBack;
		MainBack = SubBack;
		SubBack = tempBG;
		tempBG = nullptr;
	}

	float4 WorldBGPos = MainBack->GetTransform()->GetWorldPosition();

	float4 NextBGPos = MainBack->GetTransform()->GetLocalPosition();

	if (CamX - WorldBGPos.ix() > BGLimit)
	{
		NextBGPos.x += BGRange;
	}
	else if (CamX - WorldBGPos.ix() < -BGLimit) {
		NextBGPos.x -= BGRange;
	}

	if (NextBGPos != SubBack->GetTransform()->GetLocalPosition()) {
		SubBack->GetTransform()->SetLocalPosition(NextBGPos);
	}

}