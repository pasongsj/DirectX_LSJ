#include "PrecompileHeader.h"
#include "PinkSphere.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

PinkSphere::PinkSphere()
{
}

PinkSphere::~PinkSphere()
{
}

void PinkSphere::Start()
{
	PinkRender = CreateComponent< GameEngineSpriteRenderer>(CupHeadRendererOrder::BackGround);
	PinkRender->SetScaleToTexture("tutorial_pink_sphere_1.png");
	PinkCollision = CreateComponent<GameEngineCollision>(CupHeadCollisionOrder::Enemy);
	PinkCollision->GetTransform()->SetLocalScale(PinkRender->GetTransform()->GetWorldScale() * 0.75f);
	GetTransform()->SetLocalPosition(float4(386, -46, 890));
	SetPinkObject();
}

