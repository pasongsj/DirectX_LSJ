#include "PrecompileHeader.h"
#include "KnockOutUI.h"


#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineUIRenderer.h>

KnockOutUI::KnockOutUI() 
{
}

KnockOutUI::~KnockOutUI() 
{
}



void KnockOutUI::Start()
{
	std::shared_ptr<GameEngineCamera> Camera = GetLevel()->GetCamera(100);
	Camera->SetProjectionType(CameraType::Orthogonal);
	Camera->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });

	//// sprite
	//if (nullptr == GameEngineSprite::Find("Text_KO"))
	//{
	//	GameEngineDirectory NewDir;
	//	NewDir.MoveParentToDirectory("ContentResources");
	//	NewDir.Move("ContentResources\\Texture\\TextUI");


	//	GameEngineSprite::LoadFolder("Text_KO", NewDir.GetPlusFileName("Text_KO").GetFullPath().c_str());
	//}
	KnockOutRender = CreateComponent<GameEngineUIRenderer>(CupHeadRendererOrder::UI);
	KnockOutRender->CreateAnimation({ .AnimationName = "Idle",  .SpriteName = "Text_KO", .FrameInter = 0.05f, .Loop = false , .ScaleToTexture = true });
	KnockOutRender->SetScaleRatio(2.5f);
	KnockOutRender->ChangeAnimation("Idle");
	GetTransform()->SetLocalPosition(float4(0, 0, 200));

}

void KnockOutUI::Update(float _Delta)
{
	if (true == KnockOutRender->IsAnimationEnd())
	{
		Death();
	}
}
