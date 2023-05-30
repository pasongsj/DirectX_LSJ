#include "PrecompileHeader.h"
#include "GameEnermyAttack.h"
#include <GameEngineCore/GameEngineCollision.h>
#include "Player.h"

GameEnermyAttack::GameEnermyAttack() 
{
}

GameEnermyAttack::~GameEnermyAttack() 
{
}

bool GameEnermyAttack::CollisionPlayer(std::shared_ptr<class GameEngineCollision> _EnermyCol)
{
	std::shared_ptr<GameEngineCollision> Col = nullptr;
	if (nullptr != (Col = _EnermyCol->Collision(CupHeadCollisionOrder::Player)))
	{
		if (nullptr != Col && false == Col->IsDeath())
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