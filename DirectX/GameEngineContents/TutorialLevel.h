#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// ���� :
class TutorialLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	TutorialLevel();
	~TutorialLevel();

	// delete Function
	TutorialLevel(const TutorialLevel& _Other) = delete;
	TutorialLevel(TutorialLevel&& _Other) noexcept = delete;
	TutorialLevel& operator=(const TutorialLevel& _Other) = delete;
	TutorialLevel& operator=(TutorialLevel&& _Other) noexcept = delete;

protected:
	void Start() override {};

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:

	void LoadSprite();
	void UnLoadSprite();

};

