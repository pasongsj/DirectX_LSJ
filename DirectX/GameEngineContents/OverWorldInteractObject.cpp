#include "PrecompileHeader.h"
#include "OverWorldInteractObject.h"
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
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
	InteractCollision->GetTransform()->SetLocalScale({ 200 ,0 });


}

void OverWorldInteractObject::Update(float _DeltaTime)
{

}
