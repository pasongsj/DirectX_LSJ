#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class ExBullet : public GameEngineActor
{
	friend class PlayerAirPlaneMode;
public:
	// constrcuter destructer
	ExBullet();
	~ExBullet();

	// delete Function
	ExBullet(const ExBullet& _Other) = delete;
	ExBullet(ExBullet&& _Other) noexcept = delete;
	ExBullet& operator=(const ExBullet& _Other) = delete;
	ExBullet& operator=(ExBullet&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void MakeSprite();
	float4 CollisionSize = float4{ 80,50 };
	float ShootSpeed = 1200.0f;
	int Dmg = 20;

	std::shared_ptr<class GameEngineSpriteRenderer> BulletRender = nullptr;
	std::shared_ptr<class GameEngineCollision> BulletCollision = nullptr;
};

