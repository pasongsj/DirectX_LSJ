#include "PrecompileHeader.h"
#include "StoryObject.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>

StoryObject::StoryObject() 
{
}

StoryObject::~StoryObject() 
{
}
void StoryObject::MakeSprite()
{
	if (nullptr == GameEngineSprite::Find("story1"))
	{

		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("story\\before");

	
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Page 01-02").GetFullPath(), "story1");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Page 02-03").GetFullPath(), "story2");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Page 03-04").GetFullPath(), "story3");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Page 04-05").GetFullPath(), "story4");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Page 05-06").GetFullPath(), "story5");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Page 06-07").GetFullPath(), "story6");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Page 07-08").GetFullPath(), "story7");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Page 08-09").GetFullPath(), "story8");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Page 09-10").GetFullPath(), "story9");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Page 10-11").GetFullPath(), "story10");
		

	}
}
void StoryObject::Start()
{
	MakeSprite();
	BackGround = CreateComponent<GameEngineSpriteRenderer>();
	BackGround->CreateAnimation({ .AnimationName = "1",  .SpriteName = "story1", .FrameInter = 0.05f, .Loop = false ,.ScaleToTexture  = true });
	BackGround->CreateAnimation({ .AnimationName = "2",  .SpriteName = "story2", .FrameInter = 0.05f, .Loop = false ,.ScaleToTexture  = true });
	BackGround->CreateAnimation({ .AnimationName = "3",  .SpriteName = "story3", .FrameInter = 0.05f, .Loop = false ,.ScaleToTexture  = true });
	BackGround->CreateAnimation({ .AnimationName = "4",  .SpriteName = "story4", .FrameInter = 0.05f, .Loop = false ,.ScaleToTexture  = true });
	BackGround->CreateAnimation({ .AnimationName = "5",  .SpriteName = "story5", .FrameInter = 0.05f, .Loop = false ,.ScaleToTexture  = true });
	BackGround->CreateAnimation({ .AnimationName = "6",  .SpriteName = "story6", .FrameInter = 0.05f, .Loop = false ,.ScaleToTexture  = true });
	BackGround->CreateAnimation({ .AnimationName = "7",  .SpriteName = "story7", .FrameInter = 0.05f, .Loop = false ,.ScaleToTexture  = true });
	BackGround->CreateAnimation({ .AnimationName = "8",  .SpriteName = "story8", .FrameInter = 0.05f, .Loop = false ,.ScaleToTexture  = true });
	BackGround->CreateAnimation({ .AnimationName = "9",  .SpriteName = "story9", .FrameInter = 0.05f, .Loop = false ,.ScaleToTexture  = true });
	BackGround->CreateAnimation({ .AnimationName = "10",  .SpriteName = "story10", .FrameInter = 0.05f, .Loop = false ,.ScaleToTexture = true });
	BackGround->ChangeAnimation("1");

	if (false == GameEngineInput::IsKey("SpaceBar"))
	{
		GameEngineInput::CreateKey("SpaceBar", VK_SPACE);
	}
}

void StoryObject::Update(float _DeltaTime)
{
	WaitingTime -= _DeltaTime;

	if (WaitingTime <= 0 )
	{
		NextPage();
		return;
	}
	if (true == GameEngineInput::IsDown("SpaceBar"))
	{
		NextPage();
		return;
	}
}

void StoryObject::NextPage()
{
	++Page;
	if (Page > 10)
	{
		isEndStory = true;
		return;
	}
	WaitingTime = 10.0f;
	BackGround->ChangeAnimation(std::to_string(Page));
}