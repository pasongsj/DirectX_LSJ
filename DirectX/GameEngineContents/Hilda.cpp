#include "PrecompileHeader.h"
#include "Hilda.h"

#include <GameEngineBase/GameEngineRandom.h>
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

	Boss->GetTransform()->SetLocalPosition(float4(cosf(LiveTime * 2.5f) * 100.0f, CircleMove * (1-sinf(LiveTime * 2.5f)) * 100.0f)); // ���ٺ�����  8�� ������

	float degree = (LiveTime * 2.5f) / GameEngineMath::PIE2 + GameEngineMath::PIE/4;

	if (LastShare < degree)
	{
		LastShare = static_cast<int>(degree)+1;
		CircleMove *= -1;
	}


}

void Hilda::Render(float _DeltaTime)
{

}