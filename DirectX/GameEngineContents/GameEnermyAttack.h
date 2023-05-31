#pragma once
#include <GameEngineCore/GameEngineActor.h>
// ���� :
class GameEnermyAttack : public GameEngineActor
{
public:
	// constrcuter destructer
	GameEnermyAttack();
	~GameEnermyAttack();

	// delete Function
	GameEnermyAttack(const GameEnermyAttack& _Other) = delete;
	GameEnermyAttack(GameEnermyAttack&& _Other) noexcept = delete;
	GameEnermyAttack& operator=(const GameEnermyAttack& _Other) = delete;
	GameEnermyAttack& operator=(GameEnermyAttack&& _Other) noexcept = delete;

	bool CollisionPlayer(std::shared_ptr<class GameEngineCollision> _EnermyCol);

	bool IsPink()
	{
		return Pink;
	}

protected:

	bool Pink = false; // �и����� ��ü
private:

};

