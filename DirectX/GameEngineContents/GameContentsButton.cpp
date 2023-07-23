#include "PrecompileHeader.h"
#include "GameContentsButton.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineUIRenderer.h>

GameContentsButton::GameContentsButton()
{
}

GameContentsButton::~GameContentsButton()
{
}

void GameContentsButton::Start()
{
	Render = CreateComponent<GameEngineUIRenderer>(CupHeadRendererOrder::UI);
	if (false == GameEngineInput::IsKey("EnterKey"))
	{
		GameEngineInput::CreateKey("EnterKey", VK_RETURN);
	}

}
void GameContentsButton::Update(float _Delta)
{
	//float4 Scale = Render->GetTransform()->GetWorldScale();
	//float4 Pos = Render->GetTransform()->GetWorldPosition();

	// 이카메라가 원근 투영이면
	GameEngineCamera* Camera = Render->GetCamera();

	// 랜더러 
	float4x4 ViewPort = Camera->GetViewPort();
	float4x4 Proj = Camera->GetProjection();
	float4x4 View = Camera->GetView();

	float4 Mouse = GameEngineInput::GetMousePosition();

	Mouse *= ViewPort.InverseReturn();
	Mouse *= Proj.InverseReturn();
	Mouse *= View.InverseReturn();


	CollisionData MouseData;
	MouseData.SPHERE.Center = Mouse.DirectFloat3;
	MouseData.SPHERE.Radius = 0.0f;

	if (true == GameEngineTransform::AABB2DToSpehre2D(Render->GetTransform()->GetCollisionData(), MouseData))
	{
		if (HoverImage != "")
		{
			if (true == isScaleToTexture)
			{
				Render->SetScaleToTexture(HoverImage);

			}
			else
			{
				Render->SetTexture(HoverImage);

			}
		}

		if (true == GameEngineInput::IsPress("EngineMouseLeft"))
		{
			if (PressImage != "")
			{
				if (true == isScaleToTexture)
				{
					Render->SetScaleToTexture(PressImage);
				}
				else
				{
					Render->SetTexture(PressImage);

				}
			}
		}

		if (true == GameEngineInput::IsUp("EngineMouseLeft"))
		{
			if (nullptr != Click)
			{
				Click();
			}
		}
	}
	else
	{
		if (true == isHover && HoverImage != "")
		{
			if (true == isScaleToTexture)
			{
				Render->SetScaleToTexture(HoverImage);

			}
			else
			{
				Render->SetTexture(HoverImage);
			}
			if (true == GameEngineInput::IsUp("EnterKey"))
			{
				if (nullptr != Click)
				{
					Click();
				}
			}
		}
		else if (ReleaseImage != "")
		{
			if (true == isScaleToTexture)
			{
				Render->SetScaleToTexture(ReleaseImage);
			}
			else
			{
				Render->SetTexture(ReleaseImage);
			}
		}
	}
}

void GameContentsButton::SetButtonRender(const std::string_view& _Name, bool _ScaleToTexture)
{
	SetReleaseTexture(_Name);
	if (true == _ScaleToTexture)
	{
		Render->SetScaleToTexture(_Name);
	}
	else
	{
		Render->SetTexture(_Name);

	}
}