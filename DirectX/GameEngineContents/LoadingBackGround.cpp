#include "PrecompileHeader.h"
#include "LoadingBackGround.h"
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

LoadingBackGround::LoadingBackGround() 
{
}

LoadingBackGround::~LoadingBackGround() 
{
}

void LoadingBackGround::Start()
{
	if (nullptr == GameEngineSprite::Find("LoadingHourGlass"))
	{

		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources\\Texture\\Loading");
		GameEngineTexture::Load(NewDir.GetPlusFileName("BlackBG.png").GetFullPath());

		GameEngineSprite::LoadFolder("LoadingHourGlass", NewDir.GetPlusFileName("HourGlass").GetFullPath());
	}

	std::shared_ptr<GameEngineSpriteRenderer> BlackBG = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::BackGround);
	BlackBG->SetScaleToTexture("BlackBG.png");

	std::shared_ptr<GameEngineSpriteRenderer> HourGlassObject = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::UI);
	HourGlassObject->CreateAnimation({ .AnimationName = "Loading", .SpriteName = "LoadingHourGlass", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
	HourGlassObject->ChangeAnimation("Loading");
	HourGlassObject->GetTransform()->SetLocalPosition(float4(500, -150));
}
void LoadingBackGround::Update(float _DeltaTime)
{

}