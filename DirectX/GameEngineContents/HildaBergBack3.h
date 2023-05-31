#pragma once
#include "HildaBergBack.h"
#include <queue>

// Ό³Έν :
class HildaBergBack3 : public HildaBergBack
{
public:
	// constrcuter destructer
	HildaBergBack3();
	~HildaBergBack3();

	// delete Function
	HildaBergBack3(const HildaBergBack3& _Other) = delete;
	HildaBergBack3(HildaBergBack3&& _Other) noexcept = delete;
	HildaBergBack3& operator=(const HildaBergBack3& _Other) = delete;
	HildaBergBack3& operator=(HildaBergBack3&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void ChangeNight() override;

private:
	std::queue< std::shared_ptr<class GameEngineSpriteRenderer>> LargeHill;

	float IntervalX = 0.0f;

	float SettingX = 0.0f;

};

