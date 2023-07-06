#include "PrecompileHeader.h"
#include "OverWorldInteractObject.h"
#include <GameEngineCore/GameEngineCollision.h>
#include "Player.h"

OverWorldInteractObject::OverWorldInteractObject()
{
}

OverWorldInteractObject::~OverWorldInteractObject()
{
}

void OverWorldInteractObject::Start()
{
	InteractCol = CreateComponent< GameEngineCollision>(CupHeadCollisionOrder::UI);
	InteractCol->SetColType(ColType::SPHERE2D);
}

void OverWorldInteractObject::Update(float _DeltaTime)
{
	if (nullptr != Player::MainPlayer && nullptr != InteractCol->Collision(CupHeadCollisionOrder::Player))
	{
		isInteract = true;
	}
	else
	{
		isInteract = false;
	}
}
void OverWorldInteractObject::SetInteractRange(float _Range)
{
	InteractCol->GetTransform()->SetLocalScale({ _Range ,0 });
}
