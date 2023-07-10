#include "PrecompileHeader.h"
#include "OverWorldToHilda.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCore.h>
#include "LoadingLevel.h"

OverWorldToHilda::OverWorldToHilda()
{
}

OverWorldToHilda::~OverWorldToHilda()
{
}

void OverWorldToHilda::MakeSprite()
{
	if (nullptr == GameEngineSprite::Find("To_Hilda_OverWorld"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources\\Texture\\stage1\\Overworld");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("blimp").GetFullPath(), "To_Hilda_OverWorld");
	}
}


void OverWorldToHilda::Start()
{
	OverWorldInteractObject::Start();
	MakeSprite();
	BlimpRender = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::BackGround);
	BlimpRender->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "To_Hilda_OverWorld",.FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
	BlimpRender->ChangeAnimation("Idle");

	FRender = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::UI);
	FRender->SetScaleToTexture("interactionIcon.png");
	FRender->GetTransform()->SetLocalPosition(float4{ 0,0,-100 });
	SetInteractRange(200.0f);

	GetTransform()->SetLocalPosition(float4{ 3350,-300,500 });
	if (false == GameEngineInput::IsKey("KeyF_Interaction"))
	{
		GameEngineInput::CreateKey("KeyF_Interaction", 'F');
	}
}

void OverWorldToHilda::Update(float _DeltaTime)
{
	OverWorldInteractObject::Update(_DeltaTime);
	if (true == GetisInteract())
	{
		FRender->On();
		if (true == GameEngineInput::IsDown("KeyF_Interaction"))
		{
			LoadingLevel::SetLevel(CupheadLevel::WALLY);
			GameEngineCore::ChangeLevel("LoadingLevel");
			return;
		}
	}
	else
	{
		FRender->Off();
	}
}
