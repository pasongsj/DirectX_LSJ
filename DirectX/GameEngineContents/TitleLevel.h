#pragma once
#include <GameEngineCore/GameEngineLevel.h>
// ���� :
class TitleLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	TitleLevel();
	~TitleLevel();

	// delete Function
	TitleLevel(const TitleLevel& _Other) = delete;
	TitleLevel(TitleLevel&& _Other) noexcept = delete;
	TitleLevel& operator=(const TitleLevel& _Other) = delete;
	TitleLevel& operator=(TitleLevel&& _Other) noexcept = delete;

protected:
	void Start() override {};
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:

	std::shared_ptr<class GameEngineSpriteRenderer> BackGround = nullptr;
	std::shared_ptr<GameEngineActor> CharUI = nullptr;
	std::shared_ptr<GameEngineActor> BtnUI = nullptr;

	bool isLogoDone = false;
	bool isPressAnyKey = false;

	void MakeSprite();
};

