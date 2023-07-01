#pragma once
#include "GameEnemyWeapon.h"

enum class Wally1BulletPos
{
	Top,
	Mid,
	Bot,
};


// Ό³Έν :
class Wally1_Bullet : public GameEnemyWeapon
{
	friend class Wally1;
public:
	// constrcuter destructer
	Wally1_Bullet();
	~Wally1_Bullet();

	// delete Function
	Wally1_Bullet(const Wally1_Bullet& _Other) = delete;
	Wally1_Bullet(Wally1_Bullet&& _Other) noexcept = delete;
	Wally1_Bullet& operator=(const Wally1_Bullet& _Other) = delete;
	Wally1_Bullet& operator=(Wally1_Bullet&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> BulletRender = nullptr;
	std::shared_ptr<class GameEngineCollision> BulletCollision = nullptr;

	void MakeSprite();
	Wally1BulletPos CurPos = Wally1BulletPos::Mid;
	float4 Dir = float4::Left;
	float MoveSpeed = 800;
	bool isShooted = false;

	inline void SetDir(Wally1BulletPos _Pos)
	{
		if (Wally1BulletPos::Top == _Pos)
		{
			GetTransform()->AddLocalRotation(float4(0, 0, -10));
			Dir.RotaitonZDeg(-10);
			//Dir = float4(1, 1).NormalizeReturn();
		}
		else if (Wally1BulletPos::Bot == _Pos)
		{
			Dir.RotaitonZDeg(10);
			GetTransform()->AddLocalRotation(float4(0, 0, 10));
			//Dir = float4(1, -1).NormalizeReturn();
		}
		CurPos = _Pos;
	}



};

