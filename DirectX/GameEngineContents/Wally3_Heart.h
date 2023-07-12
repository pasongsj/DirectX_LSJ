#pragma once
#include "GameEnemy.h"

// Ό³Έν :
class Wally3_Heart : public GameEnemy
{
	friend class Wally3;
public:
	// constrcuter destructer
	Wally3_Heart();
	~Wally3_Heart();

	// delete Function
	Wally3_Heart(const Wally3_Heart& _Other) = delete;
	Wally3_Heart(Wally3_Heart&& _Other) noexcept = delete;
	Wally3_Heart& operator=(const Wally3_Heart& _Other) = delete;
	Wally3_Heart& operator=(Wally3_Heart&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	
	std::shared_ptr<class GameEngineSpriteRenderer> HeartRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> MouseRender = nullptr;
	std::shared_ptr<class GameEngineCollision> HeartCollision = nullptr;

	float4 Dir = float4::Up;
	float MoveSpeed = 600;
	bool isAttack = false;
	float AttackInterval = 0.0f;

	float4 StartPoint = float4::Zero;

	void MakeSprite();

	void SetStartPosition(const float4& _Pos)
	{
		StartPoint = _Pos;
		GetTransform()->SetLocalPosition(_Pos);
	}
	void ControlAnimation();
};

