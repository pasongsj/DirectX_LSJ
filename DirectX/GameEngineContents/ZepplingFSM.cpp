#include "PrecompileHeader.h"
#include "Zeppling.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ZepplingBullet.h"

void Zeppling::Move_Start()
{

}
void Zeppling::Move_Update(float _DeltaTime)
{
	float4 MoveVec = float4::Left * MoveSpeed * _DeltaTime;
	GetTransform()->AddLocalPosition(MoveVec);
	MoveLen += MoveVec.Size();
	if (MoveLen > 500.0f)
	{
		NextState = ZepplingState::SHOOT;
	}
}
void Zeppling::Move_End()
{

}

void Zeppling::Shoot_Start()
{
	Bullet = GetLevel()->CreateActor<ZepplingBullet>();
	Bullet->GetTransform()->SetLocalPosition(GetTransform()->GetWorldPosition());
}
void Zeppling::Shoot_Update(float _DeltaTime)
{
	if (nullptr == Bullet || true == Bullet->IsDeath())
	{
		NextState = ZepplingState::BACK;
	}
}
void Zeppling::Shoot_End()
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

}
void Zeppling::Back_Update(float _DeltaTime)
{
	float4 MoveVec = float4::Right * MoveSpeed * _DeltaTime;
	GetTransform()->AddLocalPosition(MoveVec);
	MoveLen += MoveVec.Size();

	// 수정필요 : 윈도우 크기 적용 필요
	if (MoveLen > 400.0f)
	{
		Death();
	}
}
void Zeppling::Back_End()
{

}