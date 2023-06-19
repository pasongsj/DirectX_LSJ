#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class CardUI : public GameEngineActor
{
	friend class PlayerUI;
public:
	// constrcuter destructer
	CardUI();
	~CardUI();

	// delete Function
	CardUI(const CardUI& _Other) = delete;
	CardUI(CardUI&& _Other) noexcept = delete;
	CardUI& operator=(const CardUI& _Other) = delete;
	CardUI& operator=(CardUI&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	
private:
	bool isFlip = false;
	bool isRot = false;
	int Energy = 0;
	int CardNumber = -1;

	std::shared_ptr<class GameEngineUIRenderer> CardRender = nullptr;
	float4 CardSize = float4(20, 30, 1);

	void MakeSprite();

	void SetEnergy(int _En, bool Rot = false);
};

