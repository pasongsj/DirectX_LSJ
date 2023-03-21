#include "PlayLevel.h"
#include "TestRectRotation.h"

PlayLevel::PlayLevel() 
{
}

PlayLevel::~PlayLevel() 
{
}

void PlayLevel::Loading()
{
	std::shared_ptr<TestRectRotation> NewPlayer = CreateActor<TestRectRotation>("TestRectRotation");


}