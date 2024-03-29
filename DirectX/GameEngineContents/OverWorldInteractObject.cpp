#include "PrecompileHeader.h"
#include "OverWorldInteractObject.h"
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineInput.h>
//#include "Player.h"

OverWorldInteractObject::OverWorldInteractObject()
{
}

OverWorldInteractObject::~OverWorldInteractObject()
{
}

void OverWorldInteractObject::Start()
{
	InteractRender = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::BackGround);

	InteractCollision = CreateComponent< GameEngineCollision>(CupHeadCollisionOrder::UI);
	InteractCollision->SetColType(ColType::SPHERE2D);
	InteractCollision->GetTransform()->SetLocalScale({ 150 ,0 });

	TitleCard = CreateComponent<GameEngineUIRenderer>(CupHeadRendererOrder::UI);
	TitleCard->GetTransform()->SetWorldPosition(float4::Zero);
	TitleCard->Off();
	if (false == GameEngineInput::IsKey("ESC_Buttion"))
	{
		GameEngineInput::CreateKey("ESC_Buttion", VK_ESCAPE);
	}
	if (false == GameEngineInput::IsKey("EnterKey"))
	{
		GameEngineInput::CreateKey("EnterKey", VK_RETURN);
	}

}

void OverWorldInteractObject::Update(float _DeltaTime)
{

	std::shared_ptr<GameEngineCollision> Obj = nullptr;
	if (nullptr != (Obj = InteractCollision->Collision(CupHeadCollisionOrder::Player)))
	{
		if ((false == isInteract && true == GameEngineInput::IsDown("KeyZ_Interaction")))
		{
			TitleCard->On();
			isInteract = true;
			GameEngineSound::Play("worldmap_menu_up.wav");
		}
		if (true == isInteract)
		{
			if(true == GameEngineInput::IsDown("ESC_Buttion"))
			{
				TitleCard->Off();
				isInteract = false;
				GameEngineSound::Play("WorldMap_LevelSelect_BubbleDisappear.wav");
			}
			if (nullptr != EnterFucntion && true == isInteract && true == GameEngineInput::IsDown("EnterKey"))
			{
				EnterFucntion();
				GameEngineSound::Play("WorldMap_LevelSelect_StartLevel.wav");
				return;
			}
		}


	}
}
