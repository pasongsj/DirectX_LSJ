#include "PrecompileHeader.h"
#include "CardUI.h"
#include <GameEngineCore/GameEngineUIRenderer.h>

CardUI::CardUI() 
{
}

CardUI::~CardUI() 
{
}
void CardUI::MakeSprite()
{
	GameEngineDirectory NewDir;
	NewDir.MoveParentToDirectory("ContentResources");
	NewDir.Move("ContentResources\\Texture\\PlayerUI");
	if (nullptr == GameEngineSprite::Find("CharacterRotateCard"))
	{
		GameEngineSprite::LoadFolder("CharacterRotateCard", NewDir.GetPlusFileName("RotateCard").GetFullPath().c_str());
		GameEngineSprite::LoadFolder("CharacterFlipCard", NewDir.GetPlusFileName("FlipCard").GetFullPath().c_str());
	}
	if (nullptr == GameEngineTexture::Find("hud_ch_card_Back.png"))
	{
		GameEngineTexture::Load(NewDir.GetPlusFileName("BackCard\\hud_ch_card_Back.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("FrontCard\\hud_ch_card_front.png").GetFullPath());
	}
	else
	{
		GameEngineTexture::ReLoad("hud_ch_card_Back.png");
		GameEngineTexture::ReLoad("hud_ch_card_front.png");
	}
	
	//if (nullptr == GameEngineTexture::Find("hud_ch_card_front.png"))
	//{
	//	GameEngineTexture::Load(NewDir.GetPlusFileName("BackCard\\hud_ch_card_Back.png").GetFullPath());
	//	GameEngineTexture::Load(NewDir.GetPlusFileName("FrontCard\\hud_ch_card_front.png").GetFullPath());
	//}
}

void CardUI::Start()
{
	MakeSprite();
	CardRender = CreateComponent< GameEngineUIRenderer>(CupHeadRendererOrder::UI);
	CardRender->CreateAnimation({ .AnimationName = "RotateCard",  .SpriteName = "CharacterRotateCard", .FrameInter = 0.05f, .Loop = true , .ScaleToTexture = true ,.FrameIndex = {5,6,7,0,1,2,3,4} });
	CardRender->CreateAnimation({ .AnimationName = "FlipCard",  .SpriteName = "CharacterFlipCard" , .FrameInter = 0.05f, .Loop = false , .ScaleToTexture = true });
	CardRender->SetTexture("hud_ch_card_Back.png");
	SetEnergy(0);
}

void CardUI::Update(float _DeltaTime)
{
	if (true == isFlip && true == CardRender->IsAnimationEnd())
	{
		CardRender->SetScaleToTexture("hud_ch_card_front.png");
		isFlip = false;
		isFront = true;
	}

}



void CardUI::SetEnergy(int _En, bool Rot)
{
	if (true == Rot)
	{
		if(false == isRot)
		{
			CardRender->ChangeAnimation("RotateCard");
			CardRender->GetTransform()->SetLocalPosition(Pivot + float4{0, CardSize.hy()});
			CardRender->ImageClippingY(1.0f, ClipYDir::Top);

			isRot = true;
			isFlip = false;
			isFront = true;
		}
	}
	else
	{
		if (_En < 100)
		{
			CardRender->SetTexture("hud_ch_card_Back.png");
			float Rat = static_cast<float>(_En) / 100;
			CardRender->GetTransform()->SetLocalScale(float4{ CardSize.x, CardSize.y * Rat,1 });
			CardRender->GetTransform()->SetLocalPosition(Pivot + float4{0, CardSize.hy() * Rat });
			CardRender->ImageClippingY(Rat, ClipYDir::Top);
			isFront = false;
			isFlip = false;
			isRot = false;

		}
		else if (false == isFront && false == isFlip && _En == 100)
		{
			CardRender->GetTransform()->SetLocalPosition(Pivot + float4{0, CardSize.hy()});
			CardRender->ImageClippingY(1.0f, ClipYDir::Top);
			CardRender->ChangeAnimation("FlipCard");

			isFlip = true;
		}

	}
}
