#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class PeaShooter : public GameEngineActor
{
public:
	// constrcuter destructer
	PeaShooter();
	~PeaShooter();

	// delete Function
	PeaShooter(const PeaShooter& _Other) = delete;
	PeaShooter(PeaShooter&& _Other) noexcept = delete;
	PeaShooter& operator=(const PeaShooter& _Other) = delete;
	PeaShooter& operator=(PeaShooter&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	std::shared_ptr <class GameEngineSpriteRenderer > Bullet;

	float ShootSpeed = 1000.0f;

};

