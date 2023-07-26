#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class ResultDeathCupheadCard : public GameEngineActor
{
public:
	// constrcuter destructer
	ResultDeathCupheadCard();
	~ResultDeathCupheadCard();

	// delete Function
	ResultDeathCupheadCard(const ResultDeathCupheadCard& _Other) = delete;
	ResultDeathCupheadCard(ResultDeathCupheadCard&& _Other) noexcept = delete;
	ResultDeathCupheadCard& operator=(const ResultDeathCupheadCard& _Other) = delete;
	ResultDeathCupheadCard& operator=(ResultDeathCupheadCard&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	std::shared_ptr<class GameEngineUIRenderer> CupheadRender = nullptr;

};

