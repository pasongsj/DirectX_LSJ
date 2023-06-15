#pragma once
#include "GameEnemyWeapon.h"

// Ό³Έν :
class HildaTornado : public GameEnemyWeapon
{
	friend class Hilda;
public:
	// constrcuter destructer
	HildaTornado();
	~HildaTornado();

	// delete Function
	HildaTornado(const HildaTornado& _Other) = delete;
	HildaTornado(HildaTornado&& _Other) noexcept = delete;
	HildaTornado& operator=(const HildaTornado& _Other) = delete;
	HildaTornado& operator=(HildaTornado&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);

private:
	std::shared_ptr<class GameEngineSpriteRenderer> TornatoRender = nullptr;
	std::shared_ptr<class GameEngineCollision> TornatoCollision = nullptr;
	bool isIntro = true;

	float4 TornadoDir = float4::Left;

	float TornadoSpeed = 1000.0f;

	void MakeSprite();

	void SetTornadoDir(float4 _Dir)
	{
		TornadoDir = _Dir;
	}

};

