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
	ForeGround,
	UI,
	BUTTON,
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
	Enemy, // 플레이어에게 타격을 받을 수 있는 개체
	EnemyWeapon, // 플레이어에게 타격을 받지 않는 개체 -> pink 제외
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
	WALLY,
	OVERWORLD,
	TUTORIAL,
	SHOP,
	RESULT,
	MAX
};
