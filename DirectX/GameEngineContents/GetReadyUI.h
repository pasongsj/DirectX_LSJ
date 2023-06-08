#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GetReadyUI : public GameEngineActor
{
public:
	// constrcuter destructer
	GetReadyUI();
	~GetReadyUI();

	// delete Function
	GetReadyUI(const GetReadyUI& _Other) = delete;
	GetReadyUI(GetReadyUI&& _Other) noexcept = delete;
	GetReadyUI& operator=(const GetReadyUI& _Other) = delete;
	GetReadyUI& operator=(GetReadyUI&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineUIRenderer> GetReadyRender = nullptr;


};

