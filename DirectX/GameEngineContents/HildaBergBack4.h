#pragma once
#include <queue>
#include "HildaBergBack.h"

// Ό³Έν :
class HildaBergBack4 : public HildaBergBack
{
public:
	// constrcuter destructer
	HildaBergBack4();
	~HildaBergBack4();

	// delete Function
	HildaBergBack4(const HildaBergBack4& _Other) = delete;
	HildaBergBack4(HildaBergBack4&& _Other) noexcept = delete;
	HildaBergBack4& operator=(const HildaBergBack4& _Other) = delete;
	HildaBergBack4& operator=(HildaBergBack4&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void ChangeNight() override;

private:
	std::queue<std::shared_ptr<class GameEngineSpriteRenderer>> Clouds;
	float NextStartXPos = 0.0f;

};

