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
		NewDir.Move("ContentResources\\Texture\\story\\before");

	
		GameEngineSprite::LoadFolder("story1" , NewDir.GetPlusFileName("Page 01-02").GetFullPath());
		GameEngineSprite::LoadFolder("story2" , NewDir.GetPlusFileName("Page 02-03").GetFullPath());
		GameEngineSprite::LoadFolder("story3" , NewDir.GetPlusFileName("Page 03-04").GetFullPath());
		GameEngineSprite::LoadFolder("story4" , NewDir.GetPlusFileName("Page 04-05").GetFullPath());
		GameEngineSprite::LoadFolder("story5" , NewDir.GetPlusFileName("Page 05-06").GetFullPath());
		GameEngineSprite::LoadFolder("story6" , NewDir.GetPlusFileName("Page 06-07").GetFullPath());
		GameEngineSprite::LoadFolder("story7" , NewDir.GetPlusFileName("Page 07-08").GetFullPath());
		GameEngineSprite::LoadFolder("story8" , NewDir.GetPlusFileName("Page 08-09").GetFullPath());
		GameEngineSprite::LoadFolder("story9" , NewDir.GetPlusFileName("Page 09-10").GetFullPath());
		GameEngineSprite::LoadFolder("story10" , NewDir.GetPlusFileName("Page 10-11").GetFullPath());
		

	}
}
void StoryObject::Start()
{
	MakeSprite();
	BackGround = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::BackGround);
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