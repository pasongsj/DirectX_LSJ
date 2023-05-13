#include "PrecompileHeader.h"
#include "Zeppling.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ZepplingBullet.h"

void Zeppling::Move_Start()
{
	Monster->ChangeAnimation(Mode + "Idle");
}
void Zeppling::Move_Update(float _DeltaTime)
{

	float4 MoveVec = float4::Left * MoveSpeed * _DeltaTime;
	GetTransform()->AddLocalPosition(MoveVec);
	MoveLen += MoveVec.Size();
	if (MoveLen > 300.0f)
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
	Bullet = GetLevel()->CreateActor<ZepplingBullet>();
	Bullet->GetTransform()->SetWorldPosition(Monster->GetTransform()->GetWorldPosition());


	Monster->ChangeAnimation(Mode + "Attack");
}
void Zeppling::Shoot_Update(float _DeltaTime)
{
	if (true == Monster->IsAnimationEnd())
	{
		NextState = ZepplingState::TURN;
	}
}
void Zeppling::Shoot_End()
{

}


void Zeppling::Turn_Start()
{
	Monster->ChangeAnimation(Mode + "Turn");
}

void Zeppling::Turn_Update(float _DeltaTime)
{

	if (true == Monster->IsAnimationEnd())
	{
		TransformData Tmp = Monster->GetTransform()->GetTransDataRef();

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
	Monster->ChangeAnimation(Mode + "Idle");
	TransformData Tmp = GetTransform()->GetTransDataRef();

	TransformData MonsterTmp0 = Monster->GetTransform()->GetTransDataRef();
	GetTransform()->SetLocalNegativeScaleX();

	TransformData Tmp2 = GetTransform()->GetTransDataRef();

	TransformData MonsterTmp1 = Monster->GetTransform()->GetTransDataRef();

	MoveLen = 0;


}
void Zeppling::Back_Update(float _DeltaTime)
{
	float4 MoveVec = float4::Right * MoveSpeed * _DeltaTime;
	GetTransform()->AddLocalPosition(MoveVec);

	MoveLen += MoveVec.Size();
	// 수정필요 : 윈도우 크기 적용 필요
	if (MoveLen > 500.0f)
	{
		Death();
	}
}
void Zeppling::Back_End()
{

}