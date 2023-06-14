#pragma once
#include "GameEngineActor.h"
#include "GameEngineCollision.h"

// Ό³Έν :
class GameEngineUIRenderer;
class GameEngineCollision;
class GameEngineButton : public GameEngineActor
{
public:
	// constrcuter destructer
	GameEngineButton();
	~GameEngineButton();

	// delete Function
	GameEngineButton(const GameEngineButton& _Other) = delete;
	GameEngineButton(GameEngineButton&& _Other) noexcept = delete;
	GameEngineButton& operator=(const GameEngineButton& _Other) = delete;
	GameEngineButton& operator=(GameEngineButton&& _Other) noexcept = delete;

	void SetEvent(std::function<void()> _Click)
	{
		Click = _Click;
	}
	
	void SetButtonRender(const std::string_view& _Name, bool _ScaleToTexture = false);

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineUIRenderer> Render = nullptr;
	std::function<void()> Click;

};

