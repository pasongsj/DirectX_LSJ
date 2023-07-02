#pragma once
#include "GameEnemyWeapon.h"


// Ό³Έν :
class Wally2_Bullet : public GameEnemyWeapon
{
	friend class Wally2;
public:
	// constrcuter destructer
	Wally2_Bullet();
	~Wally2_Bullet();

	// delete Function
	Wally2_Bullet(const Wally2_Bullet& _Other) = delete;
	Wally2_Bullet(Wally2_Bullet&& _Other) noexcept = delete;
	Wally2_Bullet& operator=(const Wally2_Bullet& _Other) = delete;
	Wally2_Bullet& operator=(Wally2_Bullet&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> BulletRender = nullptr;
	std::shared_ptr<class GameEngineCollision> BulletCollision = nullptr;

	float MoveSpeed = 800;
	float4 Dir = float4::Left;

	void MakeSprite();
	void SetPos(const float4& _Pos);
};

