#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class HildaBergBack : public GameEngineActor
{
	friend class HildaBergLevel;
public:
	// constrcuter destructer
	HildaBergBack();
	~HildaBergBack();

	// delete Function
	HildaBergBack(const HildaBergBack& _Other) = delete;
	HildaBergBack(HildaBergBack&& _Other) noexcept = delete;
	HildaBergBack& operator=(const HildaBergBack& _Other) = delete;
	HildaBergBack& operator=(HildaBergBack&& _Other) noexcept = delete;

protected:
	virtual void Start() = 0;
	void Update(float _DeltaTime) override;

	std::shared_ptr<class GameEngineSpriteRenderer> MainBack = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> SubBack = nullptr;

	float Interval = 0.0f;
	float BackGroundMoveSpeed = 50.0f;

	virtual void ChangeNight() {};

private:

};

