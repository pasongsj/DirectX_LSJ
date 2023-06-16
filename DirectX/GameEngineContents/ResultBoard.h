#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� :
class ResultBoard : public GameEngineActor
{
public:
	// constrcuter destructer
	ResultBoard();
	~ResultBoard();

	// delete Function
	ResultBoard(const ResultBoard& _Other) = delete;
	ResultBoard(ResultBoard&& _Other) noexcept = delete;
	ResultBoard& operator=(const ResultBoard& _Other) = delete;
	ResultBoard& operator=(ResultBoard&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void MakeSprite();
	std::vector<std::shared_ptr<class GameEngineSpriteRenderer>> RankStars;
};

