#include "PrecompileHeader.h"
#include "ShopLevel.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

ShopLevel::ShopLevel()
{
}

ShopLevel::~ShopLevel()
{
}
void ShopLevel::MakeSprite()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentResources");
	Dir.Move("ContentResources\\Texture\\Shop");

	if (nullptr == GameEngineSprite::Find("shop-background.png"))
	{
		GameEngineTexture::Load(Dir.GetPlusFileName("shop-background.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("shop_draped_fabric.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("shop_table.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("shop_table_chalkboard.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("shop_chalk_coin.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("shop_drawer_left.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("shop_drawer_right.png").GetFullPath());

	}
}

void ShopLevel::Start()
{
}

void ShopLevel::Update(float _DeltaTime)
{
}


void ShopLevel::LevelChangeStart()
{
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });
	MakeSprite();
	{
		std::shared_ptr<GameEngineActor> BackGround = CreateActor<GameEngineActor>(CupHeadActorOrder::BackGround);
		std::shared_ptr<GameEngineSpriteRenderer> BGRender = BackGround->CreateComponent< GameEngineSpriteRenderer>(CupHeadRendererOrder::BackGround);
		BGRender->SetScaleToTexture("shop-background.png");
		const float4 Shop_BG_Pos = float4{ 0, 180, 2000 };
		BackGround->GetTransform()->SetLocalPosition(Shop_BG_Pos);
	}
	{
		//std::shared_ptr<GameEngineActor> Curtain = CreateActor<GameEngineActor>(CupHeadActorOrder::BackGround);
		//std::shared_ptr<GameEngineSpriteRenderer> CurtainRender = Curtain->CreateComponent< GameEngineSpriteRenderer>(CupHeadRendererOrder::BackGround);
		//BGRender->SetScaleToTexture("shop-background.png");
		//const float4 Shop_BG_Pos = float4{ 0, 180, 2000 };
		//BackGround->GetTransform()->SetLocalPosition(Shop_BG_Pos);
	}
}

void ShopLevel::LevelChangeEnd()
{
}
