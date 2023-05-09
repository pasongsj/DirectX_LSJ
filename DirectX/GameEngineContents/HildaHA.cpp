#include "PrecompileHeader.h"
#include "HildaHA.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineWindow.h>

HildaHA::HildaHA() 
{
}

HildaHA::~HildaHA() 
{
}

void HildaHA::Start()
{
	HaRender = CreateComponent<GameEngineSpriteRenderer>();
	HaRender->CreateAnimation({.AnimationName = "Ha", .TextureName = "blimp_ha_00", .Start = 1, .End = 13, .InterTime = 0.05f, .Loop = false});
	HaRender->ChangeAnimation("Ha");
}

void HildaHA::Update(float _DeltaTime)
{
	GetTransform()->AddLocalPosition(float4(-800 * _DeltaTime, 0));


	float4 CamPos = GetLevel()->GetMainCamera()->GetTransform()->GetWorldPosition();
	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	if (GetTransform()->GetWorldPosition().x < CamPos.x - ScreenSize.hx())
	{
		Death();
	}

}