#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class PigState
{
	WELCOME,
	IDLE,
	CLOCK,
	NOD,
	GOODBYE,
	MAX,
};

// Ό³Έν :
class Shop_Pig : public GameEngineActor
{
public:
	// constrcuter destructer
	Shop_Pig();
	~Shop_Pig();

	// delete Function
	Shop_Pig(const Shop_Pig& _Other) = delete;
	Shop_Pig(Shop_Pig&& _Other) noexcept = delete;
	Shop_Pig& operator=(const Shop_Pig& _Other) = delete;
	Shop_Pig& operator=(Shop_Pig&& _Other) noexcept = delete;
	void SetState(PigState _State);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class ContentsSortRenderer> PigRender = nullptr;
	void MakeSprite();
	bool isWelcomeDone = false;

};

