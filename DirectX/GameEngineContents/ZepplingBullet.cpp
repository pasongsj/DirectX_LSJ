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
	// �Ѿ� �̹��� ������
	Bullet = CreateComponent<GameEngineSpriteRenderer>();
	Bullet->SetTexture("blimp_enemy_bullet_a_0001.png");
	// ��ġ,ȸ��, ũ��
	Bullet->GetTransform()->SetLocalScale(float4(46, 33) * 0.8f);
	//Bullet->Off();
}


void ZepplingBullet::Update(float _DeltaTime)
{
	//if ()// ȭ������� �����ٴ���, �÷��̾ ���ȴٴ���
	//{
	//	return;
	//}
	//else if () // �÷��̾ ���ȴٴ���
	//{
	//	return;
	//}
	//else if () // �÷��̾��� �и��� ���ߴٴ���
	//{
	//	return;
	//}

	float4 MoveVec = Dir * BulletSpeed * _DeltaTime;
	GetTransform()->AddLocalPosition(MoveVec);

	// �����ʿ� : ���� �������� ��ġ�� �����;� ��
	if (GetTransform()->GetWorldPosition().x < -400.0f)
	{
		Death();
	}

}


void ZepplingBullet::Render(float _DeltaTimes)
{
}

