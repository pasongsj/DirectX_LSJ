#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// ���� :
class ShopLevel : public GameEngineLevel
{
	static std::vector<int> SoldInex;
public:
	static int CoinCount;
	// constrcuter destructer
	ShopLevel();
	~ShopLevel();

	// delete Function
	ShopLevel(const ShopLevel& _Other) = delete;
	ShopLevel(ShopLevel&& _Other) noexcept = delete;
	ShopLevel& operator=(const ShopLevel& _Other) = delete;
	ShopLevel& operator=(ShopLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:
	void MakeSprite();

	std::shared_ptr<class Drawer_L> LeftDrawer = nullptr;
	std::shared_ptr<class Shop_Pig> PigActor = nullptr;

	std::shared_ptr<class CircleTransEffect> FadeEffect = nullptr;

	void SetItems();
	std::vector<std::shared_ptr<class ShopItem>> Items;
	int CurItemIndex = 0;
	
	GameEngineSoundPlayer BackGroundSound;

	bool isColsedDone = false;
	void SelectUpdate();
};

