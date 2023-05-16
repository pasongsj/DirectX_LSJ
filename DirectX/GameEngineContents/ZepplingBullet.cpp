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
	// 총알 이미지 랜더러
	Bullet = CreateComponent<GameEngineSpriteRenderer>();
	//Bullet->SetTexture("blimp_enemy_bullet_a_0001.png");
	Bullet->CreateAnimation({ .AnimationName = "BulletA", .SpriteName = "BlimpEnemy_BulletA",  .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
	Bullet->CreateAnimation({ .AnimationName = "BulletB", .SpriteName = "BlimpEnemy_BulletB",  .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
	Bullet->CreateAnimation({ .AnimationName = "BulletV", .SpriteName = "BlimpEnemy_BulletC",  .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
	Bullet->CreateAnimation({ .AnimationName = "BulletPinkA", .SpriteName = "BlimpEnemy_BulletPinkA",  .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
	Bullet->CreateAnimation({ .AnimationName = "BulletPinkB", .SpriteName = "BlimpEnemy_BulletPinkB",  .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
	Bullet->ChangeAnimation("BulletA");
	// 위치,회전, 크기
	//Bullet->GetTransform()->SetLocalScale(float4(46, 33) * 0.8f);
	//Bullet->Off();

	BulletCollision = CreateComponent<GameEngineCollision>(CupHeadCollisionOrder::Enemy);
}


void ZepplingBullet::Update(float _DeltaTime)
{
	BulletCollision->GetTransform()->SetLocalScale(Bullet->GetTransform()->GetLocalScale());

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