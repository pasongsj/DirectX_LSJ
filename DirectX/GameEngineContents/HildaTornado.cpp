#include "PrecompileHeader.h"
#include "HildaTornado.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineLevel.h>

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
	TornatoRender = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::EnemyWeapon);
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
	float4 Screen = GameEngineWindow::GetScreenSize();
	float4 Cam = GetLevel()->GetMainCamera()->GetTransform()->GetWorldPosition();
	float4 LocalPos = GetTransform()->GetWorldPosition();
	if (abs(Cam.x- LocalPos.x)> Screen.hx() || abs(Cam.y - LocalPos.y) > Screen.hy())
	{
		Death();
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
		GetTransform()->AddLocalPosition(TornadoDir * TornadoSpeed * _DeltaTime);
		CollisionPlayer(TornatoCollision);
	}

}