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

	HaColiision = CreateComponent<GameEngineCollision>(CupHeadCollisionOrder::EnemyWeapon);
	HaColiision->SetColType(ColType::AABBBOX2D);
}

void HildaHA::Update(float _DeltaTime)
{
	if (nullptr == HaRender || nullptr == HaColiision)
	{
		MsgAssert("Ha 랜더러 또는 콜리전이 제대로 생성되지 않았습니다.");
		return;
	}

	HaColiision->GetTransform()->SetLocalScale(HaRender->GetTransform()->GetLocalScale());

	GetTransform()->AddLocalPosition(float4(-800 * _DeltaTime, 0));


	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	if (GetTransform()->GetWorldPosition().x < -ScreenSize.hx())
	{
		Death();
	}

	std::shared_ptr<GameEngineCollision> Col = HaColiision->Collision(CupHeadCollisionOrder::Player, ColType::AABBBOX2D, ColType::SPHERE2D);
	if (nullptr != Col) // 플레이어와 충돌 함
	{
		int a = 0;

	}

}