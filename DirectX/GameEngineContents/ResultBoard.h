#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class ResultBoard : public GameEngineActor
{
public:
	static float Time;
	static int HPCount;
	static int ParryCount;
	static int SuperMeter;
	static int SkillLevel;
	static std::string_view Rank;

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
	std::shared_ptr<class NumberRenderObject> TimeMinRender = nullptr;
	std::shared_ptr<class NumberRenderObject> TimeSecRender = nullptr;
	std::shared_ptr<class NumberRenderObject> HPRender = nullptr;
	std::shared_ptr<class NumberRenderObject> ParryRender = nullptr;
	std::shared_ptr<class NumberRenderObject> SuperMeterRender = nullptr;

};

