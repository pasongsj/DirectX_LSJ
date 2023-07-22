#include "PrecompileHeader.h"
#include "YouDieUI.h"
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
YouDieUI::YouDieUI() 
{
}

YouDieUI::~YouDieUI() 
{
}


void YouDieUI::Start()
{
	std::shared_ptr<GameEngineCamera> Camera = GetLevel()->GetCamera(100);
	Camera->SetProjectionType(CameraType::Orthogonal);
	Camera->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });

	//// sprite
	//if (nullptr == GameEngineSprite::Find("Text_YouDied"))
	//{
	//	GameEngineDirectory NewDir;
	//	NewDir.MoveParentToDirectory("ContentResources");
	//	NewDir.Move("ContentResources\\Texture\\TextUI");


	//	GameEngineSprite::LoadFolder("Text_YouDied", NewDir.GetPlusFileName("Text_YouDied").GetFullPath().c_str());
	//}
	YouDieRender = CreateComponent<GameEngineUIRenderer>(CupHeadRendererOrder::UI);
	YouDieRender->CreateAnimation({ .AnimationName = "Idle",  .SpriteName = "Text_YouDied", .FrameInter = 0.05f, .Loop = false , .ScaleToTexture = true });
	YouDieRender->ChangeAnimation("Idle");
}

void YouDieUI::Update(float _Delta)
{
	if (true == YouDieRender->IsAnimationEnd())
	{
		Death();
	}
}
