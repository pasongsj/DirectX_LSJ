#pragma once
#include "GameEnemyWeapon.h"

// Ό³Έν :
class FlappyBird : public GameEnemyWeapon
{
	friend class Wally1;
public:
	// constrcuter destructer
	FlappyBird();
	~FlappyBird();

	// delete Function
	FlappyBird(const FlappyBird& _Other) = delete;
	FlappyBird(FlappyBird&& _Other) noexcept = delete;
	FlappyBird& operator=(const FlappyBird& _Other) = delete;
	FlappyBird& operator=(FlappyBird&& _Other) noexcept = delete;


protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> BirdRender = nullptr;
	std::shared_ptr<class GameEngineCollision> BirdCollision = nullptr;

	bool isDeathAnimation = false;
	float MoveSpeed = 300;
	float4 StartPoint = float4::Zero;
	float MoveDuration = 0.0f;
	void MakeSprite();
	void SetPink();
	void SetStartPosition(const float4& _Pos)
	{
		StartPoint = _Pos;
		GetTransform()->SetLocalPosition(_Pos);
	}


};

