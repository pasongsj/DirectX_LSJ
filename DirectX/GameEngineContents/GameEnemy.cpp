#include "PrecompileHeader.h"
#include "GameEnemy.h"
#include "Player.h"
#include <GameEngineCore/GameEngineCollision.h>

GameEnemy::GameEnemy() 
{
}

GameEnemy::~GameEnemy() 
{
}

bool GameEnemy::CollisionPlayer(std::shared_ptr<class GameEngineCollision> _EnermyCol)
{
	std::shared_ptr<GameEngineCollision> Col = nullptr;
	if (nullptr != (Col = _EnermyCol->Collision(CupHeadCollisionOrder::Player)))
	{
		if (false == Col->IsDeath())
		{
			std::shared_ptr<Player> ColActor = Col->GetActor()->DynamicThis<Player>();
			if (nullptr != ColActor)
			{
				ColActor->Attack(1);
				return true;
			}

		}
	}
	return false;
}