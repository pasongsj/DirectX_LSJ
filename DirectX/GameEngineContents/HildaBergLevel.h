#pragma once
#include <GameEngineCore\GameEngineLevel.h>

// ���� :
class HildaBergLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	HildaBergLevel();
	~HildaBergLevel();

	// delete Function
	HildaBergLevel(const HildaBergLevel& _Other) = delete;
	HildaBergLevel(HildaBergLevel&& _Other) noexcept = delete;
	HildaBergLevel& operator=(const HildaBergLevel& _Other) = delete;
	HildaBergLevel& operator=(HildaBergLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:
	// ��ì��
	float NextSponeTime = 5.0f;

	// ����
	std::shared_ptr<class HildaBoss> Boss = nullptr;
	int Phase = 1;
	bool IsConstell = false;
	bool IsGemini = false;
	float4 LastBossPos = float4::Zero;

	// ���
	std::vector<std::shared_ptr<class HildaBergBack>> HildaBG;

	// ����Ʈ
	bool isEffectOn = false;
	std::shared_ptr<class FadeEffect> FEffect = nullptr;
	float EndTime = 0.0f;

	//void ReLoadSprite();

	void UnLoadSprite();

	void BossSetting();

};

