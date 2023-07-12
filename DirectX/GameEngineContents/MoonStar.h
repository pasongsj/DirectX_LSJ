#pragma once
#include "GameEnemy.h"

// Ό³Έν :
class MoonStar : public GameEnemy
{
	friend class Moon;
public:
	// constrcuter destructer
	MoonStar();
	~MoonStar();

	// delete Function
	MoonStar(const MoonStar& _Other) = delete;
	MoonStar(MoonStar&& _Other) noexcept = delete;
	MoonStar& operator=(const MoonStar& _Other) = delete;
	MoonStar& operator=(MoonStar&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> StarRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> FxRender = nullptr;
	std::shared_ptr<class GameEngineCollision> StarCollision = nullptr;

	float StarSpeed = 600;

	float4 StartPos = float4::Zero;

	void StarMove(float _DeltaTime);

	void MakeSprite();

	void SettingType();

	std::map<int, std::string> AniType = { {0,"A"},{1,"B"},{2,"C"},{3,"Pink"} };
};
