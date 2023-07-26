#pragma once

// Ό³Έν :
class ItemEffect
{
public:

	static int MAXHP;
	static bool COFFEE;
	static float DMGPERC;

	// constrcuter destructer
	ItemEffect();
	~ItemEffect();

	// delete Function
	ItemEffect(const ItemEffect& _Other) = delete;
	ItemEffect(ItemEffect&& _Other) noexcept = delete;
	ItemEffect& operator=(const ItemEffect& _Other) = delete;
	ItemEffect& operator=(ItemEffect&& _Other) noexcept = delete;

protected:

private:

};

