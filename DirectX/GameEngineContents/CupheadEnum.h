#pragma once
enum class CupHeadRendererOrder
{
	BackGround,
	EnemyEffect,
	Enemy,
	Boss,
	PlayerEffect,
	Player,
	UI,
	MAX,
};

enum class CupHeadCollisionOrder
{
	Enemy,
	EnemyWeapon,
	Player,
	PlayerWepaon,
	UI,
	MAX
};
enum class CupHeadActorOrder
{
	BackGround,
	Boss,
	Enemy,
	PlayerEffect,
	Player,
	UI,
	Camera,
	MAX,
};