#include "PrecompileHeader.h"
#include "ShopLevel.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include "Shop_Pig.h"
#include "Drawer_L.h"

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
	if (false == GameEngineInput::IsKey("PressI"))
	{
		GameEngineInput::CreateKey("PressI", 'I');
	}
}

void ShopLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("PressI"))
	{
		if (nullptr != LeftDrawer)
		{
			LeftDrawer->isClosed = true;
		}
	}
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
		std::shared_ptr<GameEngineActor> Curtain = CreateActor<GameEngineActor>(CupHeadActorOrder::BackGround);
		std::shared_ptr<GameEngineSpriteRenderer> CurtainRender = Curtain->CreateComponent< GameEngineSpriteRenderer>(CupHeadRendererOrder::BackGround);
		CurtainRender->SetScaleToTexture("shop_draped_fabric.png");
		const float4 Shop_Curtain_Pos = float4{ 0, 230, 1900 };
		Curtain->GetTransform()->SetLocalPosition(Shop_Curtain_Pos);
	}

	{
		//shop_table_chalkboard
		std::shared_ptr<GameEngineActor> Board = CreateActor<GameEngineActor>(CupHeadActorOrder::BackGround);
		std::shared_ptr<GameEngineSpriteRenderer> BoardRender = Board->CreateComponent< GameEngineSpriteRenderer>(CupHeadRendererOrder::BackGround);
		BoardRender->SetScaleToTexture("shop_table_chalkboard.png");
		const float4 Shop_Board_Pos = float4{ -320, -240, 1500 };
		Board->GetTransform()->SetLocalPosition(Shop_Board_Pos);
	}

	{
		//shop_drawer_right
		std::shared_ptr<GameEngineActor> Drawer_R = CreateActor<GameEngineActor>(CupHeadActorOrder::BackGround);
		std::shared_ptr<GameEngineSpriteRenderer> DrawerRender = Drawer_R->CreateComponent< GameEngineSpriteRenderer>(CupHeadRendererOrder::BackGround);
		DrawerRender->SetScaleToTexture("shop_drawer_right.png");
		const float4 Shop_Drawer_R_Pos = float4{ 320, -238, 1300 };
		Drawer_R->GetTransform()->SetLocalPosition(Shop_Drawer_R_Pos);
	}

	{
		//shop_drawer_left
		LeftDrawer = CreateActor< Drawer_L>(CupHeadActorOrder::BackGround);
	}

	{
		std::shared_ptr<GameEngineActor> Table = CreateActor<GameEngineActor>(CupHeadActorOrder::BackGround);
		std::shared_ptr<GameEngineSpriteRenderer> TableRender = Table->CreateComponent< GameEngineSpriteRenderer>(CupHeadRendererOrder::BackGround);
		TableRender->SetScaleToTexture("shop_table.png");
		const float4 Shop_Table_Pos = float4{ 0, -220, 1200};
		Table->GetTransform()->SetLocalPosition(Shop_Table_Pos);
	}

	CreateActor<Shop_Pig>(CupHeadActorOrder::BackGround);
}

void ShopLevel::LevelChangeEnd()
{
}
