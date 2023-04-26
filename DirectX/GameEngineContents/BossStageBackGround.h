#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class BossStageBackGround : public GameEngineActor
{
public:
	// constrcuter destructer
	BossStageBackGround();
	~BossStageBackGround();

	// delete Function
	BossStageBackGround(const BossStageBackGround& _Other) = delete;
	BossStageBackGround(BossStageBackGround&& _Other) noexcept = delete;
	BossStageBackGround& operator=(const BossStageBackGround& _Other) = delete;
	BossStageBackGround& operator=(BossStageBackGround&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:

	std::shared_ptr<class GameEngineSpriteRenderer> BackGround;

};

