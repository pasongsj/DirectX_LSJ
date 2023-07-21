#pragma once
#include <GameEngineCore/GameEngineActor.h>
// Ό³Έν :
class Drawer_L : public GameEngineActor
{
	friend class ShopLevel;
public:
	// constrcuter destructer
	Drawer_L();
	~Drawer_L();

	// delete Function
	Drawer_L(const Drawer_L& _Other) = delete;
	Drawer_L(Drawer_L&& _Other) noexcept = delete;
	Drawer_L& operator=(const Drawer_L& _Other) = delete;
	Drawer_L& operator=(Drawer_L&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> DrawerRender = nullptr;
	bool isClosed = false;
	float CloseTimer = 0.0f;
	const float4 StartPos = float4{ -830, -235, 1300 };
	const float4 DestPos = float4{ -320, -235, 1300 };
};

