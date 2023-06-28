#pragma once
#include <GameEngineCore/GameEngineRenderTarget.h>
#include <GameEngineCore/GameEngineSprite.h>

// ī�޶� 1�� ������� ����.
// ���� :
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

	int Index = 0;
};

