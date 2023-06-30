#pragma once
#include "GameEnemyWeapon.h"

// Ό³Έν :
class Wally3_Garbages : public GameEnemyWeapon
{
	friend class Wally3;
public:
	// constrcuter destructer
	Wally3_Garbages();
	~Wally3_Garbages();

	// delete Function
	Wally3_Garbages(const Wally3_Garbages& _Other) = delete;
	Wally3_Garbages(Wally3_Garbages&& _Other) noexcept = delete;
	Wally3_Garbages& operator=(const Wally3_Garbages& _Other) = delete;
	Wally3_Garbages& operator=(Wally3_Garbages&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> GarbageRender = nullptr;
	float4 Dir = float4::Up;
	float MoveSpeed = 400.0f;
	void MakeSprite();
	void Setting(int index);

};

