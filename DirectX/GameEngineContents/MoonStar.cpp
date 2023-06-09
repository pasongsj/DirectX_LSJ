#include "PrecompileHeader.h"
#include "MoonStar.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

MoonStar::MoonStar()
{
}

MoonStar::~MoonStar()
{
}

void MoonStar::Start()
{
	MakeSprite();
	StarRender = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::EnemyWeapon);
	FxRender = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::EnemyEffect);
	StarCollision = CreateComponent<GameEngineCollision>(CupHeadCollisionOrder::EnemyWeapon);

	StarRender->CreateAnimation({ .AnimationName = "A", .SpriteName = "Moon_Star_A",.FrameInter = 0.05f,.Loop = true, .ScaleToTexture = true });
	StarRender->CreateAnimation({ .AnimationName = "B", .SpriteName = "Moon_Star_B",.FrameInter = 0.05f,.Loop = true, .ScaleToTexture = true });
	StarRender->CreateAnimation({ .AnimationName = "C", .SpriteName = "Moon_Star_C",.FrameInter = 0.05f,.Loop = true, .ScaleToTexture = true });
	StarRender->CreateAnimation({ .AnimationName = "Pink", .SpriteName = "Moon_Star_Pink",.FrameInter = 0.05f,.Loop = true, .ScaleToTexture = true });

	FxRender->CreateAnimation({ .AnimationName = "IdleFX", .SpriteName = "Moon_Star_IdleFX",.FrameInter = 0.05f,.Loop = true, .ScaleToTexture = true });
	FxRender->CreateAnimation({ .AnimationName = "PinkFX", .SpriteName = "Moon_Star_PinkFX",.FrameInter = 0.05f,.Loop = true, .ScaleToTexture = true });


	StarCollision->SetColType(ColType::SPHERE2D);
	FxRender->GetTransform()->SetLocalPosition(float4(100,0));

	SettingType();

	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	StartPos = float4(ScreenSize.hx(), GameEngineRandom::MainRandom.RandomFloat(-ScreenSize.hy() / 2, ScreenSize.hy() - 50));
	GetTransform()->SetLocalPosition(StartPos);

	StarSpeed = GameEngineRandom::MainRandom.RandomFloat(400, 1000);
}

void MoonStar::SettingType()
{

	int Num = GameEngineRandom::MainRandom.RandomInt(0, 3);
	StarRender->ChangeAnimation(AniType[Num]);
	if (Num != 3)
	{
		FxRender->ChangeAnimation("IdleFX");
	}
	else
	{
		FxRender->ChangeAnimation("PinkFX");
	}
}

void MoonStar::Update(float _DeltaTime)
{
	// 화면 밖으로 나갔다면
	if (false == GetLevel()->GetMainCamera()->IsView(GetTransform()->GetTransDataRef()))
	{
		Death();
		return;
	}
	StarCollision->SetRenderScaleToCollision(StarRender);
	CollisionPlayer(StarCollision);
	StarMove(_DeltaTime);

}


void MoonStar::StarMove(float _DeltaTime)
{
	float4 NextPos = float4(-1 * StarSpeed * GetLiveTime(),50 * sinf(5 * GetLiveTime()), 500);
	GetTransform()->SetLocalPosition(StartPos + NextPos);
}

void MoonStar::MakeSprite()
{
	if (nullptr == GameEngineSprite::Find("Moon_Star_A"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources\\Texture\\stage1\\Boss\\Hilda\\Moon\\Projectiles\\Star");

		GameEngineSprite::LoadFolder("Moon_Star_A", Dir.GetPlusFileName("A").GetFullPath());
		GameEngineSprite::LoadFolder("Moon_Star_B", Dir.GetPlusFileName("B").GetFullPath());
		GameEngineSprite::LoadFolder("Moon_Star_C", Dir.GetPlusFileName("C").GetFullPath());
		GameEngineSprite::LoadFolder("Moon_Star_Pink", Dir.GetPlusFileName("Pink").GetFullPath());
		GameEngineSprite::LoadFolder("Moon_Star_IdleFX", Dir.GetPlusFileName("IdleFX").GetFullPath());
		GameEngineSprite::LoadFolder("Moon_Star_PinkFX", Dir.GetPlusFileName("PinkFX").GetFullPath());


	}
}