#pragma once
enum class CupHeadRendererOrder
{
	BackGround,
	BossBack,
	Boss,
	Enemy,
	EnemyWeapon,
	EnemyEffect,
	PlayerBackGround,
	Player,
	PlayerWepaon,
	PlayerEffect,
	UI,
	MAX,
};

enum class CupHeadActorOrder
{
	BackGround,
	Boss,
	Enemy,
	EnemyWeapon,
	EnemyEffect,
	PlayerBackGround,
	Player,
	PlayerWepaon,
	PlayerEffect,
	UI,
	Camera,
	MAX,
};
enum class CupHeadCollisionOrder
{
	Enemy,
	EnemyWeapon,
	Player,
	PlayerWepaon,
	UI,
	MAX,

};

enum class CupheadLevel
{
	NONE,
	STORY,
	HILDA,
	MAX
};