#pragma once
#include <GameEngineCore/GameEngineRenderTarget.h>

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

protected:
	void Start(GameEngineRenderTarget* _Target) override;
	void Effect(GameEngineRenderTarget* _Target, float _DeltaTime) override;


private:
	std::shared_ptr<GameEngineRenderUnit> CircleTransUnit;

};

