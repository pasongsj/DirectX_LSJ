#include "PrecompileHeader.h"
#include "Zeppling.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ZepplingBullet.h"

void Zeppling::Move_Start()
{
	Enemy->ChangeAnimation(Mode + "Idle");
}
void Zeppling::Move_Update(float _DeltaTime)
{

	GetTransform()->AddLocalPosition(float4::Left * MoveSpeed * _DeltaTime);
	if (GetTransform()->GetWorldPosition().x < 0.0f)
	{
		NextState = ZepplingState::SHOOT;
	}
}
void Zeppling::Move_End()
{
	MoveLen = 0;
}

void Zeppling::Shoot_Start()
{
	Enemy->ChangeAnimation(Mode + "Attack");
}
void Zeppling::Shoot_Update(float _DeltaTime)
{
	if (true == Enemy->IsAnimationEnd())
	{
		std::shared_ptr<ZepplingBullet> Bullet = GetLevel()->CreateActor<ZepplingBullet>();
		Bullet->GetTransform()->SetWorldPosition(Enemy->GetTransform()->GetWorldPosition() - float4(Enemy->GetTransform()->GetLocalScale().hx(),0));

		//float4 BulletDir =  플레이어 위치 - Zeppling의 위치
		//Bullet->SetBulletDir(BulletDir);
		if ("Purple_" == Mode)
		{
			Bullet->SetPurpleBullet();
		}
		NextState = ZepplingState::TURN;
	}
}
void Zeppling::Shoot_End()
{

}


void Zeppling::Turn_Start()
{
	Enemy->ChangeAnimation(Mode + "Turn");
}

void Zeppling::Turn_Update(float _DeltaTime)
{

	if (true == Enemy->IsAnimationEnd())
	{
		TransformData Tmp = Enemy->GetTransform()->GetTransDataRef();

		NextState = ZepplingState::BACK;
	}
}

void Zeppling::Turn_End()
{

}



void Zeppling::Dead_Start()
{

}
void Zeppling::Dead_Update(float _DeltaTime)
{

}
void Zeppling::Dead_End()
{

}

void Zeppling::Back_Start()
{
	Enemy->ChangeAnimation(Mode + "Idle");
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