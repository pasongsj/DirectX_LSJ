#pragma once
#include <GameEngineCore/GameEngineActor.h> 

// Ό³Έν :
class shmup_smoke : public GameEngineActor
{
public:
	// constrcuter destructer
	shmup_smoke();
	~shmup_smoke();

	// delete Function
	shmup_smoke(const shmup_smoke& _Other) = delete;
	shmup_smoke(shmup_smoke&& _Other) noexcept = delete;
	shmup_smoke& operator=(const shmup_smoke& _Other) = delete;
	shmup_smoke& operator=(shmup_smoke&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> SmokeRender = nullptr;
	void MakeSprite();
};

