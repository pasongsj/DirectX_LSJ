#include "PrecompileHeader.h"
#include "FlappyBird.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>

FlappyBird::FlappyBird()
{
}

FlappyBird::~FlappyBird()
{
}
void FlappyBird::MakeSprite()
{
	if (nullptr == GameEngineSprite::Find("FlapyBird_Pink_Idle"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources\\Texture\\stage2\\Boss\\Wally\\Phase 1\\FlappyBirds");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Yellow\\Fly").GetFullPath(), "FlapyBird_Yellow_Idle");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Yellow\\Death").GetFullPath(), "FlapyBird_Yellow_Death");		

		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Pink\\Fly").GetFullPath(), "FlapyBird_Pink_Idle");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Pink\\Death").GetFullPath(), "FlapyBird_Pink_Death");
	}
}

void FlappyBird::Start()
{
	MakeSprite();
	BirdRender = CreateComponent< GameEngineSpriteRenderer>(CupHeadRendererOrder::Enemy);
	BirdRender->CreateAnimation({ .AnimationName = "Yellow_Idle",.SpriteName = "FlapyBird_Yellow_Idle",.FrameInter = 0.05f,.Loop = true, .ScaleToTexture = true });
	BirdRender->CreateAnimation({ .AnimationName = "Yellow_Death",.SpriteName = "FlapyBird_Yellow_Death",.FrameInter = 0.05f,.Loop = false, .ScaleToTexture = true });	
	BirdRender->CreateAnimation({ .AnimationName = "Pink_Idle",.SpriteName = "FlapyBird_Pink_Idle",.FrameInter = 0.05f,.Loop = true, .ScaleToTexture = true });
	BirdRender->CreateAnimation({ .AnimationName = "Pink_Death",.SpriteName = "FlapyBird_Pink_Death",.FrameInter = 0.05f,.Loop = false, .ScaleToTexture = true });
	BirdRender->ChangeAnimation("Yellow_Idle");


	BirdCollision = CreateComponent< GameEngineCollision>(CupHeadCollisionOrder::Enemy);
	BirdCollision->SetColType(ColType::SPHERE2D);
	BirdCollision->GetTransform()->SetLocalScale(float4(80,0));
	BirdCollision->GetTransform()->SetLocalPosition(float4(10, -10));
	isDeathAnimation = false;
}

void FlappyBird::Update(float _DeltaTime)
{
	if (false == GetLevel()->GetMainCamera()->IsView(GetTransform()->GetTransDataRef()) ||
		true == isDeathAnimation && true == BirdRender->IsAnimationEnd())
	{
		GameEngineObjectBase::Death();
		return;
	}
	if (true == BirdCollision->IsUpdate())
	{
		CollisionPlayer(BirdCollision);
	}
	if (false == isDeathAnimation)
	{
		if (GetHP() <= 0)
		{
			BirdCollision->Off();
			if (true == IsPink())
			{
				BirdRender->ChangeAnimation("Pink_Death");
			}
			else
			{
				BirdRender->ChangeAnimation("Yellow_Death");

			}
			isDeathAnimation = true;
		}
		else
		{
			float4 NextPos = StartPoint + float4(-1 * MoveDuration * MoveSpeed, 20 * sinf(MoveDuration * 10));
			NextPos.z = 550;
			GetTransform()->SetLocalPosition(NextPos);
			MoveDuration += _DeltaTime;
		}

	}

}
void FlappyBird::SetPink()
{
	BirdRender->ChangeAnimation("Pink_Idle");
	SetPinkObject();
}

void FlappyBird::Death()
{
	SetHP(0);
}
