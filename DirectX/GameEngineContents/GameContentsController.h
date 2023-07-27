#pragma once
#include <GameEnginePlatform/GameEngineSound.h>

// ���� :
class GameContentsController : public GameEngineSound
{
public:

	static float MasterVolume;
	static float FxVolume;
	static float BackGroundVolume;

	// constrcuter destructer
	GameContentsController();
	~GameContentsController();

	// delete Function
	GameContentsController(const GameContentsController& _Other) = delete;
	GameContentsController(GameContentsController&& _Other) noexcept = delete;
	GameContentsController& operator=(const GameContentsController& _Other) = delete;
	GameContentsController& operator=(GameContentsController&& _Other) noexcept = delete;

protected:

private:

};

