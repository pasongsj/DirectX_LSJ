#include "PrecompileHeader.h"
#include "HildaTornado.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

HildaTornado::HildaTornado() 
{
}

HildaTornado::~HildaTornado() 
{
}

void HildaTornado::MakeSprite()
{
	if (nullptr == GameEngineSprite::Find("Hilda_Tornado_Intro"))
	{

		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources\\Texture\\stage1\\Boss\\Hilda\\HildaBerg\\Normal");


		GameEngineSprite::LoadFolder("Hilda_Tornado_Attack", NewDir.GetPlusFileName("Tornado\\Tornado\\Attack").GetFullPath());
		GameEngineSprite::LoadFolder("Hilda_Tornado_Intro", NewDir.GetPlusFileName("Tornado\\Tornado\\Intro").GetFullPath());

	}
}


void HildaTornado::Start()
{
	MakeSprite();
	TornatoRender = CreateComponent<GameEngineSpriteRenderer>();
	TornatoRender->CreateAnimation({ .AnimationName = "Intro",  .SpriteName = "Hilda_Tornado_Intro", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
	TornatoRender->CreateAnimation({ .AnimationName = "attack",  .SpriteName = "Hilda_Tornado_Attack",.FrameInter = 0.05f, .Loop = false , .ScaleToTexture = true });
	TornatoRender->ChangeAnimation("Intro");

	TornatoCollision = CreateComponent<GameEngineCollision>(CupHeadCollisionOrder::EnemyWeapon);
	TornatoCollision->SetColType(ColType::AABBBOX2D);
	TornatoCollision->Off();
}

void HildaTornado::Update(float _DeltaTime)
{

	if (nullptr == TornatoRender || nullptr == TornatoCollision)
	{
		MsgAssert("토네이도 랜더러또는 콜리전이 제대로 생성되지 않았습니다");
		return;
	}
	if (true == isIntro && GetLiveTime() > 1.6f)
	{
		isIntro = false;
		TornatoRender->ChangeAnimation("attack");
		TornatoCollision->On();
	}
	else if (false == isIntro)
	{
		TornatoCollision->GetTransform()->SetLocalScale(TornatoRender->GetTransform()->GetLocalScale());
		GetTransform()->AddLocalPosition(float4(-1000 * _DeltaTime, 0));
	}

	float4 Screen = GameEngineWindow::GetScreenSize();
	if (GetTransform()->GetWorldPosition().x< -Screen.hx() || GetTransform()->GetWorldPosition().x > Screen.hx())
	{
		Death();
	}

	std::shared_ptr<GameEngineCollision> Col = TornatoCollision->Collision(CupHeadCollisionOrder::Player, ColType::AABBBOX2D, ColType::SPHERE2D);
	if (nullptr != Col) // 플레이어와 충돌 함
	{
		int a = 0;

	}
}