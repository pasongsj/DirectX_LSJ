#pragma once
#include <GameEngineCore\GameEngineLevel.h>

// Ό³Έν :
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

private:

};

