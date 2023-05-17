#include "PrecompileHeader.h"
#include "IntroStoryLevel.h"
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCore.h>

#include "StoryObject.h"
IntroStoryLevel::IntroStoryLevel() 
{
}

IntroStoryLevel::~IntroStoryLevel() 
{
}

void IntroStoryLevel::Start()
{
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });
}
void IntroStoryLevel::Update(float _DeltaTime) 
{
	if (true == Story->isEnd()) 
	{
		GameEngineCore::ChangeLevel("HildaBergLevel");
	}
}
	
void IntroStoryLevel::LevelChangeStart()
{
	Story = CreateActor<StoryObject>(CupHeadActorOrder::BackGround);
}
void IntroStoryLevel::LevelChangeEnd()
{

}