#include "PrecompileHeader.h"
#include "Sagittarius.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>

Sagittarius::Sagittarius() 
{
}

Sagittarius::~Sagittarius() 
{
}

void Sagittarius::Start()
{						

	GetTransform()->SetLocalPosition(float4(300.0f, 0));


	Upper = CreateComponent<GameEngineSpriteRenderer>();
	Upper->SetScaleToTexture("sagg_idle_0001.png");
	Upper->GetTransform()->SetLocalPosition(float4(0, 100));

	Lower = CreateComponent<GameEngineSpriteRenderer>();
	Lower->SetScaleToTexture("sagg_cloud_top_0003.png");
	Lower->GetTransform()->SetLocalPosition(float4(170, -50));


	//Lower->SetTexture("sagg_cloud_top_0003.png");
																													   
	//std::shared_ptr<GameEngineTexture> FindTex = GameEngineTexture::Find("sagg_cloud_top_0003.png");
	//float4 Scale = float4(FindTex->GetWidth(), FindTex->GetHeight(), 1);
	//Lower->GetTransform()->SetLocalScale(Scale);
	////Lower->GetTransform()->SetLocalScale(Scale * 0.8f);
	////Lower->SetScaleToTexture("sagg_cloud_top_0003.png");							
	//Lower->GetTransform()->SetLocalPosition(float4(170, -50));						
	////Lower->GetTransform()->SetLocalPosition(float4(145, -50));						

																						
																						
	//FSM																				

	//IDLE
	StartFuncPtr[static_cast<int>(SagittariusState::IDLE)] = std::bind(&Sagittarius::Idle_Start, this);
	UpdateFuncPtr[static_cast<int>(SagittariusState::IDLE)] = std::bind(&Sagittarius::Idle_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(SagittariusState::IDLE)] = std::bind(&Sagittarius::Idle_End, this);

	//SHOOT
	StartFuncPtr[static_cast<int>(SagittariusState::SHOOT)] = std::bind(&Sagittarius::Shoot_Start, this);
	UpdateFuncPtr[static_cast<int>(SagittariusState::SHOOT)] = std::bind(&Sagittarius::Shoot_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(SagittariusState::SHOOT)] = std::bind(&Sagittarius::Shoot_End, this);


}

void Sagittarius::Update(float _DeltaTime)
{
	GetTransform()->SetLocalPosition(float4(300.0f, 0) + float4(cosf(GetLiveTime() * 2.5f) * SpinSpeed, CircleMove * (1 - sinf(GetLiveTime() * 2.5f)) * SpinSpeed)); // 힐다베르그  8자 움직임

	float degree = (GetLiveTime() * 2.5f) / GameEngineMath::PIE2 + GameEngineMath::PIE / 4;

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
		LastShare = static_cast<int>(degree) + 1;
	}

	UpdateState(_DeltaTime);
}

void Sagittarius::Render(float _DeltaTime) 
{
}



void Sagittarius::UpdateState(float _DeltaTime)
{

}


void Sagittarius::Idle_Start()
{

}

void Sagittarius::Idle_Update(float _DeltaTime)
{

}

void Sagittarius::Idle_End()
{

}


void Sagittarius::Shoot_Start()
{

}

void Sagittarius::Shoot_Update(float _DeltaTime)
{

}

void Sagittarius::Shoot_End()
{

}
