#include "PrecompileHeader.h"
#include "PeaShooter.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEnginePlatform/GameEngineWindow.h>

PeaShooter::PeaShooter() 
{
}

PeaShooter::~PeaShooter() 
{
}

void PeaShooter::MakeSprite()
{
	if (nullptr == GameEngineSprite::Find("Cuphead_AirPlane_Bullet"))
	{

		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Cuphead_AirPlane\\bullet");



		// Origin
		// idle

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("peashot").GetFullPath(), "Cuphead_AirPlane_Bullet");
	}
}

void PeaShooter::Start()
{

	MakeSprite();

	Bullet = CreateComponent<GameEngineSpriteRenderer>();
	Bullet->CreateAnimation({ .AnimationName = "Origin",  .SpriteName = "Cuphead_AirPlane_Bullet", .FrameInter = 0.1f, .Loop = true, .ScaleToTexture = true });

	Bullet->ChangeAnimation("Origin");
}

void PeaShooter::Update(float _DeltaTime)
{
	GetTransform()->AddLocalPosition(float4(ShootSpeed * _DeltaTime, 0));
	GetTransform()->GetLocalPosition();

	if (GameEngineWindow::GameEngineWindow().GetScreenSize().x < GetTransform()->GetLocalPosition().x)
	{
		Death();
	}
}