#pragma once
#include "GameEnemy.h"
#include <map>

enum class EggPiecesPos
{
	Top,
	Mid,
	Bot,
};

// Ό³Έν :
class Wally1_Egg_Pieces : public GameEnemy
{
	friend class Wally1_Egg_Spin;
public:
	// constrcuter destructer
	Wally1_Egg_Pieces();
	~Wally1_Egg_Pieces();

	// delete Function
	Wally1_Egg_Pieces(const Wally1_Egg_Pieces& _Other) = delete;
	Wally1_Egg_Pieces(Wally1_Egg_Pieces&& _Other) noexcept = delete;
	Wally1_Egg_Pieces& operator=(const Wally1_Egg_Pieces& _Other) = delete;
	Wally1_Egg_Pieces& operator=(Wally1_Egg_Pieces&& _Other) noexcept = delete;

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
			Dir.z = 0;
			//Dir = float4(1, 1).NormalizeReturn();
		}
		else if (EggPiecesPos::Bot == _Pos)
		{
			Dir.RotaitonZDeg(-30);
			GetTransform()->AddLocalRotation(float4(0, 0, -30));
			Dir.z = 0;
			//Dir = float4(1, -1).NormalizeReturn();
		}
		CurPos = _Pos;
	}

	std::shared_ptr<class GameEngineSpriteRenderer> PiecesRender = nullptr;
	std::shared_ptr<class GameEngineCollision> PiecesCollision = nullptr;
	float MoveSpeed = 800;
	float4 Dir = float4::Right;
	EggPiecesPos CurPos = EggPiecesPos::Mid;
	std::map<int, std::string> AnimationMap = { {1,"A"},{2,"B"},{3,"C"} };

	void MakeSprite();

};

