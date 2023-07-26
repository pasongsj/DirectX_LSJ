#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class WallyLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	WallyLevel() ;
	~WallyLevel();

	// delete Function
	WallyLevel(const WallyLevel& _Other) = delete;
	WallyLevel(WallyLevel&& _Other) noexcept = delete;
	WallyLevel& operator=(const WallyLevel& _Other) = delete;
	WallyLevel& operator=(WallyLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:
	//Boss
	int Phase = 1;
	std::shared_ptr<class WallyBoss> Boss = nullptr;
	float4 LastBossPos = float4::Zero;

	//Effect
	std::shared_ptr<class FadeEffect> FEffect = nullptr;
	bool isEffectOn = false;
	// player death
	bool DeathCard = false;
	float EndTimer = 0.0f;

	void BackGroundSetting();
	void BossSetting();

	void EndCheck();
	void UnLoadSprite();

	GameEngineSoundPlayer BackGroundSound;
};

