#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class BossType
{
	HILDA,
	WALLY,
};

// Ό³Έν :
class Result_DeathUI : public GameEngineActor
{
public:
	// constrcuter destructer
	Result_DeathUI();
	~Result_DeathUI();

	// delete Function
	Result_DeathUI(const Result_DeathUI& _Other) = delete;
	Result_DeathUI(Result_DeathUI&& _Other) noexcept = delete;
	Result_DeathUI& operator=(const Result_DeathUI& _Other) = delete;
	Result_DeathUI& operator=(Result_DeathUI&& _Other) noexcept = delete;

	void SetReTryBtn(std::function<void()> _Func);
	void SetCardUI(const std::string_view _Name);
	void SetPhase(BossType _Type, int _Phase);



protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	std::shared_ptr<class GameEngineUIRenderer> BGUI = nullptr;
	std::shared_ptr<class GameEngineUIRenderer> CardUI = nullptr;

	std::shared_ptr<class GameEngineActor> Pivot = nullptr;

	std::shared_ptr<class GameContentsButton> RetryBtn = nullptr;
	std::shared_ptr<class GameContentsButton> ExitBtn = nullptr;
	std::shared_ptr<class GameContentsButton> QuitBtn = nullptr;

	std::shared_ptr<class GameContentsButton> HoverButton = nullptr;

	std::shared_ptr<class ResultDeathCupheadCard> Cuphead = nullptr;

};

