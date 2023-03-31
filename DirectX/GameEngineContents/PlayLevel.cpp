#include "PlayLevel.h"
#include "TestRectRotation.h"
#include <GameEngineCore/GameEngineCamera.h>

PlayLevel::PlayLevel() 
{
}

PlayLevel::~PlayLevel() 
{
}

void PlayLevel::Loading()
{
	GetMainCamera()->GetTransform().SetLocalPosition({ 0, 0, -100.0f });

	std::shared_ptr<TestRectRotation> NewPlayer = CreateActor<TestRectRotation>("TestRectRotation");


}