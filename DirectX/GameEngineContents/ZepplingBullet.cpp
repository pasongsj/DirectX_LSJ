#include "PrecompileHeader.h"
#include "ZepplingBullet.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineCollision.h>


ZepplingBullet::ZepplingBullet() 
{
}

ZepplingBullet::~ZepplingBullet() 
{
}


void ZepplingBullet::MakeSprite()
{
	if (nullptr == GameEngineSprite::Find("BlimpEnemy_BulletA"))
	{

		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources\\Texture\\stage1\\Boss\\Hilda\\BlimpEnemy\\Bullet");


		GameEngineSprite::LoadFolder("BlimpEnemy_BulletA", NewDir.GetPlusFileName("A\\Bullet").GetFullPath());
		GameEngineSprite::LoadFolder("BlimpEnemy_BulletB", NewDir.GetPlusFileName("B\\Bullet").GetFullPath());
		GameEngineSprite::LoadFolder("BlimpEnemy_BulletC", NewDir.GetPlusFileName("C\\Bullet").GetFullPath());
		GameEngineSprite::LoadFolder("BlimpEnemy_BulletPinkA", NewDir.GetPlusFileName("Pink\\A").GetFullPath());
		GameEngineSprite::LoadFolder("BlimpEnemy_BulletPinkB", NewDir.GetPlusFileName("Pink\\B").GetFullPath());

	}
}



void ZepplingBullet::Start()
{
	MakeSprite();
	// �Ѿ� �̹��� ������
	Bullet = CreateComponent<GameEngineSpriteRenderer>();
	//Bullet->SetTexture("blimp_enemy_bullet_a_0001.png");
	Bullet->CreateAnimation({ .AnimationName = "BulletA", .SpriteName = "BlimpEnemy_BulletA",  .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
	Bullet->CreateAnimation({ .AnimationName = "BulletB", .SpriteName = "BlimpEnemy_BulletB",  .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
	Bullet->CreateAnimation({ .AnimationName = "BulletV", .SpriteName = "BlimpEnemy_BulletC",  .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
	Bullet->CreateAnimation({ .AnimationName = "BulletPinkA", .SpriteName = "BlimpEnemy_BulletPinkA",  .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
	Bullet->CreateAnimation({ .AnimationName = "BulletPinkB", .SpriteName = "BlimpEnemy_BulletPinkB",  .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
	Bullet->ChangeAnimation("BulletA");
	// ��ġ,ȸ��, ũ��
	//Bullet->GetTransform()->SetLocalScale(float4(46, 33) * 0.8f);
	//Bullet->Off();

	BulletCollision = CreateComponent<GameEngineCollision>(CupHeadCollisionOrder::Enemy);
}


void ZepplingBullet::Update(float _DeltaTime)
{
	BulletCollision->GetTransform()->SetLocalScale(Bullet->GetTransform()->GetLocalScale());

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
	if (GetTransform()->GetWorldPosition().x < -GameEngineWindow::GetScreenSize().hx())
	{
		Death();
	}

}


void ZepplingBullet::Render(float _DeltaTimes)
{
}

void ZepplingBullet::SetPurpleBullet()
{
	int RandomNumber = GameEngineRandom::MainRandom.RandomInt(0, 4);
	if (3 < RandomNumber)
	{
		Bullet->ChangeAnimation("BulletPinkA");
	}
}