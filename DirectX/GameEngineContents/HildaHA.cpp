#include "PrecompileHeader.h"
#include "HildaHA.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCollision.h>

HildaHA::HildaHA() 
{
}

HildaHA::~HildaHA() 
{
}

void HildaHA::MakeSprite()
{
	if (nullptr == GameEngineSprite::Find("Hilda_Ha"))
	{

		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources\\Texture\\stage1\\Boss\\Hilda\\HildaBerg\\Normal");


		GameEngineSprite::LoadFolder("Hilda_Ha", NewDir.GetPlusFileName("Laugh\\Ha").GetFullPath());

	}
}

void HildaHA::Start()
{
	MakeSprite();
	HaRender = CreateComponent<GameEngineSpriteRenderer>();
	HaRender->CreateAnimation({.AnimationName = "Ha", .SpriteName = "Hilda_Ha",  .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	
	HaRender->ChangeAnimation("Ha");

	HaCollision = CreateComponent<GameEngineCollision>(CupHeadCollisionOrder::EnemyWeapon);
	HaCollision->SetColType(ColType::AABBBOX2D);
}

void HildaHA::Update(float _DeltaTime)
{
	if (nullptr == HaRender || nullptr == HaCollision)
	{
		MsgAssert("Ha 랜더러 또는 콜리전이 제대로 생성되지 않았습니다.");
		return;
	}
	HaCollision->SetRenderScaleToCollision(HaRender);


	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	if (GetTransform()->GetWorldPosition().x < -ScreenSize.hx())
	{
		Death();
		return;
	}
	// 플레이어와 충돌 함
	CollisionPlayer(HaCollision);
	
	GetTransform()->AddLocalPosition(float4(-800 * _DeltaTime, 0));
}