#include "PrecompileHeader.h"
#include "BoomEffect.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

BoomEffect::BoomEffect() 
{
}

BoomEffect::~BoomEffect() 
{
}
void BoomEffect::MakeSprite()
{
	if (nullptr == GameEngineSprite::Find("shmup_super_boom"))
	{

		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("Cuphead_AirPlane\\effect");



		// Origin
		// idle

		GameEngineSprite::LoadFolder("shmup_super_boom", NewDir.GetPlusFileName("Boom").GetFullPath());
		GameEngineSprite::LoadFolder("shmup_super_explode", NewDir.GetPlusFileName("Explode").GetFullPath());

	}
}

void BoomEffect::Start()
{
	MakeSprite();
	Explode = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::PlayerEffect);
	Explode->CreateAnimation({ .AnimationName = "Idle",  .SpriteName = "shmup_super_boom",.FrameInter = 0.03f, .Loop = false , .ScaleToTexture = true });
	Explode->ChangeAnimation("Idle");

	Boom = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::PlayerEffect);
	Boom->CreateAnimation({ .AnimationName = "Idle",  .SpriteName = "shmup_super_explode", .FrameInter = 0.09f, .Loop = false , .ScaleToTexture = true });
	Boom->ChangeAnimation("Idle");
}

void BoomEffect::Update(float _DeltaTime)
{
	if (true == Explode->IsAnimationEnd())
	{
		Explode->Off();
	}
	if (true == Boom->IsAnimationEnd())
	{
		Boom->Off();
	}
	if ((false == Explode->IsUpdate() && false == Boom->IsUpdate()) || GetLiveTime() > 4.0f)
	{
		Death();
	}

}