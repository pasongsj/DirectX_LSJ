#include "PrecompileHeader.h"
#include "IntroStoryLevel.h"
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEnginePlatform/GameEngineInput.h>

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
	if (false == GameEngineInput::IsKey("ChangeLevel"))
	{
		GameEngineInput::CreateKey("ChangeLevel", VK_F4);
	}
}
void IntroStoryLevel::Update(float _DeltaTime) 
{
	if (true == Story->isEnd()) 
	{
		GameEngineCore::ChangeLevel("LoadingLevel");
	}
	if (true == GameEngineInput::IsDown("ChangeLevel"))
	{
		GameEngineCore::ChangeLevel("LoadingLevel");
	}
}
	
void IntroStoryLevel::LevelChangeStart()
{
	Story = CreateActor<StoryObject>(CupHeadActorOrder::BackGround);
}
void IntroStoryLevel::LevelChangeEnd()
{
	Story->Death();
	Story = nullptr;
}