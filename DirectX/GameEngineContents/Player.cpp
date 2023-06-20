#include "PrecompileHeader.h"
#include "Player.h"
#include <GameEnginePlatform/GameEngineInput.h>

Player* Player::MainPlayer = nullptr;

Player::Player() 
{
}

Player::~Player() 
{
}

void Player::Start()
{
	if (false == GameEngineInput::IsKey("PlayerAirPlaneMoveLeft"))
	{
		GameEngineInput::CreateKey("PlayerAirPlaneMoveLeft", VK_LEFT);
		GameEngineInput::CreateKey("PlayerAirPlaneMoveRight", VK_RIGHT);
		GameEngineInput::CreateKey("PlayerAirPlaneMoveUp", VK_UP);
		GameEngineInput::CreateKey("PlayerAirPlaneMoveDown", VK_DOWN);
		GameEngineInput::CreateKey("PlayerAirPlaneParry", 'Z');
		GameEngineInput::CreateKey("PlayerShmupSkill", 'V');
		GameEngineInput::CreateKey("PlayerAttack", 'X');
		GameEngineInput::CreateKey("PlayerShmUpModeSwitch", VK_SPACE);
		GameEngineInput::CreateKey("PlayerOriginMode", VK_NUMPAD1);
		GameEngineInput::CreateKey("PlayerShmUpMode", VK_NUMPAD2);
		GameEngineInput::CreateKey("PlayerShrinkMode", VK_SHIFT);
	}
}