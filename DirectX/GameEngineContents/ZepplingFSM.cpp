#include "PrecompileHeader.h"
#include "Zeppling.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "GameContentsEnemyRenderer.h"


#include "ZepplingBullet.h"
#include "ZepplingBroken.h"
#include "PlayerAirPlaneMode.h"


void Zeppling::Move_Start()
{
	EnemyRender->ChangeAnimation(Mode + "Idle");
}
void Zeppling::Move_Update(float _DeltaTime)
{

	GetTransform()->AddLocalPosition(float4::Left * MoveSpeed * _DeltaTime);
	if (GetTransform()->GetWorldPosition().x < 0.0f)
	{
		NextState = ZepplingState::SHOOT;
	}
	CheckDeath();
}
void Zeppling::Move_End()
{
	MoveLen = 0;
}

void Zeppling::Shoot_Start()
{
	EnemyRender->ChangeAnimation(Mode + "Attack");
	BulletDir = PlayerAirPlaneMode::MainPlayer->GetTransform()->GetWorldPosition() - GetTransform()->GetWorldPosition();// 플레이어 위치 - Zeppling의 위치
	BulletDir.z = 0;
	BulletDir.Normalize();
}
void Zeppling::Shoot_Update(float _DeltaTime)
{
	if (true == EnemyRender->IsAnimationEnd())
	{
		std::shared_ptr<ZepplingBullet> Bullet = GetLevel()->CreateActor<ZepplingBullet>(CupHeadActorOrder::EnemyWeapon);
		float4 Pos = EnemyRender->GetTransform()->GetWorldPosition();
		Pos.x -= EnemyRender->GetTransform()->GetLocalScale().hx();
		Pos.z = 490;

		Bullet->GetTransform()->SetLocalPosition(Pos);
		Bullet->SetBulletDir(BulletDir);
		if ("Purple_" == Mode)
		{
			Bullet->SetPurpleBullet();
		}
		NextState = ZepplingState::TURN;
	}
	CheckDeath();
}
void Zeppling::Shoot_End()
{

}


void Zeppling::Turn_Start()
{
	EnemyRender->ChangeAnimation(Mode + "Turn");
}

void Zeppling::Turn_Update(float _DeltaTime)
{

	if (true == EnemyRender->IsAnimationEnd())
	{
		NextState = ZepplingState::BACK;
	}
	CheckDeath();
}

void Zeppling::Turn_End()
{

}



void Zeppling::Dead_Start()
{
	std::shared_ptr< ZepplingBroken> Pieces = GetLevel()->CreateActor< ZepplingBroken>(CupHeadActorOrder::Enemy);
	Pieces->SetColor(Mode);
	float4 Pos = GetTransform()->GetWorldPosition();
	Pos.z = 600;
	Pieces->GetTransform()->SetLocalPosition(Pos);
	Death();

}
void Zeppling::Dead_Update(float _DeltaTime)
{

}
void Zeppling::Dead_End()
{

}

void Zeppling::Back_Start()
{
	EnemyRender->ChangeAnimation(Mode + "Idle");
	GetTransform()->SetLocalNegativeScaleX();
}
void Zeppling::Back_Update(float _DeltaTime)
{
	GetTransform()->AddLocalPosition(float4::Right * MoveSpeed * _DeltaTime);

	if (GetTransform()->GetWorldPosition().x > ScreenSize.hx())
	{
		Death();
	}
}
void Zeppling::Back_End()
{

}