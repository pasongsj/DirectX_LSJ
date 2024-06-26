#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� :
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

	std::vector<std::shared_ptr<class CardUI>> CardRenders;
	void UpdateCard();


	float4 CardYSize = float4(0, 30);
	int LastInputEnergy = 0;


	void MakeSprite();

	float4 CardSize = float4(20, 30, 1);

};

