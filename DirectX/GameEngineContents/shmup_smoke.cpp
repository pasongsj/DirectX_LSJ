#include "PrecompileHeader.h"
#include "shmup_smoke.h"
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

shmup_smoke::shmup_smoke() 
{
}

shmup_smoke::~shmup_smoke() 
{
}

void shmup_smoke::MakeSprite()
{
	if (nullptr == GameEngineSprite::Find("shmup_smoke"))
	{

		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources\\Texture\\Cuphead_AirPlane");

		GameEngineSprite::LoadFolder("shmup_smoke", NewDir.GetPlusFileName("effect\\shmup_smoke").GetFullPath());
	}
}

void shmup_smoke::Start() 
{
	MakeSprite();
	SmokeRender = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::PlayerEffect);
	SmokeRender->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "shmup_smoke",.FrameInter = 1.0f,.ScaleToTexture = true });
	SmokeRender->GetTransform()->SetLocalPosition(float4(-70, 0));
	SmokeRender->SetAnimationStartEvent("Idle", 1, [this] {	SmokeRender->GetTransform()->SetLocalPosition(float4(-70, 0));}	);
	SmokeRender->SetAnimationStartEvent("Idle", 2, [this] {	SmokeRender->GetTransform()->SetLocalPosition(float4(-85, 10));}	);
	SmokeRender->SetAnimationStartEvent("Idle", 3, [this] {	SmokeRender->GetTransform()->SetLocalPosition(float4(-85, 30));}	);
	SmokeRender->SetAnimationStartEvent("Idle", 4, [this] {	SmokeRender->GetTransform()->SetLocalPosition(float4(-85, 45));}	);
	SmokeRender->SetAnimationStartEvent("Idle", 5, [this] {	SmokeRender->GetTransform()->SetLocalPosition(float4(-100, 45));}	);
	SmokeRender->SetAnimationStartEvent("Idle", 6, [this] {	SmokeRender->GetTransform()->SetLocalPosition(float4(-110, 45));}	);
	SmokeRender->SetAnimationStartEvent("Idle", 7, [this] {	SmokeRender->GetTransform()->SetLocalPosition(float4(-120, 43));}	);
	SmokeRender->SetAnimationStartEvent("Idle", 8, [this] {	SmokeRender->GetTransform()->SetLocalPosition(float4(-130, 25));}	);
	SmokeRender->SetAnimationStartEvent("Idle", 9, [this] {	SmokeRender->GetTransform()->SetLocalPosition(float4(-135, 20));}	);


	SmokeRender->SetAnimationStartEvent("Idle", 10, [this] {	SmokeRender->GetTransform()->SetLocalPosition(float4(-135, 15));}	);
	SmokeRender->SetAnimationStartEvent("Idle", 11, [this] {	SmokeRender->GetTransform()->SetLocalPosition(float4(-140, -5));}	);
	SmokeRender->SetAnimationStartEvent("Idle", 12, [this] {	SmokeRender->GetTransform()->SetLocalPosition(float4(-135, -10));}	);
	SmokeRender->SetAnimationStartEvent("Idle", 13, [this] {	SmokeRender->GetTransform()->SetLocalPosition(float4(-135, -30));}	);
	SmokeRender->SetAnimationStartEvent("Idle", 14, [this] {	SmokeRender->GetTransform()->SetLocalPosition(float4(-135, 0));}	);
	SmokeRender->SetAnimationStartEvent("Idle", 15, [this] {	SmokeRender->GetTransform()->SetLocalPosition(float4(-135, 0));}	);
	SmokeRender->SetAnimationStartEvent("Idle", 16, [this] {	SmokeRender->GetTransform()->SetLocalPosition(float4(-135, 0));}	);
	SmokeRender->SetAnimationStartEvent("Idle", 17, [this] {	SmokeRender->GetTransform()->SetLocalPosition(float4(-135, 0));}	);
	SmokeRender->SetAnimationStartEvent("Idle", 18, [this] {	SmokeRender->GetTransform()->SetLocalPosition(float4(-135, 0));}	);
	SmokeRender->SetAnimationStartEvent("Idle", 19, [this] {	SmokeRender->GetTransform()->SetLocalPosition(float4(-135, 0));}	);






	SmokeRender->ChangeAnimation("Idle");

	GetTransform()->SetLocalPosition(float4(0, 0, 350));
}

void shmup_smoke::Update(float _DeltaTime)
{
	if (true == SmokeRender->IsAnimationEnd())
	{
		Death();
		return;
	}
}
