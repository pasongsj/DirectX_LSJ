#pragma once
#include "GameEnemyWeapon.h"
// ���� :
class ZepplingBullet : public GameEnemyWeapon
{
	friend class Zeppling;
public:
	// constrcuter destructer
	ZepplingBullet();
	~ZepplingBullet();

	// delete Function
	ZepplingBullet(const ZepplingBullet& _Other) = delete;
	ZepplingBullet(ZepplingBullet&& _Other) noexcept = delete;
	ZepplingBullet& operator=(const ZepplingBullet& _Other) = delete;
	ZepplingBullet& operator=(ZepplingBullet&& _Other) noexcept = delete;


protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTimes) override;


private:
	void SetBulletDir(const float4& _Dir)
	{
		Dir = _Dir;
	}

	void SetPurpleBullet();

	std::shared_ptr<class GameEngineSpriteRenderer> BulletRender = nullptr;
	std::shared_ptr<class GameEngineCollision> BulletCollision = nullptr;
	float BulletSpeed = 400.0f;

	
	float4 Dir = float4::Left;

	void MakeSprite();

};

