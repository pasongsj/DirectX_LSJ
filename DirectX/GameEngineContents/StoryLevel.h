#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class StoryLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	StoryLevel();
	~StoryLevel();

	// delete Function
	StoryLevel(const StoryLevel& _Other) = delete;
	StoryLevel(StoryLevel&& _Other) noexcept = delete;
	StoryLevel& operator=(const StoryLevel& _Other) = delete;
	StoryLevel& operator=(StoryLevel&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:

	std::shared_ptr<class StoryObject> Story = nullptr;
	std::shared_ptr<class CircleTransEffect> FadeEffect = nullptr;
	float LevelChangeTime = 0.0f;

	GameEngineSoundPlayer BackGroundSound;
};

