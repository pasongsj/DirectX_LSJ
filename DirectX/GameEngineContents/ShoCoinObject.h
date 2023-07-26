#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class ShoCoinObject : public GameEngineActor
{
public:
	// constrcuter destructer
	ShoCoinObject();
	~ShoCoinObject();

	// delete Function
	ShoCoinObject(const ShoCoinObject& _Other) = delete;
	ShoCoinObject(ShoCoinObject&& _Other) noexcept = delete;
	ShoCoinObject& operator=(const ShoCoinObject& _Other) = delete;
	ShoCoinObject& operator=(ShoCoinObject&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineUIRenderer> CoinUI = nullptr;
	std::shared_ptr<class GameEngineUIRenderer> GoldNum = nullptr;
	int CurCoin = 20;

};

