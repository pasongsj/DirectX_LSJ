#include "PrecompileHeader.h"
#include "Zeppling.h"

void Zeppling::Move_Start()
{

}
void Zeppling::Move_Update(float _DeltaTime)
{
	float4 MoveVec = float4::Left * MoveSpeed * _DeltaTime;
	GetTransform()->AddLocalPosition(MoveVec);
	MoveLen += MoveVec.Size();
	if (MoveLen > 800.0f)
	{
		NextState = ZepplingState::SHOOT;
	}
}
void Zeppling::Move_End()
{

}

void Zeppling::Shoot_Start()
{

}
void Zeppling::Shoot_Update(float _DeltaTime)
{
	int a = 0;
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

}
void Zeppling::Back_End()
{

}