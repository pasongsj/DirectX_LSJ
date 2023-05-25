#include "PrecompileHeader.h"
#include "ZepplingBroken.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineBase/GameEngineRandom.h>

ZepplingBroken::ZepplingBroken() 
{
}

ZepplingBroken::~ZepplingBroken() 
{
}

void ZepplingBroken::Start()
{
	MakeSprite();


	A = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::Enemy);
	B = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::Enemy);
	C = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::Enemy);
	D = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::Enemy);
	E = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::Enemy);
	F = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::Enemy);

	Spark = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::Enemy);
	Explode = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::Enemy);

	A->CreateAnimation({.AnimationName = "Green_",  .SpriteName = "BlimpEnemy_Green_Death_A", .FrameInter = 0.1f, .Loop = false, .ScaleToTexture = true });
	B->CreateAnimation({.AnimationName = "Green_",  .SpriteName = "BlimpEnemy_Green_Death_B", .FrameInter = 0.1f, .Loop = false, .ScaleToTexture = true });
	C->CreateAnimation({.AnimationName = "Green_",  .SpriteName = "BlimpEnemy_Green_Death_C", .FrameInter = 0.1f, .Loop = false, .ScaleToTexture = true });
	D->CreateAnimation({.AnimationName = "Green_",  .SpriteName = "BlimpEnemy_Green_Death_D", .FrameInter = 0.1f, .Loop = false, .ScaleToTexture = true });
	E->CreateAnimation({.AnimationName = "Green_",  .SpriteName = "BlimpEnemy_Green_Death_E", .FrameInter = 0.1f, .Loop = false, .ScaleToTexture = true });
	F->CreateAnimation({.AnimationName = "Green_",  .SpriteName = "BlimpEnemy_Green_Death_F", .FrameInter = 0.1f, .Loop = false, .ScaleToTexture = true });
	
	A->CreateAnimation({.AnimationName = "Purple_",  .SpriteName = "BlimpEnemy_Purple_Death_A", .FrameInter = 0.1f, .Loop = false, .ScaleToTexture = true });
	B->CreateAnimation({.AnimationName = "Purple_",  .SpriteName = "BlimpEnemy_Purple_Death_B", .FrameInter = 0.1f, .Loop = false, .ScaleToTexture = true });
	C->CreateAnimation({.AnimationName = "Purple_",  .SpriteName = "BlimpEnemy_Purple_Death_C", .FrameInter = 0.1f, .Loop = false, .ScaleToTexture = true });
	D->CreateAnimation({.AnimationName = "Purple_",  .SpriteName = "BlimpEnemy_Purple_Death_D", .FrameInter = 0.1f, .Loop = false, .ScaleToTexture = true });
	E->CreateAnimation({.AnimationName = "Purple_",  .SpriteName = "BlimpEnemy_Purple_Death_E", .FrameInter = 0.1f, .Loop = false, .ScaleToTexture = true });
	F->CreateAnimation({.AnimationName = "Purple_",  .SpriteName = "BlimpEnemy_Purple_Death_F", .FrameInter = 0.1f, .Loop = false, .ScaleToTexture = true });

	Spark->CreateAnimation({ .AnimationName = "Idle",  .SpriteName = "BlimpEnemy_Spark", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	Explode->CreateAnimation({ .AnimationName = "Idle",  .SpriteName = "BlimpEnemy_Explode", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	MakePiecesDir();
}

void ZepplingBroken::Update(float _DeltaTime)
{
	Dir.y -= 0.1f;
	GetTransform()->AddLocalPosition(Dir * 100 *_DeltaTime);
	MovePieces(_DeltaTime);
	if (true == CheckEnd())
	{
		Death();
	}
}


void ZepplingBroken::MakeSprite()
{
	if (nullptr == GameEngineSprite::Find("BlimpEnemy_Green_Death_A"))
	{

		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources\\Texture\\stage1\\Boss\\Hilda\\BlimpEnemy");

		// death
		GameEngineSprite::LoadFolder("BlimpEnemy_Green_Death_A", NewDir.GetPlusFileName("Green\\Pieces\\A").GetFullPath());
		GameEngineSprite::LoadFolder("BlimpEnemy_Green_Death_B", NewDir.GetPlusFileName("Green\\Pieces\\B").GetFullPath());
		GameEngineSprite::LoadFolder("BlimpEnemy_Green_Death_C", NewDir.GetPlusFileName("Green\\Pieces\\C").GetFullPath());
		GameEngineSprite::LoadFolder("BlimpEnemy_Green_Death_D", NewDir.GetPlusFileName("Green\\Pieces\\D").GetFullPath());
		GameEngineSprite::LoadFolder("BlimpEnemy_Green_Death_E", NewDir.GetPlusFileName("Green\\Pieces\\E").GetFullPath());
		GameEngineSprite::LoadFolder("BlimpEnemy_Green_Death_F", NewDir.GetPlusFileName("Green\\Pieces\\F").GetFullPath());

		GameEngineSprite::LoadFolder("BlimpEnemy_Purple_Death_A", NewDir.GetPlusFileName("Purple\\Pieces\\A").GetFullPath());
		GameEngineSprite::LoadFolder("BlimpEnemy_Purple_Death_B", NewDir.GetPlusFileName("Purple\\Pieces\\B").GetFullPath());
		GameEngineSprite::LoadFolder("BlimpEnemy_Purple_Death_C", NewDir.GetPlusFileName("Purple\\Pieces\\C").GetFullPath());
		GameEngineSprite::LoadFolder("BlimpEnemy_Purple_Death_D", NewDir.GetPlusFileName("Purple\\Pieces\\D").GetFullPath());
		GameEngineSprite::LoadFolder("BlimpEnemy_Purple_Death_E", NewDir.GetPlusFileName("Purple\\Pieces\\E").GetFullPath());
		GameEngineSprite::LoadFolder("BlimpEnemy_Purple_Death_F", NewDir.GetPlusFileName("Purple\\Pieces\\F").GetFullPath());


		GameEngineSprite::LoadFolder("BlimpEnemy_Explode", NewDir.GetPlusFileName("Explode (Death)\\Explode").GetFullPath());
		GameEngineSprite::LoadFolder("BlimpEnemy_Spark", NewDir.GetPlusFileName("Explode (Death)\\Spark").GetFullPath());

	}
}

void ZepplingBroken::ChangeAnimationAll()
{
	A->ChangeAnimation(ZepColor, true);
	B->ChangeAnimation(ZepColor, true);
	C->ChangeAnimation(ZepColor, true);
	D->ChangeAnimation(ZepColor, true);
	E->ChangeAnimation(ZepColor, true);
	F->ChangeAnimation(ZepColor, true);

	Spark->ChangeAnimation("Idle", true);
	Explode->ChangeAnimation("Idle", true);
}

bool ZepplingBroken::CheckEnd()
{
	if (A != nullptr &&
		Spark != nullptr &&
		Explode != nullptr)
	{
		if (true == A->IsAnimationEnd() && true == Spark->IsAnimationEnd() && true == Explode->IsAnimationEnd())
		{
			return true;
		}
	}
	return false;
}

void ZepplingBroken::MovePieces(float _DeltaTime)
{
	if (true == DirA.IsZero())
	{
		MakePiecesDir();
	}
	float MoveSpeed = 200;
	A->GetTransform()->AddLocalPosition(DirA * _DeltaTime * MoveSpeed);
	B->GetTransform()->AddLocalPosition(DirB * _DeltaTime * MoveSpeed);
	C->GetTransform()->AddLocalPosition(DirC * _DeltaTime * MoveSpeed);
	D->GetTransform()->AddLocalPosition(DirD * _DeltaTime * MoveSpeed);
	E->GetTransform()->AddLocalPosition(DirE * _DeltaTime * MoveSpeed);
	F->GetTransform()->AddLocalPosition(DirF * _DeltaTime * MoveSpeed);
}

void ZepplingBroken::MakePiecesDir()
{
	float4 d = float4(GameEngineRandom::MainRandom.RandomFloat(-1, 1), GameEngineRandom::MainRandom.RandomFloat(-1, 1));
	d.Normalize();
	DirA = d;
	DirB = d.RotaitonYDegReturn(60);
	DirC = d.RotaitonYDegReturn(120);
	DirD = d.RotaitonYDegReturn(180);
	DirE = d.RotaitonYDegReturn(240);
	DirF = d.RotaitonYDegReturn(300);

}