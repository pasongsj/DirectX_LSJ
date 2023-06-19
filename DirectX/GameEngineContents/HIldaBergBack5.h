#pragma once
#include <queue>
#include "HildaBergBack.h"


// Ό³Έν :
class HildaBergBack5 : public HildaBergBack
{
public:
	// constrcuter destructer
	HildaBergBack5();
	~HildaBergBack5();

	// delete Function
	HildaBergBack5(const HildaBergBack5& _Other) = delete;
	HildaBergBack5(HildaBergBack5&& _Other) noexcept = delete;
	HildaBergBack5& operator=(const HildaBergBack5& _Other) = delete;
	HildaBergBack5& operator=(HildaBergBack5&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void ChangeNight() override;

private:
	std::queue<std::shared_ptr<class GameEngineSpriteRenderer>> Clouds;
	float NextStartXPos = 0.0f;
};

