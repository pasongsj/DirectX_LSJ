#include "PrecompileHeader.h"
#include "GetReadyUI.h"

#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineUIRenderer.h>


GetReadyUI::GetReadyUI() 
{
}

GetReadyUI::~GetReadyUI() 
{
}

void GetReadyUI::Start()
{
	//std::shared_ptr<GameEngineCamera> Camera = GetLevel()->GetCamera(100);
	//Camera->SetProjectionType(CameraType::Orthogonal);
	//Camera->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });

	//// sprite
	//if (nullptr == GameEngineSprite::Find("Text_GetReady"))
	//{
	//	GameEngineDirectory NewDir;
	//	NewDir.MoveParentToDirectory("ContentResources");
	//	NewDir.Move("ContentResources\\Texture\\TextUI");


	//	GameEngineSprite::LoadFolder("Text_GetReady", NewDir.GetPlusFileName("Text_GetReady").GetFullPath().c_str());
	//}
	GetReadyRender = CreateComponent<GameEngineUIRenderer>(CupHeadRendererOrder::UI);
	GetReadyRender->CreateAnimation({ .AnimationName = "Idle",  .SpriteName = "Text_GetReady", .FrameInter = 0.05f, .Loop = false , .ScaleToTexture = true });
	GetReadyRender->SetScaleRatio(2.5f);
	GetReadyRender->ChangeAnimation("Idle");
	GetTransform()->SetLocalPosition(float4(0, 0, 200));
}

void GetReadyUI::Update(float _Delta)
{
	if (true == GetReadyRender->IsAnimationEnd())
	{
		Death();
	}
}
