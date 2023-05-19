#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class PlayerAirPlaneSmokeEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayerAirPlaneSmokeEffect();
	~PlayerAirPlaneSmokeEffect();

	// delete Function
	PlayerAirPlaneSmokeEffect(const PlayerAirPlaneSmokeEffect& _Other) = delete;
	PlayerAirPlaneSmokeEffect(PlayerAirPlaneSmokeEffect&& _Other) noexcept = delete;
	PlayerAirPlaneSmokeEffect& operator=(const PlayerAirPlaneSmokeEffect& _Other) = delete;
	PlayerAirPlaneSmokeEffect& operator=(PlayerAirPlaneSmokeEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	std::shared_ptr<class GameEngineSpriteRenderer> Smoke = nullptr;
	float MoveSpeed = 100;

	void MakeSprite();

};

