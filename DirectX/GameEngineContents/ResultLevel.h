#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class ResultLevel : public GameEngineLevel
{
	friend class ResultBoard;
public:
	// constrcuter destructer
	ResultLevel();
	~ResultLevel();

	// delete Function
	ResultLevel(const ResultLevel& _Other) = delete;
	ResultLevel(ResultLevel&& _Other) noexcept = delete;
	ResultLevel& operator=(const ResultLevel& _Other) = delete;
	ResultLevel& operator=(ResultLevel&& _Other) noexcept = delete;

protected:
	void Start() override {};
	void Update(float _DeltaTime) override;


	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:

	void MakeSprite();

	std::shared_ptr<class FadeEffect> FadeOutEffect = nullptr;
	std::shared_ptr<class CircleTransEffect> FadeInEffect = nullptr;

	float LevelChangeTimer = 0.0f;
	bool didFadein = false;

};

