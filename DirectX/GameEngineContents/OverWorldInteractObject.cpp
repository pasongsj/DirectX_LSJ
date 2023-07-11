#include "PrecompileHeader.h"
#include "OverWorldInteractObject.h"
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "Player.h"

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
	InteractCollision->GetTransform()->SetLocalScale({ 200 ,0 });


	FRender = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::UI);
	FRender->SetScaleToTexture("interactionIcon.png");
	FRender->GetTransform()->SetLocalPosition(float4{ 0,0,-300 });
}

void OverWorldInteractObject::Update(float _DeltaTime)
{
	if (nullptr != Player::MainPlayer && nullptr != InteractCollision->Collision(CupHeadCollisionOrder::Player))
	{
		FRender->On();
		if (nullptr != InteractFucntion)
		{
			InteractFucntion();
		}
	}
	else
	{
		FRender->Off();
	}
}
//void OverWorldInteractObject::SetInteractRange(float _Range)
//{
//	InteractCollision->GetTransform()->SetLocalScale({ _Range ,0 });
//}
