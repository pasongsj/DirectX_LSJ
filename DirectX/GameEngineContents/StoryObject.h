#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class StoryObject : public GameEngineActor
{
public:
	// constrcuter destructer
	StoryObject();
	~StoryObject();

	// delete Function
	StoryObject(const StoryObject& _Other) = delete;
	StoryObject(StoryObject&& _Other) noexcept = delete;
	StoryObject& operator=(const StoryObject& _Other) = delete;
	StoryObject& operator=(StoryObject&& _Other) noexcept = delete;

	bool isEnd()
	{
		return isEndStory;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	std::shared_ptr<class GameEngineSpriteRenderer> BackGround = nullptr;
	int Page = 0;
	float WaitingTime = 5.0f;

	bool isEndStory = false;

	void MakeSprite();

	void NextPage();


};

