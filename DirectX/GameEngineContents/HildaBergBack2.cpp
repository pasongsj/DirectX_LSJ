#include "PrecompileHeader.h"
#include "HildaBergBack2.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

HildaBergBack2::HildaBergBack2() 
{
}

HildaBergBack2::~HildaBergBack2() 
{
}


void HildaBergBack2::Start()
{
	float4 WindowSize = GameEngineWindow::GetScreenSize();

	MainBack = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::BackGround);
	MainBack->SetScaleToTexture("blimp_main_ground_0001.png");
	MainBack->GetTransform()->SetLocalPosition(float4(0,-WindowSize.hy()+ MainBack->GetTransform()->GetLocalScale().hy()-15));

	SubBack = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::BackGround);
	SubBack->SetScaleToTexture("blimp_main_ground_0002.png");

	float4 Pos = float4(MainBack->GetTransform()->GetLocalScale().hx() + SubBack->GetTransform()->GetLocalScale().hx(), -WindowSize.hy() + SubBack->GetTransform()->GetLocalScale().hy() - 15);
	SubBack->GetTransform()->SetLocalPosition(Pos);


	GetTransform()->AddLocalPosition(float4(0, 0, 800));

	Interval = 0.0f;
	BackGroundMoveSpeed = 150.0f;

}

void HildaBergBack2::ChangeNight()
{
	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("blimp_main_ground_night_0001.png");

	if ((Tex->GetScale() + float4(0,0,1)) == MainBack->GetTransform()->GetLocalScale())
	{
		MainBack->SetScaleToTexture("blimp_main_ground_night_0001.png");
		SubBack->SetScaleToTexture("blimp_main_ground_night_0002.png");
	}
	else
	{
		MainBack->SetScaleToTexture("blimp_main_ground_night_0002.png");
		SubBack->SetScaleToTexture("blimp_main_ground_night_0001.png");
	}
}