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
	Enemy, // �÷��̾�� Ÿ���� ���� �� �ִ� ��ü
	EnemyWeapon, // �÷��̾�� Ÿ���� ���� �ʴ� ��ü -> pink ����
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
