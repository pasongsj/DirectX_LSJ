#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class ZepplingBullet : public GameEngineActor
{
public:
	// constrcuter destructer
	ZepplingBullet();
	~ZepplingBullet();

	// delete Function
	ZepplingBullet(const ZepplingBullet& _Other) = delete;
	ZepplingBullet(ZepplingBullet&& _Other) noexcept = delete;
	ZepplingBullet& operator=(const ZepplingBullet& _Other) = delete;
	ZepplingBullet& operator=(ZepplingBullet&& _Other) noexcept = delete;

	void SetBulletDir(const float4& _Dir)
	{
		Dir = _Dir;
	}

	void SetPurpleBullet();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTimes) override;


private:
	std::shared_ptr<class GameEngineSpriteRenderer> Bullet = nullptr;
	std::shared_ptr<class GameEngineCollision> BulletCollision = nullptr;
	float BulletSpeed = 400.0f;

	
	float4 Dir = float4::Left;

	void MakeSprite();

};

