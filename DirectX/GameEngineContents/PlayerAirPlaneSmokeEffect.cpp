#include "PrecompileHeader.h"
#include "PlayerAirPlaneSmokeEffect.h"
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

PlayerAirPlaneSmokeEffect::PlayerAirPlaneSmokeEffect() 
{
}

PlayerAirPlaneSmokeEffect::~PlayerAirPlaneSmokeEffect() 
{
}
void PlayerAirPlaneSmokeEffect::MakeSprite()
{
	if (nullptr == GameEngineSprite::Find("Cuphead_AirPlane_Smoke_Idle"))
	{

		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Cuphead_AirPlane");

		GameEngineSprite::LoadFolder("Cuphead_AirPlane_Smoke_Idle", NewDir.GetPlusFileName("effect\\PlaneSmoke").GetFullPath());
	}
}

void PlayerAirPlaneSmokeEffect::Start()
{
	MakeSprite();
	Smoke = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::PlayerEffect);
	Smoke->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "Cuphead_AirPlane_Smoke_Idle", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	Smoke->ChangeAnimation("Idle");

}
void PlayerAirPlaneSmokeEffect::Update(float _DeltaTime)
{
	GetTransform()->AddLocalPosition(float4::Left * MoveSpeed * _DeltaTime);
	if (true == Smoke->IsAnimationEnd())
	{
		Death();
		return;
	}
}
