#pragma once
#include "GameEnemyWeapon.h"

// Ό³Έν :
class Wally1_Feather : public GameEnemyWeapon
{
	friend class Wally1;
public:
	// constrcuter destructer
	Wally1_Feather();
	~Wally1_Feather();

	// delete Function
	Wally1_Feather(const Wally1_Feather& _Other) = delete;
	Wally1_Feather(Wally1_Feather&& _Other) noexcept = delete;
	Wally1_Feather& operator=(const Wally1_Feather& _Other) = delete;
	Wally1_Feather& operator=(Wally1_Feather&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:
	void SetDir(float _degree)
	{
		GetTransform()->SetLocalRotation(float4(0, 0, _degree));
		Dir.RotaitonZDeg(_degree);
	}

	std::shared_ptr<class GameEngineSpriteRenderer> FeatherRender = nullptr;

	float4 Dir = float4::Left;
	float MoveSpeed = 800;

	void MakeSprite();
};

