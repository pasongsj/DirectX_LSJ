#include "PrecompileHeader.h"
#include "Player.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>

Player::Player()
{
}

Player::~Player()
{
}


void Player::Update(float _DeltaTime)
{

	float RotSpeed = 180.0f;

	float Speed = 200.0f;

	if (true == GameEngineInput::IsPress("PlayerSpeedBoost"))
	{
		Speed = 500.0f;
	}

	if (true == GameEngineInput::IsPress("PlayerMoveLeft"))
	{
		GetTransform()->AddLocalPosition(float4::Left * Speed * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("PlayerMoveRight"))
	{
		GetTransform()->AddLocalPosition(float4::Right * Speed * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("PlayerMoveUp"))
	{
		GetTransform()->AddLocalPosition(float4::Up * Speed * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("PlayerMoveDown"))
	{
		GetTransform()->AddLocalPosition(float4::Down * Speed * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("PlayerMoveForward"))
	{
		GetTransform()->AddLocalPosition(GetTransform()->GetLocalForwardVector() * Speed * _DeltaTime);
		// GetTransform()->AddLocalPosition(float4::Forward * Speed * _DeltaTime);
	}
	if (true == GameEngineInput::IsPress("PlayerMoveBack"))
	{
		GetTransform()->AddLocalPosition(float4::Back * Speed * _DeltaTime);
	}

	if (true == GameEngineInput::IsPress("PlayerRotY+"))
	{
		GetTransform()->AddLocalRotation({ 0.0f, RotSpeed * _DeltaTime, 0.0f });
	}
	if (true == GameEngineInput::IsPress("PlayerRotY-"))
	{
		GetTransform()->AddLocalRotation({ 0.0f, -RotSpeed * _DeltaTime, 0.0f });
	}
	if (true == GameEngineInput::IsPress("PlayerRotZ+"))
	{
		GetTransform()->AddLocalRotation({ 0.0f, 0.0f, RotSpeed * _DeltaTime });
	}
	if (true == GameEngineInput::IsPress("PlayerRotZ-"))
	{
		GetTransform()->AddLocalRotation({ 0.0f, 0.0f, -RotSpeed * _DeltaTime });
	}
	if (true == GameEngineInput::IsPress("PlayerRotX+"))
	{
		GetTransform()->AddLocalRotation({ RotSpeed * _DeltaTime, 0.0f, 0.0f });
	}
	if (true == GameEngineInput::IsPress("PlayerRotX-"))
	{
		GetTransform()->AddLocalRotation({ -RotSpeed * _DeltaTime, 0.0f, 0.0f });
	}

	float ScaleSpeed = 10.0f;

	if (true == GameEngineInput::IsPress("PlayerScaleY+"))
	{
		//TestColor.x += _DeltaTime;
		GetTransform()->AddLocalScale({ 0.0f, ScaleSpeed * _DeltaTime, 0.0f });
	}
	if (true == GameEngineInput::IsPress("PlayerScaleY-"))
	{
		//TestColor.x -= _DeltaTime;
		GetTransform()->AddLocalScale({ 0.0f, -ScaleSpeed * _DeltaTime, 0.0f });
	}
	if (true == GameEngineInput::IsPress("PlayerScaleZ+"))
	{
		GetTransform()->AddLocalScale({ 0.0f, 0.0f, ScaleSpeed * _DeltaTime });
	}
	if (true == GameEngineInput::IsPress("PlayerScaleZ-"))
	{
		GetTransform()->AddLocalScale({ 0.0f, 0.0f, -ScaleSpeed * _DeltaTime });
	}
	if (true == GameEngineInput::IsPress("PlayerScaleX+"))
	{
		GetTransform()->AddLocalScale({ ScaleSpeed * _DeltaTime, 0.0f, 0.0f });
	}
	if (true == GameEngineInput::IsPress("PlayerScaleX-"))
	{
		GetTransform()->AddLocalScale({ -ScaleSpeed * _DeltaTime, 0.0f, 0.0f });
	}
	Render0->GetTransform()->SetWorldRotation(float4::Zero);
}

void Player::Start()
{
	if (false == GameEngineInput::IsKey("PlayerMoveLeft"))
	{
		GameEngineInput::CreateKey("PlayerMoveLeft", 'A');
		GameEngineInput::CreateKey("PlayerMoveRight", 'D');
		GameEngineInput::CreateKey("PlayerMoveUp", 'Q');
		GameEngineInput::CreateKey("PlayerMoveDown", 'E');
		GameEngineInput::CreateKey("PlayerMoveForward", 'W');
		GameEngineInput::CreateKey("PlayerMoveBack", 'S');

		GameEngineInput::CreateKey("PlayerScaleY+", 'Y');
		GameEngineInput::CreateKey("PlayerScaleY-", 'U');
		GameEngineInput::CreateKey("PlayerScaleZ+", 'H');
		GameEngineInput::CreateKey("PlayerScaleZ-", 'J');
		GameEngineInput::CreateKey("PlayerScaleX+", 'N');
		GameEngineInput::CreateKey("PlayerScaleX-", 'M');


		GameEngineInput::CreateKey("PlayerRotY+", VK_NUMPAD1);
		GameEngineInput::CreateKey("PlayerRotY-", VK_NUMPAD2);
		GameEngineInput::CreateKey("PlayerRotZ+", VK_NUMPAD4);
		GameEngineInput::CreateKey("PlayerRotZ-", VK_NUMPAD5);
		GameEngineInput::CreateKey("PlayerRotX+", VK_NUMPAD7);
		GameEngineInput::CreateKey("PlayerRotX-", VK_NUMPAD8);
		GameEngineInput::CreateKey("PlayerSpeedBoost", VK_LSHIFT);
	}

	 //큐브
	Render0 = CreateComponent<GameEngineRenderer>();
	Render0->SetPipeLine("3DTexture");
	Render0->GetShaderResHelper().SetConstantBufferLink("OutPixelColor", float4::White);
	Render0->GetTransform()->SetLocalScale({ 100.0f, 100.0f , 100.0f });
	Render0->GetTransform()->SetLocalRotation(float4(0, 0, 0));

	Render1 = CreateComponent<GameEngineRenderer>();
	Render1->SetPipeLine("3DTexture");
	Render1->GetShaderResHelper().SetConstantBufferLink("OutPixelColor", float4::Red);
	Render1->GetTransform()->SetLocalScale({ 100.0f, 100.0f , 100.0f });
	Render1->GetTransform()->SetLocalRotation(float4(0, 0, 0));
	Render1->GetTransform()->SetLocalPosition({ -300,0,0 });

	Render2 = CreateComponent<GameEngineRenderer>();
	Render2->SetPipeLine("3DTexture");
	Render2->GetShaderResHelper().SetConstantBufferLink("OutPixelColor", float4::Green);
	Render2->GetTransform()->SetLocalScale({ 100.0f, 100.0f , 100.0f });
	Render2->GetTransform()->SetLocalRotation(float4(0, 0, 0));
	Render2->GetTransform()->SetLocalPosition({ 300,0,0 });


	//// 사각형
	//Render0 = CreateComponent<GameEngineRenderer>();
	//Render0->SetPipeLine("2DTexture");
	//Render0->GetShaderResHelper().SetConstantBufferLink("OutPixelColor", float4::Black);
	//Render0->GetTransform()->SetLocalScale({ 100.0f, 100.0f , 100.0f });
	//Render0->GetTransform()->SetLocalRotation(float4(0, 0, 0));
	//Render0->GetTransform()->SetLocalPosition({ 0,0,-50 });

	//TestColor = { 0.0f, 0.0f, 0.0f, 1.0f };



	//Render2 = CreateComponent<GameEngineRenderer>();
	//Render2->SetPipeLine("2DTexture");
	//Render2->GetShaderResHelper().SetConstantBufferLink("OutPixelColor", float4::White);
	//Render2->GetTransform()->SetLocalScale({ 100.0f, 100.0f , 100.0f });
	//Render2->GetTransform()->SetLocalRotation(float4(180, 0, 0));
	//Render2->GetTransform()->SetLocalPosition({ 0,0,50 });


	//Render1 = CreateComponent<GameEngineRenderer>();
	//Render1->SetPipeLine("2DTexture");
	//Render1->GetShaderResHelper().SetConstantBufferLink("OutPixelColor", float4::Red);
	//Render1->GetTransform()->SetLocalRotation(float4(90, 0, 0));
	//Render1->GetTransform()->SetLocalScale({ 100.0f, 100.0f , 100.0f });
	//Render1->GetTransform()->SetLocalPosition({ 0,50,0 });

	//Render3 = CreateComponent<GameEngineRenderer>();
	//Render3->SetPipeLine("2DTexture");
	//Render3->GetShaderResHelper().SetConstantBufferLink("OutPixelColor", float4::Green);
	//Render3->GetTransform()->SetLocalScale({ 100.0f, 100.0f , 100.0f });
	//Render3->GetTransform()->SetLocalRotation(float4(-90, 0, 0));
	//Render3->GetTransform()->SetLocalPosition({ 0,-50,0 });

	//Render4 = CreateComponent<GameEngineRenderer>();
	//Render4->SetPipeLine("2DTexture");
	//Render4->GetShaderResHelper().SetConstantBufferLink("OutPixelColor", float4(0.5f, 0, 0.5f, 1.0f));
	//Render4->GetTransform()->SetLocalScale({ 100.0f, 100.0f , 100.0f });
	//Render4->GetTransform()->SetLocalRotation(float4(0, 90, 0));
	//Render4->GetTransform()->SetLocalPosition({ -50,0,0 });

	//Render5 = CreateComponent<GameEngineRenderer>();
	//Render5->SetPipeLine("2DTexture");
	//Render5->GetShaderResHelper().SetConstantBufferLink("OutPixelColor", float4(0.0f, 1.0f, 1.0f, 1.0f));
	//Render5->GetTransform()->SetLocalScale({ 100.0f, 100.0f , 100.0f });
	//Render5->GetTransform()->SetLocalRotation(float4(0, 270, 0));
	//Render5->GetTransform()->SetLocalPosition({ 50,0,0 });
}

// 이건 디버깅용도나 
void Player::Render(float _Delta)
{
	// GetTransform()->AddLocalRotation({0.0f, 0.0f, 360.0f * _Delta});
};
