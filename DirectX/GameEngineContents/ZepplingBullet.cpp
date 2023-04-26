#include "PrecompileHeader.h"
#include "ZepplingBullet.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>


ZepplingBullet::ZepplingBullet() 
{
}

ZepplingBullet::~ZepplingBullet() 
{
}

void ZepplingBullet::Start()
{
	// 총알 이미지 랜더러
	Bullet = CreateComponent<GameEngineSpriteRenderer>();
	Bullet->SetTexture("blimp_enemy_bullet_a_0001.png");
	// 위치,회전, 크기
	Bullet->GetTransform()->SetLocalScale(float4(46, 33) * 0.8f);
	//Bullet->Off();
}


void ZepplingBullet::Update(float _DeltaTime)
{
	//if ()// 화면밖으로 나갔다던가, 플레이어를 때렸다던가
	//{
	//	return;
	//}
	//else if () // 플레이어를 때렸다던가
	//{
	//	return;
	//}
	//else if () // 플레이어의 패리를 당했다던가
	//{
	//	return;
	//}

	float4 MoveVec = Dir * BulletSpeed * _DeltaTime;
	GetTransform()->AddLocalPosition(MoveVec);

	// 수정필요 : 현재 윈도우의 위치를 가져와야 함
	if (GetTransform()->GetWorldPosition().x < -400.0f)
	{
		Death();
	}

}


void ZepplingBullet::Render(float _DeltaTimes)
{
}

