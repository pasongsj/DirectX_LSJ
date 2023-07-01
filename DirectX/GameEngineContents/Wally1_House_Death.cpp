#include "PrecompileHeader.h"
#include "Wally1_House_Death.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

Wally1_House_Death::Wally1_House_Death()
{
}

Wally1_House_Death::~Wally1_House_Death()
{
}
void Wally1_House_Death::MakeSprite()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentResources"); // ContentResources\Texture\stage2\Boss\Wally\Phase 1
	Dir.Move("ContentResources\\Texture\\stage2\\Boss\\Wally\\Phase 1\\Death\\House");
	if (nullptr == GameEngineSprite::Find("Wally1_House_Back"))
	{
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Back").GetFullPath(), "Wally1_House_Back");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Bottom").GetFullPath(), "Wally1_House_Bottom");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Front").GetFullPath(), "Wally1_House_Front");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Left").GetFullPath(), "Wally1_House_Left");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Right").GetFullPath(), "Wally1_House_Right");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Top").GetFullPath(), "Wally1_House_Top");
	}
}


void Wally1_House_Death::Start()
{
	MakeSprite();
	BackRender	    = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::EnemyEffect);
	BottomRender    = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::EnemyEffect);
	LeftRender	    = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::EnemyEffect);
	RightRender	    = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::EnemyEffect);
	TopRender		= CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::EnemyEffect);
	FrontRender	    = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::EnemyEffect);

	BackRender	->CreateAnimation({ .AnimationName = "Idle",.SpriteName = "Wally1_House_Back",.FrameInter = 0.05f,.Loop = true,.ScaleToTexture = true });
	RightRender	->CreateAnimation({ .AnimationName = "Idle",.SpriteName = "Wally1_House_Right",.FrameInter = 0.05f,.Loop = true,.ScaleToTexture = true });
	BottomRender->CreateAnimation({ .AnimationName = "Idle",.SpriteName = "Wally1_House_Bottom",.FrameInter = 0.05f,.Loop = true,.ScaleToTexture = true });
	FrontRender	->CreateAnimation({ .AnimationName = "Idle",.SpriteName = "Wally1_House_Front",.FrameInter = 0.05f,.Loop = true,.ScaleToTexture = true });
	LeftRender	->CreateAnimation({ .AnimationName = "Idle",.SpriteName = "Wally1_House_Left",.FrameInter = 0.05f,.Loop = true,.ScaleToTexture = true });
	TopRender	->CreateAnimation({ .AnimationName = "Idle",.SpriteName = "Wally1_House_Top",.FrameInter = 0.05f,.Loop = true,.ScaleToTexture = true });

	BackRender	->ChangeAnimation("Idle");
	RightRender	->ChangeAnimation("Idle");
	BottomRender->ChangeAnimation("Idle");
	FrontRender	->ChangeAnimation("Idle");
	LeftRender	->ChangeAnimation("Idle");
	TopRender   ->ChangeAnimation("Idle");


	BackRender	 ->GetTransform()->AddLocalPosition(float4(74, -27));
	BottomRender ->GetTransform()->AddLocalPosition(float4(-30,-120));
	LeftRender	 ->GetTransform()->AddLocalPosition(float4(-78, -49));
	RightRender	 ->GetTransform()->AddLocalPosition(float4(65,-89));
	FrontRender	 ->GetTransform()->AddLocalPosition(float4(-100, -45));
	TopRender	 ->GetTransform()->AddLocalPosition(float4(0, 45));

	Dir[0] = float4::Right;
	Dir[1] = float4::Down;
	Dir[2] = float4(-1, 1); Dir[2].Normalize();
	Dir[3] = float4(1, -1); Dir[3].Normalize();
	Dir[4] = float4::Left;
	Dir[5] = float4(1, 1); Dir[5].Normalize();

}

void Wally1_House_Death::Update(float _DeltaTime)
{
	BackRender	->GetTransform()->AddLocalPosition(Dir[0] * _DeltaTime * MoveSpeed);
	BottomRender->GetTransform()->AddLocalPosition(Dir[1] * _DeltaTime * MoveSpeed);
	LeftRender	->GetTransform()->AddLocalPosition(Dir[2] * _DeltaTime * MoveSpeed);
	RightRender	->GetTransform()->AddLocalPosition(Dir[3] * _DeltaTime * MoveSpeed);
	FrontRender	->GetTransform()->AddLocalPosition(Dir[4] * _DeltaTime * MoveSpeed);
	TopRender   ->GetTransform()->AddLocalPosition(Dir[5] * _DeltaTime * MoveSpeed);

	if (GetLiveTime() > 2.0f)
	{
		Death();
		return;
	}


}
