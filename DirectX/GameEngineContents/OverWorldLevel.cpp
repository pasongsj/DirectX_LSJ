#include "PrecompileHeader.h"
#include "OverWorldLevel.h"

#include "OverWorldBack.h"
#include "PlayerOverWorldMode.h"
#include <GameEngineCore/GameEngineSprite.h>

OverWorldLevel::OverWorldLevel() 
{
}

OverWorldLevel::~OverWorldLevel() 
{
}

void OverWorldLevel::MakeSprite()
{
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources\\Texture\\stage1\\Overworld");

		// Texture
		if (nullptr == GameEngineTexture::Find("Overworld_Map.png"))
		{
			GameEngineTexture::Load(Dir.GetPlusFileName("Overworld_Map.png").GetFullPath());
			GameEngineTexture::Load(Dir.GetPlusFileName("Overworld_ColMap.png").GetFullPath());
		}
		else
		{
			GameEngineTexture::ReLoad("Overworld_Map.png");
			GameEngineTexture::ReLoad("Overworld_ColMap.png");
		}

		// Sprite
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources\\Texture\\Cuphead_Overworld");


		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Diag_Down_Idle").GetFullPath(),"Diag_Down_Idle");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Diag_Down_Move").GetFullPath(),"Diag_Down_Move");

		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Diag_Up_Idle").GetFullPath(),"Diag_Up_Idle");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Diag_Up_Move").GetFullPath(),"Diag_Up_Move");

		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Down_Idle").GetFullPath(),"Down_Idle");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Down_Move").GetFullPath(),"Down_Move");

		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Side_Idle").GetFullPath(),"Side_Idle");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Side_Move").GetFullPath(),"Side_Move");

		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Up_Idle").GetFullPath(),"Up_Idle");
		GameEngineSprite::ReLoad(Dir.GetPlusFileName("Up_Move").GetFullPath(),"Up_Move");

		GameEngineSprite::ReLoad(Dir.GetPlusFileName("InterAction_Win").GetFullPath(),"InterAction_Win");
	}

}


void OverWorldLevel::Start()
{

}

void OverWorldLevel::Update(float _DeltaTime)
{

}

void OverWorldLevel::LevelChangeStart()
{
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });
	MakeSprite();
	CreateActor<OverWorldBack>(CupHeadActorOrder::BackGround);
	CreateActor<PlayerOverWorldMode>(CupHeadActorOrder::Player);
}
void OverWorldLevel::LevelChangeEnd()
{
	AllActorDestroy();

	GameEngineTexture::UnLoad("Overworld_Map.png");
	GameEngineTexture::UnLoad("Overworld_ColMap.png");
}