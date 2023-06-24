#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class YouDieUI : public GameEngineActor
{
public:
	// constrcuter destructer
	YouDieUI();
	~YouDieUI();

	// delete Function
	YouDieUI(const YouDieUI& _Other) = delete;
	YouDieUI(YouDieUI&& _Other) noexcept = delete;
	YouDieUI& operator=(const YouDieUI& _Other) = delete;
	YouDieUI& operator=(YouDieUI&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineUIRenderer> YouDieRender = nullptr;

};

