#include "PrecompileHeader.h"
#include "PlanePlayer.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>

PlanePlayer::PlanePlayer() 
{
}

PlanePlayer::~PlanePlayer() 
{
}

void PlanePlayer::Start()
{

	if (false == GameEngineInput::IsKey("PlayerMoveLeft"))
	{
		GameEngineInput::CreateKey("PlayerMoveLeft", 'A');
		GameEngineInput::CreateKey("PlayerMoveRight", 'D');
		GameEngineInput::CreateKey("PlayerMoveUp", 'W');
		GameEngineInput::CreateKey("PlayerMoveDown", 'S');
	}
	
	Player = CreateComponent<GameEngineRenderer>();
	Player->SetPipeLine("2DTexture");
	Player->GetShaderResHelper().SetTexture("DiffuseTex", "cuphead_plane_idle_straight_0001.png");
	Player->GetTransform()->SetLocalScale({ 100.0f, 100.0f , 100.0f });
}

void PlanePlayer::Update(float _DeltaTime)
{
	float Speed = 500.0f;

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
}

void PlanePlayer::Render(float _DeltaTime)
{
	
}