#include "PrecompileHeader.h"
#include "Sagittarius.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineLevel.h>

#include <GameEngineCore/GameEngineCollision.h>

#include "SagittariusArrow.h"
#include "SagittariusStar.h"
#include "GameContentsEnemyRenderer.h"


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
		NewDir.Move("ContentResources\\Texture\\stage1\\Boss\\Hilda\\Sagittarius\\Sagittarius");


		GameEngineSprite::LoadFolder( "Sagittarius_Lower_Idle", NewDir.GetPlusFileName("Lower\\Idle").GetFullPath());
		GameEngineSprite::LoadFolder("Sagittarius_Upper_Idle", NewDir.GetPlusFileName("Upper\\Idle").GetFullPath());
		GameEngineSprite::LoadFolder("Sagittarius_Upper_Attack", NewDir.GetPlusFileName("Upper\\Attack").GetFullPath());

	}
}




void Sagittarius::Start()
{			
	SetPhase(4);
	MakeSprite();


	Upper = CreateComponent<GameContentsEnemyRenderer>(CupHeadRendererOrder::Boss);
	Upper->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "Sagittarius_Upper_Idle", .FrameInter = 0.05f, .Loop = true , .ScaleToTexture = true });
	Upper->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "Sagittarius_Upper_Attack",.FrameInter = 0.07f, .Loop = false , .ScaleToTexture = true });

	Upper->ChangeAnimation("Idle");
	Upper->GetTransform()->SetLocalPosition(float4(0, 100));

	Lower = CreateComponent<GameContentsEnemyRenderer>(CupHeadRendererOrder::Boss);
	Lower->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "Sagittarius_Lower_Idle",  .FrameInter = 0.05f, .Loop = true , .ScaleToTexture = true });
	Lower->ChangeAnimation("Idle");
	Lower->GetTransform()->SetLocalPosition(float4(160, -55));


	BossCollision = CreateComponent<GameEngineCollision>(CupHeadCollisionOrder::Enemy);
	BossCollision->GetTransform()->SetLocalScale(float4(200.0f,440,0));
	BossCollision->GetTransform()->SetLocalPosition(float4(80, 40, 0));
	BossCollision->SetColType(ColType::AABBBOX2D);

	std::shared_ptr<GameEngineCollision> Arm = CreateComponent<GameEngineCollision>(CupHeadCollisionOrder::Enemy);
	Arm->GetTransform()->SetLocalScale(float4(120, 50, 0));
	Arm->GetTransform()->SetLocalPosition(float4(-80, 90, 0));
	Arm->SetColType(ColType::AABBBOX2D);
																						
	//FSM																				

	//IDLE
	StartFuncPtr[static_cast<int>(SagittariusState::IDLE)] = std::bind(&Sagittarius::Idle_Start, this);
	UpdateFuncPtr[static_cast<int>(SagittariusState::IDLE)] = std::bind(&Sagittarius::Idle_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(SagittariusState::IDLE)] = std::bind(&Sagittarius::Idle_End, this);

	//SHOOT
	StartFuncPtr[static_cast<int>(SagittariusState::ATTACK)] = std::bind(&Sagittarius::Attack_Start, this);
	UpdateFuncPtr[static_cast<int>(SagittariusState::ATTACK)] = std::bind(&Sagittarius::Attack_Update, this, std::placeholders::_1);
	EndFuncPtr[static_cast<int>(SagittariusState::ATTACK)] = std::bind(&Sagittarius::Attack_End, this);

	GetTransform()->SetLocalPosition(float4(0, 0, 600));

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
	GetTransform()->SetLocalPosition(GetHildaMove(_DeltaTime) + float4(300.0f, 0 , 600));
}

void Sagittarius::Idle_End()
{
}
void Sagittarius::Attack_Start()
{
	Upper->GetTransform()->SetLocalPosition(float4(15, 120));
	Upper->ChangeAnimation("Attack");
	AttackInterval = GameEngineRandom::MainRandom.RandomFloat(5.0f, 8.0f);
	isShoot = false;
	ResetLiveTime();
}

void Sagittarius::Attack_Update(float _DeltaTime)
{
	if (false == isShoot && GetLiveTime() > 0.5f)
	{
		isShoot = true;
		std::shared_ptr<SagittariusArrow> Arrow = GetLevel()->CreateActor<SagittariusArrow>(CupHeadActorOrder::EnemyWeapon);
		Arrow->GetTransform()->SetLocalPosition(Upper->GetTransform()->GetWorldPosition() + float4(0,30, -100));

		std::shared_ptr<SagittariusStar> Star1 = GetLevel()->CreateActor<SagittariusStar>(CupHeadActorOrder::EnemyWeapon);
		Star1->GetTransform()->SetLocalPosition(Upper->GetTransform()->GetWorldPosition() + float4(0, 60, -90));

		std::shared_ptr<SagittariusStar> Star2 = GetLevel()->CreateActor<SagittariusStar>(CupHeadActorOrder::EnemyWeapon);
		Star2->GetTransform()->SetLocalPosition(Upper->GetTransform()->GetWorldPosition() + float4(0, 0 , -90));
	}
	if (true == Upper->IsAnimationEnd())
	{
		NextState = SagittariusState::IDLE;
	}
}

void Sagittarius::Attack_End()
{

}



void Sagittarius::Attack(int _Dmg)
{
	Upper->MakeBright();
	Lower->MakeBright();
	GameEnemy::Attack(_Dmg);
}
