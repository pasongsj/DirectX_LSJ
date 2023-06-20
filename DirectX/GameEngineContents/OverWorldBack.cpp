#include "PrecompileHeader.h"
#include "OverWorldBack.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

OverWorldBack::OverWorldBack() 
{
}

OverWorldBack::~OverWorldBack() 
{
}

void OverWorldBack::Start()
{
	std::shared_ptr<GameEngineSpriteRenderer> BG = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::BackGround);
	BG->SetScaleToTexture("Overworld_Map.png");
	GetTransform()->SetLocalPosition(float4(0, 0, 900));
}
void OverWorldBack::Update(float _DeltaTiime)
{

}