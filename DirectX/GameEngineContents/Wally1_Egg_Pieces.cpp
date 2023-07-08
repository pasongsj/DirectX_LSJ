#include "PrecompileHeader.h"
#include "Wally1_Egg_Pieces.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>

Wally1_Egg_Pieces::Wally1_Egg_Pieces() 
{
}

Wally1_Egg_Pieces::~Wally1_Egg_Pieces() 
{
}
void Wally1_Egg_Pieces::MakeSprite()
{
	if (nullptr == GameEngineSprite::Find("Wally_Egg_Piece_A"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources"); // ContentResources\Texture\stage2\Boss\Wally\Phase 1
		Dir.Move("ContentResources\\Texture\\stage2\\Boss\\Wally\\Phase 1\\Egg");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Piece\\A").GetFullPath(), "Wally_Egg_Piece_A");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Piece\\B").GetFullPath(), "Wally_Egg_Piece_B");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Piece\\C").GetFullPath(), "Wally_Egg_Piece_C");
	}

}


void Wally1_Egg_Pieces::Start()
{
	MakeSprite();
	PiecesRender = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::EnemyWeapon);
	PiecesRender->CreateAnimation({ .AnimationName = "A",.SpriteName = "Wally_Egg_Piece_A",.FrameInter = 0.05f,.Loop = true, .ScaleToTexture = true });
	PiecesRender->CreateAnimation({ .AnimationName = "B",.SpriteName = "Wally_Egg_Piece_B",.FrameInter = 0.05f,.Loop = true, .ScaleToTexture = true });
	PiecesRender->CreateAnimation({ .AnimationName = "C",.SpriteName = "Wally_Egg_Piece_C",.FrameInter = 0.05f,.Loop = true, .ScaleToTexture = true });
	PiecesRender->ChangeAnimation(AnimationMap[GameEngineRandom::MainRandom.RandomInt(1, 3)]);

	PiecesCollision = CreateComponent< GameEngineCollision>(CupHeadCollisionOrder::EnemyWeapon);
	PiecesCollision->SetColType(ColType::SPHERE2D);
	PiecesCollision->GetTransform()->SetLocalScale(float4(55, 0));
	//EggCollision->GetTransform()->SetLocalPosition(float4(-25, 0));
	
}
void Wally1_Egg_Pieces::Update(float _DeltaTime)
{
	GetTransform()->AddLocalPosition(Dir * _DeltaTime * MoveSpeed);
	if (false == GetLevel()->GetMainCamera()->IsView(GetTransform()->GetTransDataRef()))
	{
		Death();
		return;
	}
}