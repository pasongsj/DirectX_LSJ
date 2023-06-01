#pragma once
enum class CupHeadRendererOrder
{
	BackGround,
	EnemyEffect,
	Enemy,
	Boss,
	Player,
	PlayerEffect,
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
	EnemyEffect,
	Player,
	PlayerEffect,
	UI,
	Camera,
	MAX,
};