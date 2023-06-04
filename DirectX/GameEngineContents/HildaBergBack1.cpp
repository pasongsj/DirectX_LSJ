#include "PrecompileHeader.h"
#include "HildaBergBack1.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineResource.h>

HildaBergBack1::HildaBergBack1() 
{
}

HildaBergBack1::~HildaBergBack1() 
{
}


void HildaBergBack1::Start()
{
	float4 WindowSize = GameEngineWindow::GetScreenSize();

	MainBack= CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::BackGround);
	MainBack->SetScaleToTexture("blimp_dark_hills.png");
	MainBack->GetTransform()->SetLocalPosition( float4(0,-WindowSize.hy()+ MainBack->GetTransform()->GetLocalScale().hy() - 30));

	SubBack = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::BackGround);
	SubBack->SetScaleToTexture("blimp_dark_hills.png");
	SubBack->GetTransform()->SetLocalPosition(float4(MainBack->GetTransform()->GetLocalScale().x , MainBack->GetTransform()->GetLocalPosition().y));


	GetTransform()->AddLocalPosition(float4(0, 0, 400));

	Interval = 0.0f;
	BackGroundMoveSpeed = 100.0f;
}

void HildaBergBack1::ChangeNight()
{
	MainBack->SetScaleToTexture("blimp_dark_hills_night.png");
	SubBack->SetScaleToTexture("blimp_dark_hills_night.png");
}