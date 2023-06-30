#pragma once
#include "GameEnemyWeapon.h"
// Ό³Έν :
class Wally3_Pill_Piece : public GameEnemyWeapon
{
	friend class Wally3_Pill;
public:
	// constrcuter destructer
	Wally3_Pill_Piece();
	~Wally3_Pill_Piece();

	// delete Function
	Wally3_Pill_Piece(const Wally3_Pill_Piece& _Other) = delete;
	Wally3_Pill_Piece(Wally3_Pill_Piece&& _Other) noexcept = delete;
	Wally3_Pill_Piece& operator=(const Wally3_Pill_Piece& _Other) = delete;
	Wally3_Pill_Piece& operator=(Wally3_Pill_Piece&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::map<int, std::string> NextAnimation = { {0,"Blue"},{1,"Yellow"},{2,"DPink"},{3,"LPink"} };
	std::shared_ptr<class GameEngineSpriteRenderer> PillPiece = nullptr;
	float4 Dir = float4::Down;
	float MoveSpeed = 400;
	void Setting(float _Rot, int index);

	void MakeSprite();

};

