#pragma once
#include "GameEnemyWeapon.h"
#include <map>

enum class EggPiecesPos
{
	Top,
	Mid,
	Bot,
};

// Ό³Έν :
class Wally_Egg_Pieces : public GameEnemyWeapon
{
	friend class WallyEggSpin;
public:
	// constrcuter destructer
	Wally_Egg_Pieces();
	~Wally_Egg_Pieces();

	// delete Function
	Wally_Egg_Pieces(const Wally_Egg_Pieces& _Other) = delete;
	Wally_Egg_Pieces(Wally_Egg_Pieces&& _Other) noexcept = delete;
	Wally_Egg_Pieces& operator=(const Wally_Egg_Pieces& _Other) = delete;
	Wally_Egg_Pieces& operator=(Wally_Egg_Pieces&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;

private:
	inline void SetDir(EggPiecesPos _Pos)
	{
		if (EggPiecesPos::Top == _Pos)
		{
			GetTransform()->AddLocalRotation(float4(0, 0, 30));
			Dir.RotaitonZDeg(30);
			//Dir = float4(1, 1).NormalizeReturn();
		}
		else if (EggPiecesPos::Bot == _Pos)
		{
			Dir.RotaitonZDeg(-30);
			GetTransform()->AddLocalRotation(float4(0, 0, -30));
			//Dir = float4(1, -1).NormalizeReturn();
		}
		CurPos = _Pos;
	}

	std::shared_ptr<class GameEngineSpriteRenderer> PiecesRender = nullptr;
	float MoveSpeed = 800;
	float4 Dir = float4::Right;
	EggPiecesPos CurPos = EggPiecesPos::Mid;
	std::map<int, std::string> AnimationMap = { {1,"A"},{2,"B"},{3,"C"} };

	void MakeSprite();

};

