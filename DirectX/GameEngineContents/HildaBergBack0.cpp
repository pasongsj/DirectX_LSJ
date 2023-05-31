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

	MainBack = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::BackGround);
	MainBack->SetScaleToTexture("blimp_sky.png");


	SubBack = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::BackGround);
	SubBack->SetScaleToTexture("blimp_sky.png");
	SubBack->GetTransform()->SetLocalPosition(float4(MainBack->GetTransform()->GetLocalScale().x, 0));


	GetTransform()->SetLocalPosition(float4(0, 0, 500));

	Interval = 0.0f;
	BackGroundMoveSpeed = 50.0f;

}

void HildaBergBack0::ChangeNight()
{
	MainBack->SetScaleToTexture("blimp_sky_night.png");
	SubBack->SetScaleToTexture("blimp_sky_night.png");
}