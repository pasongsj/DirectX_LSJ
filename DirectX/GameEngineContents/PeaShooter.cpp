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

void PeaShooter::Start()
{
	Bullet = CreateComponent<GameEngineSpriteRenderer>();
	Bullet->CreateAnimation({ .AnimationName = "Origin",  .TextureName = "schmup_peashot_bullet_A_000", .Start = 1, .End = 3,.InterTime = 0.1f, .Loop = true });
	//Bullet->CreateAnimation({ .AnimationName = "Idle",  .TextureName = "schmup_peashot_bullet_A_000", .Start = 1, .End = 3,.InterTime = 0.1f, .Loop = true });
	//Bullet->CreateAnimation({ .AnimationName = "Idle",  .TextureName = "schmup_peashot_bullet_A_000", .Start = 1, .End = 3,.InterTime = 0.1f, .Loop = true });
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