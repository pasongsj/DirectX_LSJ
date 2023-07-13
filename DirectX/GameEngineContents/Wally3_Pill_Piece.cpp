#include "PrecompileHeader.h"
#include "Wally3_Pill_Piece.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCollision.h>

Wally3_Pill_Piece::Wally3_Pill_Piece()
{
}

Wally3_Pill_Piece::~Wally3_Pill_Piece()
{
}

void Wally3_Pill_Piece::MakeSprite()
{
	if (nullptr == GameEngineSprite::Find("Wally3_Pill_Blue_Piece"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources\\Texture\\stage2\\Boss\\Wally\\Phase 3\\Birds\\Pills");


		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Normal\\Blue Piece").GetFullPath(), "Wally3_Pill_Blue_Piece");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Normal\\Yellow Piece").GetFullPath(), "Wally3_Pill_Yellow_Piece");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Pink\\Dark Pink Piece").GetFullPath(), "Wally3_Pill_DPink_Piece");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Pink\\Light Pink Piece").GetFullPath(), "Wally3_Pill_LPink_Piece");
	}
}

void Wally3_Pill_Piece::Start()
{
	MakeSprite();
	PieceRender = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::EnemyWeapon);
	PieceRender->CreateAnimation({ .AnimationName = "Blue",.SpriteName = "Wally3_Pill_Blue_Piece",.FrameInter = 0.05f,.Loop = true,.ScaleToTexture = true });
	PieceRender->CreateAnimation({ .AnimationName = "Yellow",.SpriteName = "Wally3_Pill_Yellow_Piece",.FrameInter = 0.05f,.Loop = true,.ScaleToTexture = true });
	PieceRender->CreateAnimation({ .AnimationName = "DPink",.SpriteName = "Wally3_Pill_DPink_Piece",.FrameInter = 0.05f,.Loop = true,.ScaleToTexture = true });
	PieceRender->CreateAnimation({ .AnimationName = "LPink",.SpriteName = "Wally3_Pill_LPink_Piece",.FrameInter = 0.05f,.Loop = true,.ScaleToTexture = true });

	PieceCollision = CreateComponent<GameEngineCollision>(CupHeadCollisionOrder::EnemyWeapon);
	PieceCollision->SetColType(ColType::SPHERE2D);
	PieceCollision->GetTransform()->SetLocalScale(float4(30, 30));
}

void Wally3_Pill_Piece::Update(float _DeltaTime)
{
	GetTransform()->AddLocalPosition(Dir * MoveSpeed * _DeltaTime);
	if (false == GetLevel()->GetMainCamera()->IsView(PieceRender->GetTransform()->GetTransDataRef()))
	{
		Death();
		return;
	}
	CollisionPlayer(PieceCollision);

}

void Wally3_Pill_Piece::Setting(float _Rot, int index)
{
	if (2 == index || 3 == index)
	{
		SetPinkObject();
	}
	PieceRender->ChangeAnimation(NextAnimation[index]);
	Dir.RotaitonZDeg(_Rot);
	GetTransform()->SetLocalRotation(float4(0, 0, _Rot));
}