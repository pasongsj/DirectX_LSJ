#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class IntroStoryLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	IntroStoryLevel();
	~IntroStoryLevel();

	// delete Function
	IntroStoryLevel(const IntroStoryLevel& _Other) = delete;
	IntroStoryLevel(IntroStoryLevel&& _Other) noexcept = delete;
	IntroStoryLevel& operator=(const IntroStoryLevel& _Other) = delete;
	IntroStoryLevel& operator=(IntroStoryLevel&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:

};

