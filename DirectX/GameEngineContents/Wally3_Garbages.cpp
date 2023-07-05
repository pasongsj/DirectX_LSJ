#include "PrecompileHeader.h"
#include "Wally3_Garbages.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

Wally3_Garbages::Wally3_Garbages()
{
}

Wally3_Garbages::~Wally3_Garbages()
{
}
void Wally3_Garbages::MakeSprite()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentResources");
	Dir.Move("ContentResources\\Texture\\stage2\\Boss\\Wally\\Phase 3\\Garbage\\Garbages");


	if (nullptr == GameEngineSprite::Find("Wally3_Garbage_Apple"))
	{
		// Bird
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("garbage_apple").GetFullPath(), "Wally3_Garbage_Apple");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("garbage_boot").GetFullPath(), "Wally3_Garbage_Boot");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("garbage_fish").GetFullPath(), "Wally3_Garbage_Fish");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("pink_garbage_boot").GetFullPath(), "Wally3_Garbage_Boot_Pink");
	}
}

void Wally3_Garbages::Start()
{
	MakeSprite();
	GarbageRender = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::EnemyWeapon);
	GarbageRender->CreateAnimation({ .AnimationName = "0",.SpriteName = "Wally3_Garbage_Boot_Pink",.FrameInter = 0.05f,.Loop = true ,.ScaleToTexture = true });
	GarbageRender->CreateAnimation({ .AnimationName = "1",.SpriteName = "Wally3_Garbage_Boot",.FrameInter = 0.05f,.Loop = true ,.ScaleToTexture = true });
	GarbageRender->CreateAnimation({ .AnimationName = "2",.SpriteName = "Wally3_Garbage_Fish",.FrameInter = 0.05f,.Loop = true ,.ScaleToTexture = true });
	GarbageRender->CreateAnimation({ .AnimationName = "3",.SpriteName = "Wally3_Garbage_Apple",.FrameInter = 0.05f,.Loop = true ,.ScaleToTexture = true });

	GarbageCollision = CreateComponent<GameEngineCollision>(CupHeadCollisionOrder::EnemyWeapon);
	GarbageCollision->SetColType(ColType::SPHERE2D);

	Dir = float4(0, 3);
	Dir.Normalize();
}

void Wally3_Garbages::Update(float _DeltaTime)
{
	GetTransform()->AddLocalPosition(Dir * _DeltaTime * MoveSpeed);
	Dir -= (float4(_DeltaTime * 0.1f, _DeltaTime * GameEngineRandom::MainRandom.RandomFloat(0.4f, 0.6f)));
	if (false == GetLevel()->GetMainCamera()->IsView(GarbageRender->GetTransform()->GetTransDataRef()))
	{
		Death();
		return;
	}
}
void Wally3_Garbages::Setting(int index)
{
	GarbageRender->ChangeAnimation(std::to_string(index), false, GameEngineRandom::MainRandom.RandomInt(0, 7));

	switch (index)
	{
	case 0:
		GarbageCollision->SetColType(ColType::AABBBOX2D);
		GarbageCollision->GetTransform()->SetLocalScale(float4(50, 50, 0));
		GarbageCollision->GetTransform()->SetLocalPosition(float4(0, -5, 0));
		PinkObject = true;
		break;
	case 1:
		GarbageCollision->SetColType(ColType::AABBBOX2D);
		GarbageCollision->GetTransform()->SetLocalScale(float4(50, 50, 0));
		GarbageCollision->GetTransform()->SetLocalPosition(float4(0, -5, 0));
		break;
	case 2:
		GarbageCollision->SetColType(ColType::AABBBOX2D);
		GarbageCollision->GetTransform()->SetLocalScale(float4(80, 40, 0));
		break;
	case 3:
		GarbageCollision->SetColType(ColType::SPHERE2D);
		GarbageCollision->GetTransform()->SetLocalScale(float4(50, 0, 0));
		GarbageCollision->GetTransform()->SetLocalPosition(float4(0, -5, 0));
		break;
	default:
		break;
	}
}
