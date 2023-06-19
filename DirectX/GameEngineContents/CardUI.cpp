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
		GameEngineSprite::LoadFolder("CharacterBackCard", NewDir.GetPlusFileName("BackCard").GetFullPath().c_str());
		GameEngineSprite::LoadFolder("CharacterFrontCard", NewDir.GetPlusFileName("FrontCard").GetFullPath().c_str());
		GameEngineSprite::LoadFolder("CharacterFlipCard", NewDir.GetPlusFileName("FlipCard").GetFullPath().c_str());
	}
	if (nullptr == GameEngineTexture::Find("hud_ch_card_front.png"))
	{
		GameEngineTexture::Load(NewDir.GetPlusFileName("BackCard\\hud_ch_card_Back.png").GetFullPath());
		GameEngineTexture::Load(NewDir.GetPlusFileName("FrontCard\\hud_ch_card_front.png").GetFullPath());
	}
}

void CardUI::Start()
{
	CardRender = CreateComponent< GameEngineUIRenderer>(CupHeadRendererOrder::UI);
	CardRender->CreateAnimation({ .AnimationName = "RotateCard",  .SpriteName = "CharacterRotateCard", .FrameInter = 0.05f, .Loop = true , .ScaleToTexture = true });
	CardRender->CreateAnimation({ .AnimationName = "FlipCard",  .SpriteName = "CharacterFlipCard" , .FrameInter = 0.05f, .Loop = true , .ScaleToTexture = true });
	CardRender->SetTexture("hud_ch_card_Back.png");
}

void CardUI::Update(float _DeltaTime)
{
	if (true == isFlip && true == CardRender->IsAnimationEnd())
	{
		CardRender->SetScaleToTexture("hud_ch_card_front.png");
		isFlip = false;
	}

}



void CardUI::SetEnergy(int _En, bool Rot)
{
	if (Energy != _En)
	{
		if (_En == 100)
		{
			if (true == Rot && false == isRot)
			{
				CardRender->ChangeAnimation("RotateCard");
				isRot = true;
			}
			else
			{
				CardRender->ChangeAnimation("FlipCard");
				isFlip = true;
			}
		}
		else
		{
			float Rat = static_cast<float>(_En) / 100;
			CardRender->ImageClippingY(Rat, ClipYDir::Top);
			CardRender->GetTransform()->SetLocalScale(float4(CardSize.x, CardSize.y * Rat, 1));
		}
	}
}
