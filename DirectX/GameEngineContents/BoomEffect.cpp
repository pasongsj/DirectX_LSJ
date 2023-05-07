#include "PrecompileHeader.h"
#include "BoomEffect.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

BoomEffect::BoomEffect() 
{
}

BoomEffect::~BoomEffect() 
{
}

void BoomEffect::Start()
{
	Explode = CreateComponent<GameEngineSpriteRenderer>();
	Explode->CreateAnimation({ .AnimationName = "Idle",  .TextureName = "shmup_super_explode_00", .Start = 1, .End = 27,.InterTime = 0.02f, .Loop = false });
	Explode->ChangeAnimation("Idle");


	Boom = CreateComponent<GameEngineSpriteRenderer>();
	Boom->CreateAnimation({ .AnimationName = "Idle",  .TextureName = "shmup_super_boom_00", .Start = 1, .End = 11,.InterTime = 0.06f, .Loop = false });
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