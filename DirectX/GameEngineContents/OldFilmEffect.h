#pragma once
#include <GameEngineCore/GameEngineRenderTarget.h>
#include <GameEngineCore/GameEngineSprite.h>

// 카메라를 1개 더만들고 말지.
// 설명 :
class OldFilmEffect : public GameEnginePostProcess
{
public:
	// constrcuter destructer
	OldFilmEffect();
	~OldFilmEffect();

	// delete Function
	OldFilmEffect(const OldFilmEffect& _Other) = delete;
	OldFilmEffect(OldFilmEffect&& _Other) noexcept = delete;
	OldFilmEffect& operator=(const OldFilmEffect& _Other) = delete;
	OldFilmEffect& operator=(OldFilmEffect&& _Other) noexcept = delete;

protected:
	void Start(GameEngineRenderTarget* _Target) override;
	void Effect(GameEngineRenderTarget* _Target, float _DeltaTime) override;

private:
	std::shared_ptr<GameEngineRenderUnit> OldUnit;
	std::shared_ptr<GameEngineSprite> OldSprite;

	float4 OldData;

	float FilmTimer = 0.0f;
	float FilmInterval = 0.05f;

	int Index = 0;
};

