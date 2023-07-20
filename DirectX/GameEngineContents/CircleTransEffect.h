#pragma once
#include <GameEngineCore/GameEngineRenderTarget.h>

enum class CircleTransOption
{
	None,
	FadeIn,
	FadeOut,
};
// Ό³Έν :
class CircleTransEffect : public GameEnginePostProcess
{
public:
	// constrcuter destructer
	CircleTransEffect();
	~CircleTransEffect();

	// delete Function
	CircleTransEffect(const CircleTransEffect& _Other) = delete;
	CircleTransEffect(CircleTransEffect&& _Other) noexcept = delete;
	CircleTransEffect& operator=(const CircleTransEffect& _Other) = delete;
	CircleTransEffect& operator=(CircleTransEffect&& _Other) noexcept = delete;

	void SetFade(CircleTransOption _Option)
	{
		CurState = _Option;
		StateEnd = false;
	}

protected:
	void Start(GameEngineRenderTarget* _Target) override;
	void Effect(GameEngineRenderTarget* _Target, float _DeltaTime) override;


private:
	std::shared_ptr<GameEngineRenderUnit> CircleTransUnit;
	float4 TimeData = float4::Zero;
	float TimeRatio = 1.0f;
	bool StateEnd = false;
	CircleTransOption CurState = CircleTransOption::None;

};

