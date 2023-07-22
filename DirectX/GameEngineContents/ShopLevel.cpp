#include "PrecompileHeader.h"
#include "ShopLevel.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>

#include "Shop_Pig.h"
#include "Drawer_L.h"
#include "ShopItem.h"

//effect
#include "OldFilmEffect.h"
#include "CircleTransEffect.h"

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

	if (nullptr == GameEngineTexture::Find("shop-background.png"))
	{
		GameEngineTexture::Load(Dir.GetPlusFileName("shop-background.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("shop_draped_fabric.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("shop_table.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("shop_table_chalkboard.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("shop_chalk_coin.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("shop_drawer_left.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("shop_drawer_right.png").GetFullPath());
	}
	else
	{
		GameEngineTexture::ReLoad("shop-background.png");
		GameEngineTexture::ReLoad("shop_draped_fabric.png");
		GameEngineTexture::ReLoad("shop_table.png");
		GameEngineTexture::ReLoad("shop_table_chalkboard.png");
		GameEngineTexture::ReLoad("shop_chalk_coin.png");
		GameEngineTexture::ReLoad("shop_drawer_left.png");
		GameEngineTexture::ReLoad("shop_drawer_right.png");
	}

	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Items\\Coffee\\glow").GetFullPath(), "Item_Coffee_Glow");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Items\\Coffee\\dim").GetFullPath(), "Item_Coffee_Dim");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Items\\Coffee\\sold").GetFullPath(), "Item_Coffee_Sold");

	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Items\\Hp1\\glow").GetFullPath(), "Item_Hp1_Glow");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Items\\Hp1\\dim").GetFullPath(), "Item_Hp1_Dim");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Items\\Hp1\\sold").GetFullPath(), "Item_Hp1_Sold");
	
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Items\\Hp2\\glow").GetFullPath(), "Item_Hp2_Glow");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Items\\Hp2\\dim").GetFullPath(), "Item_Hp2_Dim");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("Items\\Hp2\\sold").GetFullPath(), "Item_Hp2_Sold");

}

void ShopLevel::Start()
{
	GetLastTarget()->CreateEffect<OldFilmEffect>();
	FadeEffect = GetLastTarget()->CreateEffect<CircleTransEffect>();

	if (false == GameEngineInput::IsKey("PressI"))
	{
		GameEngineInput::CreateKey("PressI", 'I');
	}
	if (false == GameEngineInput::IsKey("Left_Buttion"))
	{
		GameEngineInput::CreateKey("Left_Buttion", VK_LEFT);
	}
	if (false == GameEngineInput::IsKey("Right_Buttion"))
	{
		GameEngineInput::CreateKey("Right_Buttion", VK_RIGHT);
	}
	if (false == GameEngineInput::IsKey("ESC_Buttion"))
	{
		GameEngineInput::CreateKey("ESC_Buttion", VK_ESCAPE);
	}
}

void ShopLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("ESC_Buttion"))
	{
		if (nullptr != LeftDrawer && nullptr != PigActor)
		{
			PigActor->SetState(PigState::GOODBYE);
			LeftDrawer->isClosed = true;
			FadeEffect->SetFade(CircleTransOption::FadeIn);
		}
	}
	if (nullptr != LeftDrawer && LeftDrawer->CloseTimer > 1.0f)
	{
		GameEngineCore::ChangeLevel("OverWorldLevel");
	}

	if (true == GameEngineInput::IsDown("PressI"))
	{
	}
	if (true == GameEngineInput::IsUp("Left_Buttion"))
	{
		if (CurItemIndex <= 0)
		{
			return;
		}
		else
		{
			Items[CurItemIndex--]->SetState(ItemState::DIM);
			Items[CurItemIndex]->SetState(ItemState::GLOW);
		}
	}

	if (true == GameEngineInput::IsUp("Right_Buttion"))
	{
		if (CurItemIndex >= Items.size()-1)
		{
			return;
		}
		else
		{
			Items[CurItemIndex++]->SetState(ItemState::DIM);
			Items[CurItemIndex]->SetState(ItemState::GLOW);
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

	PigActor = CreateActor<Shop_Pig>(CupHeadActorOrder::BackGround);
	SetItems();
	FadeEffect->SetFade(CircleTransOption::FadeOut);

}

void ShopLevel::LevelChangeEnd()
{
	LeftDrawer = nullptr;
	PigActor = nullptr;
	Items.clear();
	AllActorDestroy();


	GameEngineTexture::UnLoad("shop-background.png");
	GameEngineTexture::UnLoad("shop_draped_fabric.png");
	GameEngineTexture::UnLoad("shop_table.png");
	GameEngineTexture::UnLoad("shop_table_chalkboard.png");
	GameEngineTexture::UnLoad("shop_chalk_coin.png");
	GameEngineTexture::UnLoad("shop_drawer_left.png");
	GameEngineTexture::UnLoad("shop_drawer_right.png");

	GameEngineSprite::UnLoad("Item_Coffee_Glow");
	GameEngineSprite::UnLoad("Item_Coffee_Dim");
	GameEngineSprite::UnLoad("Item_Coffee_Sold");
							
	GameEngineSprite::UnLoad("Item_Hp1_Glow");
	GameEngineSprite::UnLoad("Item_Hp1_Dim");
	GameEngineSprite::UnLoad("Item_Hp1_Sold");
							
	GameEngineSprite::UnLoad("Item_Hp2_Glow");
	GameEngineSprite::UnLoad("Item_Hp2_Dim");
	GameEngineSprite::UnLoad("Item_Hp2_Sold");
}


void ShopLevel::SetItems()
{
	const float4 ItemPos1 = float4{ -500, 0, 1000 };
	const float4 ItemPos2 = float4{ -430, 20, 900 };
	const float4 ItemPos3 = float4{ -360, 30, 1000 };
	Items.resize(3);
	std::string glow = std::to_string(static_cast<int>(ItemState::GLOW));
	std::string dim = std::to_string(static_cast<int>(ItemState::DIM));
	std::string sold = std::to_string(static_cast<int>(ItemState::SOLD));
	{
		std::shared_ptr< ShopItem> Item = CreateActor< ShopItem>(CupHeadActorOrder::PlayerBackGround);
		Item->GetItemRender()->CreateAnimation({ .AnimationName = glow,.SpriteName = "Item_Coffee_Glow",.FrameInter = 0.1f,.Loop = true, .ScaleToTexture = true});
		Item->GetItemRender()->CreateAnimation({ .AnimationName = dim,.SpriteName = "Item_Coffee_Dim",.FrameInter = 0.1f,.Loop = false, .ScaleToTexture = true });
		Item->GetItemRender()->CreateAnimation({ .AnimationName = sold,.SpriteName = "Item_Coffee_Sold",.FrameInter = 0.1f,.Loop = false, .ScaleToTexture = true });
		Item->SetState(ItemState::DIM);
		Item->GetTransform()->SetLocalPosition(ItemPos1);
		Items[0] = Item;
	}
	{
		std::shared_ptr< ShopItem> Item = CreateActor< ShopItem>(CupHeadActorOrder::PlayerBackGround);
		Item->GetItemRender()->CreateAnimation({ .AnimationName = glow,.SpriteName = "Item_Hp2_Glow",.FrameInter = 0.1f,.Loop = true, .ScaleToTexture = true });
		Item->GetItemRender()->CreateAnimation({ .AnimationName = dim,.SpriteName = "Item_Hp2_Dim",.FrameInter = 0.1f,.Loop = false, .ScaleToTexture = true });
		Item->GetItemRender()->CreateAnimation({ .AnimationName = sold,.SpriteName = "Item_Hp2_Sold",.FrameInter = 0.1f,.Loop = false, .ScaleToTexture = true });
		Item->SetState(ItemState::DIM);
		Item->GetTransform()->SetLocalPosition(ItemPos3);
		Items[2] = Item;

	}
	{
		std::shared_ptr< ShopItem> Item = CreateActor< ShopItem>(CupHeadActorOrder::PlayerBackGround);
		Item->GetItemRender()->CreateAnimation({ .AnimationName = glow,.SpriteName = "Item_Hp1_Glow",.FrameInter = 0.1f,.Loop = true, .ScaleToTexture = true });
		Item->GetItemRender()->CreateAnimation({ .AnimationName = dim,.SpriteName = "Item_Hp1_Dim",.FrameInter = 0.1f,.Loop = false, .ScaleToTexture = true });
		Item->GetItemRender()->CreateAnimation({ .AnimationName = sold,.SpriteName = "Item_Hp1_Sold",.FrameInter = 0.1f,.Loop = false, .ScaleToTexture = true });
		Item->SetState(ItemState::DIM);
		Item->GetTransform()->SetLocalPosition(ItemPos2);
		Items[1] = Item;

	}
	Items[CurItemIndex]->SetState(ItemState::GLOW);
}


