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
			GetTransform()->AddLocalScale({ 0.0f, ScaleSpeed * _DeltaTime, 0.0f });
		}
		if (true == GameEngineInput::IsPress("PlayerScaleY-"))
		{
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


	//// 나는 스케일을 1로 고정해 놓는게 좋다.
	// 나는 스케일을 1로 고정해 놓는게 좋다.
	Render0 = CreateComponent<GameEngineRenderer>();
	Render0->SetPipeLine("2DTexture");
	Render0->GetShaderResHelper().SetTexture("DiffuseTex", "Test.png");
	Render0->GetTransform()->SetLocalScale({ 500.0f, 500.0f , 500.0f });


	// 원
	//{
	//	Render0 = CreateComponent<GameEngineRenderer>();
	//	Render0->SetPipeLine("2DTextureCircle");
	//	//Render0->GetShaderResHelper().SetConstantBufferLink("OutPixelColor", float4::White);
	//	Render0->GetTransform()->SetLocalScale({ 50.0f, 50.0f , 50.0f });
	//}

	//큐브
	//{
	//	//Render0 = CreateComponent<GameEngineRenderer>();
	//	//Render0->SetPipeLine("3DTexture");
	//	////Render0->GetShaderResHelper().SetConstantBufferLink("OutPixelColor", float4::White);
	//	//Render0->GetTransform()->SetLocalScale({ 100.0f, 100.0f , 100.0f });
	//	//Render0->GetTransform()->SetLocalRotation(float4(0, 0, 0));

	//	Render1 = CreateComponent<GameEngineRenderer>();
	//	Render1->SetPipeLine("3DTexture");
	//	//Render1->GetShaderResHelper().SetConstantBufferLink("OutPixelColor", float4::Red);
	//	Render1->GetTransform()->SetLocalScale({ 100.0f, 100.0f , 100.0f });
	//	Render1->GetTransform()->SetLocalRotation(float4(0, 0, 0));
	//	Render1->GetTransform()->SetLocalPosition({ -300,0,0 });

	//	Render2 = CreateComponent<GameEngineRenderer>();
	//	Render2->SetPipeLine("3DTexture");
	//	//Render2->GetShaderResHelper().SetConstantBufferLink("OutPixelColor", float4::Green);
	//	Render2->GetTransform()->SetLocalScale({ 100.0f, 100.0f , 100.0f });
	//	Render2->GetTransform()->SetLocalRotation(float4(0, 0, 0));
	//	Render2->GetTransform()->SetLocalPosition({ 300,0,0 });
	//}


	TestColor = { 0.0f, 0.0f, 0.0f, 1.0f };
}

// 이건 디버깅용도나 
void Player::Render(float _Delta) 
{
	// GetTransform()->AddLocalRotation({0.0f, 0.0f, 360.0f * _Delta});
};
