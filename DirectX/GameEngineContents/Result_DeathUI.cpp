#include "PrecompileHeader.h"
#include "Result_DeathUI.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "GameContentsButton.h"
#include "ResultDeathCupheadCard.h"
#include "LoadingLevel.h"



Result_DeathUI::Result_DeathUI()
{
}

Result_DeathUI::~Result_DeathUI()
{
}

void Result_DeathUI::Start()
{


	GetLevel()->GetCamera(100)->SetSortType(CupHeadRendererOrder::UI, SortType::ZSort);

	BGUI = CreateComponent< GameEngineUIRenderer>(CupHeadRendererOrder::UI);
	BGUI->SetScaleToTexture("Death_Result_BG.png");

	Pivot = GetLevel()->CreateActor< GameEngineActor>(CupHeadRendererOrder::UI);

	CardUI = CreateComponent< GameEngineUIRenderer>(CupHeadRendererOrder::UI);
	CardUI->GetTransform()->SetParent(Pivot->GetTransform());

	RetryBtn = GetLevel()->CreateActor<GameContentsButton>(CupHeadRendererOrder::UI);
	RetryBtn->SetAllButtionTexture({ "RetryButton_release.png" ,"RetryButton_hover.png", "",true });
	RetryBtn->SetName("RetryBtn");
	RetryBtn->GetTransform()->SetParent(Pivot->GetTransform());
	//RetryBtn->GetTransform()->SetLocalRotation(float4{ 0,0, 5 });
	RetryBtn->GetTransform()->SetLocalPosition(float4{ 5,-130,-5 });

	ExitBtn = GetLevel()->CreateActor<GameContentsButton>(CupHeadRendererOrder::UI);
	ExitBtn->SetAllButtionTexture({ "ExitButton_release.png" ,"ExitButton_hover.png", "",true });
	ExitBtn->SetEvent([] {
		LoadingLevel::SetLevel(CupheadLevel::OVERWORLD);
		GameEngineCore::ChangeLevel("LoadingLevel");
		});
	ExitBtn->SetName("ExitBtn");
	ExitBtn->GetTransform()->SetParent(Pivot->GetTransform());
	//ExitBtn->GetTransform()->SetLocalRotation(float4{ 0,0, 5 });
	ExitBtn->GetTransform()->SetLocalPosition(float4{ 5,-170, -5 });


	QuitBtn = GetLevel()->CreateActor<GameContentsButton>(CupHeadRendererOrder::UI);
	QuitBtn->SetAllButtionTexture({ "QuitButton_release.png" ,"QuitButton_hover.png", "",true });
	QuitBtn->SetName("QuitBtn");
	QuitBtn->GetTransform()->SetParent(Pivot->GetTransform());
	QuitBtn->GetTransform()->SetLocalPosition(float4{ 5,-210, -5 });
	QuitBtn->SetEvent([]
		{
		GameEngineWindow::AppOff(); 
		});
	// 
	// 
	Cuphead = GetLevel()->CreateActor< ResultDeathCupheadCard>(CupHeadActorOrder::UI);
	Cuphead->GetTransform()->SetParent(Pivot->GetTransform());
	Pivot->GetTransform()->SetLocalRotation(float4{ 0,0, 5 });


	{
		if (false == GameEngineInput::IsKey("ChangeLevel"))
		{
			GameEngineInput::CreateKey("ChangeLevel", VK_F4);
		}
		if (false == GameEngineInput::IsKey("Up_Buttion"))
		{
			GameEngineInput::CreateKey("Up_Buttion", VK_UP);
		}
		if (false == GameEngineInput::IsKey("Down_Buttion"))
		{
			GameEngineInput::CreateKey("Down_Buttion", VK_DOWN);
		}
	}
	GetTransform()->SetLocalPosition(float4(0, 0, 0));
}

void Result_DeathUI::SetPhase(BossType _Type, int _Phase)
{
	if(BossType::HILDA == _Type)
	{
		switch (_Phase)
		{
		case 2:
			Cuphead->GetTransform()->SetLocalPosition(float4(-200, -40, 0));
			break;
		case 3:
			Cuphead->GetTransform()->SetLocalPosition(float4(-120, -40, 0));
			break;
		case 4:
			Cuphead->GetTransform()->SetLocalPosition(float4(-60, -40, 0));
			break;
		case 5:
			Cuphead->GetTransform()->SetLocalPosition(float4(10, -40, 0));
			break;
		case 6:
			Cuphead->GetTransform()->SetLocalPosition(float4(60, -40, 0));
			break;
		case 7:
			Cuphead->GetTransform()->SetLocalPosition(float4(180, -40, 0));
			break;

		default:
			break;
		}
	}
	else
	{
		switch (_Phase)
		{
		case 2:
			Cuphead->GetTransform()->SetLocalPosition(float4(-200, -40, 0));
			break;
		case 3:
			Cuphead->GetTransform()->SetLocalPosition(float4(-20, -40, 0));
			break;
		case 4:
			Cuphead->GetTransform()->SetLocalPosition(float4(120, -40, 0));

			break;
		default:
			break;
		}
	}

}


void Result_DeathUI::Update(float _DeltaTime)
{

	if (true == GameEngineInput::IsDown("Up_Buttion"))
	{
		if (nullptr == HoverButton)
		{
			HoverButton = RetryBtn;
			HoverButton->SetHover();
			return;
		}
		HoverButton->SetRelease();
		std::string_view NowBtn = HoverButton->GetName();
		if (NowBtn == "RetryBtn")
		{
			HoverButton = QuitBtn;
		}
		else if (NowBtn == "ExitBtn")
		{
			HoverButton = RetryBtn;
		}
		else // NowBtn == "ExitButtion
		{
			HoverButton = ExitBtn;
		}
		HoverButton->SetHover();
	}
	if (true == GameEngineInput::IsDown("Down_Buttion"))
	{
		if (nullptr == HoverButton)
		{
			HoverButton = RetryBtn;
			HoverButton->SetHover();
			return;
		}
		HoverButton->SetRelease();
		std::string_view NowBtn = HoverButton->GetName();
		if (NowBtn == "RetryBtn")
		{
			HoverButton = ExitBtn;
		}
		else if (NowBtn == "ExitBtn")
		{
			HoverButton = QuitBtn;
		}
		else // NowBtn == "ExitButtion
		{
			HoverButton = RetryBtn;
		}
		HoverButton->SetHover();

	}
}


void Result_DeathUI::SetCardUI(const std::string_view _Name)
{
	CardUI->SetScaleToTexture(_Name);

}

void Result_DeathUI::SetReTryBtn(std::function<void()> _Func)
{
	RetryBtn->SetEvent(_Func);
}