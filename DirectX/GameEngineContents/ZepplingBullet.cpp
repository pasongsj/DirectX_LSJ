#include "PrecompileHeader.h"
#include "ZepplingBullet.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>


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
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("stage1\\Boss\\Hilda\\BlimpEnemy\\Bullet");


		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("A\\Bullet").GetFullPath(), "BlimpEnemy_BulletA");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("B\\Bullet").GetFullPath(), "BlimpEnemy_BulletB");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("C\\Bullet").GetFullPath(), "BlimpEnemy_BulletC");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Pink\\A").GetFullPath(), "BlimpEnemy_BulletPinkA");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Pink\\B").GetFullPath(), "BlimpEnemy_BulletPinkB");

	}
}



void ZepplingBullet::Start()
{
	MakeSprite();
	// �Ѿ� �̹��� ������
	Bullet = CreateComponent<GameEngineSpriteRenderer>();
	//Bullet->SetTexture("blimp_enemy_bullet_a_0001.png");
	Bullet->CreateAnimation({ .AnimationName = "BulletA", .SpriteName = "BlimpEnemy_BulletA",  .FrameInter = 0.05f, .Loop = true, .ScaleToImage = true });
	Bullet->CreateAnimation({ .AnimationName = "BulletB", .SpriteName = "BlimpEnemy_BulletB",  .FrameInter = 0.05f, .Loop = true, .ScaleToImage = true });
	Bullet->CreateAnimation({ .AnimationName = "BulletV", .SpriteName = "BlimpEnemy_BulletC",  .FrameInter = 0.05f, .Loop = true, .ScaleToImage = true });
	Bullet->CreateAnimation({ .AnimationName = "BulletPinkA", .SpriteName = "BlimpEnemy_BulletPinkA",  .FrameInter = 0.05f, .Loop = true, .ScaleToImage = true });
	Bullet->CreateAnimation({ .AnimationName = "BulletPinkB", .SpriteName = "BlimpEnemy_BulletPinkB",  .FrameInter = 0.05f, .Loop = true, .ScaleToImage = true });
	Bullet->ChangeAnimation("BulletA");
	// ��ġ,ȸ��, ũ��
	//Bullet->GetTransform()->SetLocalScale(float4(46, 33) * 0.8f);
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

