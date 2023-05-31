#pragma once
#include <GameEngineCore\GameEngineLevel.h>

// º≥∏Ì :
class HildaBergLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	HildaBergLevel();
	~HildaBergLevel();

	// delete Function
	HildaBergLevel(const HildaBergLevel& _Other) = delete;
	HildaBergLevel(HildaBergLevel&& _Other) noexcept = delete;
	HildaBergLevel& operator=(const HildaBergLevel& _Other) = delete;
	HildaBergLevel& operator=(HildaBergLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:
	// ¿‹√¨¿Ã
	float NextSponeTime = 5.0f;

	// ∫∏Ω∫
	std::shared_ptr<class HildaBoss> Boss = nullptr;
	int Phase = 1;

	// πË∞Ê
	std::vector<std::shared_ptr<class HildaBergBack>> HildaBG;

};

