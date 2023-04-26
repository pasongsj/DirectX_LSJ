#include "PrecompileHeader.h"
#include "Hilda.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

Hilda::Hilda() 
{
}

Hilda::~Hilda() 
{
}

void Hilda::Start()
{

	Boss = CreateComponent<GameEngineSpriteRenderer>();
	Boss->SetTexture("blimp_idle_0001.png");
	Boss->GetTransform()->SetLocalScale(float4(300, 300));
	GetTransform()->SetLocalPosition(float4(300.0f,0));
	

}

void Hilda::Update(float _DeltaTime)
{
	LiveTime += _DeltaTime;

	Boss->GetTransform()->SetLocalPosition(float4(-sinf(LiveTime*5)*100.0f,sinf(LiveTime*2.5f)*200.0f)); // 힐다베르그  8자 움직임

}

void Hilda::Render(float _DeltaTime)
{

}