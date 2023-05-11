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

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Boom").GetFullPath(), "shmup_super_boom");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Explode").GetFullPath(), "shmup_super_explode");

	}
}

void BoomEffect::Start()
{
	MakeSprite();
	Explode = CreateComponent<GameEngineSpriteRenderer>();
	Explode->CreateAnimation({ .AnimationName = "Idle",  .SpriteName = "shmup_super_boom",.FrameInter = 0.02f, .Loop = false , .ScaleToTexture = true });
	Explode->ChangeAnimation("Idle");

	Boom = CreateComponent<GameEngineSpriteRenderer>();
	Boom->CreateAnimation({ .AnimationName = "Idle",  .SpriteName = "shmup_super_explode", .FrameInter = 0.06f, .Loop = false , .ScaleToTexture = true });
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
	if (false == Explode->IsUpdate() && false == Boom->IsUpdate())
	{
		Death();
	}
}