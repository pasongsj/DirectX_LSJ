#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// ���� :
class ResultLevel : public GameEngineLevel
{
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
	void Start() override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:

};

