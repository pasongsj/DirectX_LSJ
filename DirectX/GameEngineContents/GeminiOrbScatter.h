#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GeminiOrbScatter : public GameEngineActor
{
public:
	// constrcuter destructer
	GeminiOrbScatter();
	~GeminiOrbScatter();

	// delete Function
	GeminiOrbScatter(const GeminiOrbScatter& _Other) = delete;
	GeminiOrbScatter(GeminiOrbScatter&& _Other) noexcept = delete;
	GeminiOrbScatter& operator=(const GeminiOrbScatter& _Other) = delete;
	GeminiOrbScatter& operator=(GeminiOrbScatter&& _Other) noexcept = delete;

	void SetDir(float4 _Dir)
	{
		Dir = _Dir;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	float4 Dir = float4::Left;
	float ShootSpeed = 1000.0f;

	std::shared_ptr<class GameEngineSpriteRenderer> ScatterRender = nullptr;

	void MakeSprite();

};

