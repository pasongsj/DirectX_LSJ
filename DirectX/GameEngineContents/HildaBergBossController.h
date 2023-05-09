#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class HildaBergBossController : public GameEngineActor
{
public:
	// constrcuter destructer
	HildaBergBossController();
	~HildaBergBossController();

	// delete Function
	HildaBergBossController(const HildaBergBossController& _Other) = delete;
	HildaBergBossController(HildaBergBossController&& _Other) noexcept = delete;
	HildaBergBossController& operator=(const HildaBergBossController& _Other) = delete;
	HildaBergBossController& operator=(HildaBergBossController&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	std::shared_ptr<GameEngineActor> Boss = nullptr;
	int Phase = 0;

};

