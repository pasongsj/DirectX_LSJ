#pragma once
#include<GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class OverWorldLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	OverWorldLevel();
	~OverWorldLevel();

	// delete Function
	OverWorldLevel(const OverWorldLevel& _Other) = delete;
	OverWorldLevel(OverWorldLevel&& _Other) noexcept = delete;
	OverWorldLevel& operator=(const OverWorldLevel& _Other) = delete;
	OverWorldLevel& operator=(OverWorldLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:

	float4 LastPlayerPos = float4::Zero;
	void MakeSprite();
	void MakeInteractObject();

	//std::shared_ptr<class OldFilmEffect> OldFilmEff = nullptr;
	std::shared_ptr<class CircleTransEffect> FadeEffect = nullptr;
	
	GameEngineSoundPlayer BackGroundSound;
};

