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

	Boss->GetTransform()->SetLocalPosition(float4(cosf(GetLiveTime() * 2.5f) * SpinSpeed, CircleMove * (1-sinf(GetLiveTime() * 2.5f)) * SpinSpeed)); // 힐다베르그  8자 움직임

	float degree = (GetLiveTime() * 2.5f) / GameEngineMath::PIE2 + GameEngineMath::PIE/4;

	if (LastShare < degree)
	{
		int RandNum = GameEngineRandom::MainRandom.RandomInt(0, 9);
		if (0 == (RandNum & 1))
		{
			CircleMove = 1;
		}
		else
		{
			CircleMove = -1;
		}
		LastShare = static_cast<int>(degree)+1;
	}


}

void Hilda::Render(float _DeltaTime)
{

}