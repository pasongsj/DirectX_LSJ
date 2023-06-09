#pragma once
#include<GameEngineCore/GameEngineLevel.h>

// ���� :
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

	void MakeSprite();
	void MakeInteractObject();
};

