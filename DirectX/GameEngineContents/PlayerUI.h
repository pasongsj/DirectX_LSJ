#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class PlayerUI : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayerUI();
	~PlayerUI();

	// delete Function
	PlayerUI(const PlayerUI& _Other) = delete;
	PlayerUI(PlayerUI&& _Other) noexcept = delete;
	PlayerUI& operator=(const PlayerUI& _Other) = delete;
	PlayerUI& operator=(PlayerUI&& _Other) noexcept = delete;


protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::map<int, std::shared_ptr<class GameEngineTexture>> HPTexture;
	std::shared_ptr<class GameEngineUIRenderer> HPRender = nullptr;

	int CardCount = 0;
	int CardEnergy = 0;
};

