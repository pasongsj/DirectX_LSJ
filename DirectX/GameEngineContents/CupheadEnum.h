#pragma once
enum class CupHeadRendererOrder
{
	BackGround,
	Enemy,
	Boss,
	Player,
	UI,
	MAX,
};

enum class CupHeadCollisionOrder
{
	Enemy,
	Player,
	PlayerBullet,
	UI,
	MAX
};