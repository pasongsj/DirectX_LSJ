#include "PrecompileHeader.h"
#include "StoryLevel.h"
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSprite.h>

#include "StoryObject.h"

StoryLevel::StoryLevel() 
{
}

StoryLevel::~StoryLevel() 
{
}

void StoryLevel::Start()
{
	//GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	//GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });
	if (false == GameEngineInput::IsKey("ChangeLevel"))
	{
		GameEngineInput::CreateKey("ChangeLevel", VK_F4);
	}
}
void StoryLevel::Update(float _DeltaTime) 
{
	if (true == Story->isEnd() || true == GameEngineInput::IsDown("ChangeLevel"))
	{
		GameEngineCore::ChangeLevel("OverWorldLevel");
	}
}
	
void StoryLevel::LevelChangeStart()
{
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });

	if (nullptr == GameEngineSprite::Find("story0"))
	{

		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources\\Texture\\story\\before");


		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("Page 00-01").GetFullPath(),"story0");
		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("Page 01-02").GetFullPath(),"story1");
		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("Page 02-03").GetFullPath(),"story2");
		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("Page 03-04").GetFullPath(),"story3");
		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("Page 04-05").GetFullPath(),"story4");
		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("Page 05-06").GetFullPath(),"story5");
		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("Page 06-07").GetFullPath(),"story6");
		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("Page 07-08").GetFullPath(),"story7");
		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("Page 08-09").GetFullPath(),"story8");
		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("Page 09-10").GetFullPath(),"story9");
		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("Page 10-11").GetFullPath(),"story10");


	}

	Story = CreateActor<StoryObject>(CupHeadActorOrder::BackGround);
}
void StoryLevel::LevelChangeEnd()
{
	GameEngineSprite::UnLoad("story0");
	GameEngineSprite::UnLoad("story1");
	GameEngineSprite::UnLoad("story2");
	GameEngineSprite::UnLoad("story3");
	GameEngineSprite::UnLoad("story4");
	GameEngineSprite::UnLoad("story5");
	GameEngineSprite::UnLoad("story6");
	GameEngineSprite::UnLoad("story7");
	GameEngineSprite::UnLoad("story8");
	GameEngineSprite::UnLoad("story9");
	GameEngineSprite::UnLoad("story10");
	Story->Death();
	Story = nullptr;

	AllActorDestroy();
}