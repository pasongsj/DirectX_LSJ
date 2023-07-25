#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class ResultBoard : public GameEngineActor
{
public:
	static float ResultTime;
	static int ResultHPCount;
	static int ResultParryCount;
	static int ResultSuperMeter;
	static int ResultSkillLevel;
	static std::string_view Rank;

	// constrcuter destructer
	ResultBoard();
	~ResultBoard();

	// delete Function
	ResultBoard(const ResultBoard& _Other) = delete;
	ResultBoard(ResultBoard&& _Other) noexcept = delete;
	ResultBoard& operator=(const ResultBoard& _Other) = delete;
	ResultBoard& operator=(ResultBoard&& _Other) noexcept = delete;

	void StopSound()
	{
		ResultSound.Stop();
	}

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

	std::shared_ptr<class GameEngineUIRenderer> RankRender = nullptr;

	float ChangeInterval = 0.3f;
	float CurLocalTime = 0.0f;
	int CurHPCount = 0;
	int CurParryCount = 0;
	int CurSuperMeter = 0;
	int CurSkillLevel = 3;

	int StarIndex = 0;

	bool ShowRank = false;
	bool WinCircle = false;
	bool Banner = false;

	GameEngineSoundPlayer ResultSound;
};

