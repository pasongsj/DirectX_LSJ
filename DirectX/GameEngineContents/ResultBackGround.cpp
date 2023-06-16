#include "PrecompileHeader.h"
#include "ResultBackGround.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

ResultBackGround::ResultBackGround() 
{
}

ResultBackGround::~ResultBackGround() 
{
}

void ResultBackGround::Start()
{
	BGRender = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::BackGround);
	BGRender->SetScaleToTexture("winscreen_bg.png");
	GetTransform()->SetLocalPosition(float4(0, 0, 1000));
}

void ResultBackGround::Update(float _DetatTime)
{
	GetTransform()->AddLocalRotation(float4(0, 0, _DetatTime * 50.0f));
}