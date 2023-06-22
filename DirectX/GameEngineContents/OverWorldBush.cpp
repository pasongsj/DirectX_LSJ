#include "PrecompileHeader.h"
#include "OverWorldBush.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

OverWorldBush::OverWorldBush()
{
}

OverWorldBush::~OverWorldBush()
{
}


void OverWorldBush::Start()
{
	std::shared_ptr<GameEngineSpriteRenderer> LeftBush = CreateComponent< GameEngineSpriteRenderer>(CupHeadRendererOrder::ForeGround);
	LeftBush->SetScaleToTexture("Overworld_Bush_Left.png");
	float4 LScale = LeftBush->GetTransform()->GetLocalScale();
	LeftBush->GetTransform()->SetLocalPosition(float4(-LScale.hx(), 0));


	std::shared_ptr<GameEngineSpriteRenderer> RightBush = CreateComponent< GameEngineSpriteRenderer>(CupHeadRendererOrder::ForeGround);
	RightBush->SetScaleToTexture("Overworld_Bush_Right.png");
	float4 RScale = RightBush->GetTransform()->GetLocalScale();
	RightBush->GetTransform()->SetLocalPosition(float4(RScale.hx(), -21));

	GetTransform()->SetLocalPosition(float4(2139, -1084, 300));
}

void OverWorldBush::Update(float _DeltaTime)
{
}
