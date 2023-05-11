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

void HildaHA::MakeSprite()
{
	if (nullptr == GameEngineSprite::Find("Hilda_Ha"))
	{

		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("stage1\\Boss\\Hilda\\HildaBerg\\Normal");


		GameEngineSprite::LoadFolder("Hilda_Ha", NewDir.GetPlusFileName("Laugh\\Ha").GetFullPath());

	}
}

void HildaHA::Start()
{
	MakeSprite();
	HaRender = CreateComponent<GameEngineSpriteRenderer>();
	HaRender->CreateAnimation({.AnimationName = "Ha", .SpriteName = "Hilda_Ha",  .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	
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