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

void Sagittarius::MakeSprite()
{
	if (nullptr == GameEngineSprite::Find("Sagittarius_Lower_Idle"))
	{

		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("stage1\\Boss\\Hilda\\Sagittarius\\Sagittarius");


		GameEngineSprite::LoadFolder( "Sagittarius_Lower_Idle", NewDir.GetPlusFileName("Lower\\Idle").GetFullPath());
		GameEngineSprite::LoadFolder("Sagittarius_Upper_Idle", NewDir.GetPlusFileName("Upper\\Idle").GetFullPath());
		GameEngineSprite::LoadFolder("Sagittarius_Upper_Attack", NewDir.GetPlusFileName("Upper\\Attack").GetFullPath());

	}
}




void Sagittarius::Start()
{						
	MakeSprite();
	//GetTransform()->SetLocalPosition(float4(300.0f, 0));


	Upper = CreateComponent<GameEngineSpriteRenderer>();
	Upper->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "Sagittarius_Upper_Idle", .FrameInter = 0.05f, .Loop = true , .ScaleToTexture = true });
	Upper->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "Sagittarius_Upper_Attack",.FrameInter = 0.05f, .Loop = false , .ScaleToTexture = true });

	Upper->ChangeAnimation("Idle");
	//Upper->SetScaleToTexture("sagg_idle_0001.png");
	Upper->GetTransform()->SetLocalPosition(float4(0, 100));

	Lower = CreateComponent<GameEngineSpriteRenderer>();
	Lower->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "Sagittarius_Lower_Idle",  .FrameInter = 0.05f, .Loop = true , .ScaleToTexture = true });
	//Lower->SetScaleToTexture("sagg_cloud_top_0003.png");
	Lower->ChangeAnimation("Idle");
	Lower->GetTransform()->SetLocalPosition(float4(160, -55));



																						
																						
	//FSM																				

	//IDLE
	StartFuncPtr[static_cast<int>(SagittariusState::IDLE)] = std::bind(&Sagittarius::Idle_Start, this);
	UpdateFuncPtr[static_cast<int>(SagittariusState::IDLE)] = std::bind(&Sagittarius::Idle_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(SagittariusState::IDLE)] = std::bind(&Sagittarius::Idle_End, this);

	//SHOOT
	StartFuncPtr[static_cast<int>(SagittariusState::ATTACK)] = std::bind(&Sagittarius::Attack_Start, this);
	UpdateFuncPtr[static_cast<int>(SagittariusState::ATTACK)] = std::bind(&Sagittarius::Attack_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(SagittariusState::ATTACK)] = std::bind(&Sagittarius::Attack_End, this);


}

void Sagittarius::Update(float _DeltaTime)
{

	UpdateState(_DeltaTime);
}

void Sagittarius::Render(float _DeltaTime) 
{
}



void Sagittarius::UpdateState(float _DeltaTime)
{
	if (CurState != NextState)
	{
		// CurState에 대한 ending
		EndFuncPtr[static_cast<int>(CurState)]();

		// NextState에 대한 Start
		StartFuncPtr[static_cast<int>(NextState)]();

		// State변경
		CurState = NextState;
		return;
	}

	UpdateFuncPtr[static_cast<int>(CurState)](_DeltaTime);
}


void Sagittarius::Idle_Start()
{
	ResetLiveTime();
	Upper->GetTransform()->SetLocalPosition(float4(0, 100));
	Upper->ChangeAnimation("Idle");
	Lower->ChangeAnimation("Idle");
}

void Sagittarius::Idle_Update(float _DeltaTime)
{
	if (AttackInterval < GetLiveTime())
	{
		NextState = SagittariusState::ATTACK;
	}
	IdleMoveTime += _DeltaTime;

	GetTransform()->SetLocalPosition(float4(cosf(IdleMoveTime * 2.5f) * SpinSpeed, CircleMove * (1 - sinf(IdleMoveTime * 2.5f)) * SpinSpeed) + float4(300.0f, 0)); // 힐다베르그  8자 움직임

	float degree = (IdleMoveTime * 2.5f) / GameEngineMath::PIE2 + GameEngineMath::PIE / 4;

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
}

void Sagittarius::Idle_End()
{
}


void Sagittarius::Attack_Start()
{
	Upper->GetTransform()->SetLocalPosition(float4(15, 110));
	Upper->ChangeAnimation("Attack");
	AttackInterval = GameEngineRandom::MainRandom.RandomFloat(5.0f, 8.0f);
}

void Sagittarius::Attack_Update(float _DeltaTime)
{
	if (true == Upper->IsAnimationEnd())
	{
		NextState = SagittariusState::IDLE;
	}
}

void Sagittarius::Attack_End()
{

}
