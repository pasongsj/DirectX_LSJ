#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class LoadingLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	LoadingLevel();
	~LoadingLevel();

	// delete Function
	LoadingLevel(const LoadingLevel& _Other) = delete;
	LoadingLevel(LoadingLevel&& _Other) noexcept = delete;
	LoadingLevel& operator=(const LoadingLevel& _Other) = delete;
	LoadingLevel& operator=(LoadingLevel&& _Other) noexcept = delete;

	std::shared_ptr<class FadeEffect> FEffect;


	static void SetLevel(CupheadLevel _Level)
	{
		NextLevel = _Level;
	}


protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:

	float NextLevelTime = 0.0f;
	std::shared_ptr<class GameEngineActor> Glass = nullptr;

	static CupheadLevel NextLevel;
	GameEngineSoundPlayer BackGroundSound;

};
