#pragma once
#include <GameEngineCore/GameEngineRenderTarget.h>

enum class CircleTransOption
{
	None,
	FadeIn,
	FadeOut,
};
// ���� :
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

	inline void SetFade(CircleTransOption _Option)
	{
		CurState = _Option;
		if (CircleTransOption::FadeIn == _Option)
		{
			TimeData.x = 1.2f;
		}
		else if (CircleTransOption::FadeOut == _Option)
		{
			TimeData.x = 0;
		}
		StateEnd = false;
	}

	inline bool IsEnd()
	{
		return StateEnd;
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

