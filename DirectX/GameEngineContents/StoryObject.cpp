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

void StoryObject::Start()
{
	BackGround = CreateComponent<GameEngineSpriteRenderer>();
	BackGround->CreateAnimation({ .AnimationName = "1",  .TextureName = "book_p1_00", .Start = 0, .End = 24,.InterTime = 0.05f, .Loop = false });
	BackGround->CreateAnimation({ .AnimationName = "2",  .TextureName = "book_p2_00", .Start = 0, .End = 23,.InterTime = 0.05f, .Loop = false });
	BackGround->CreateAnimation({ .AnimationName = "3",  .TextureName = "book_p3_00", .Start = 0, .End = 23,.InterTime = 0.05f, .Loop = false });
	BackGround->CreateAnimation({ .AnimationName = "4",  .TextureName = "book_p4_00", .Start = 0, .End = 23,.InterTime = 0.05f, .Loop = false });
	BackGround->CreateAnimation({ .AnimationName = "5",  .TextureName = "book_p5_00", .Start = 0, .End = 24,.InterTime = 0.05f, .Loop = false });
	BackGround->CreateAnimation({ .AnimationName = "6",  .TextureName = "book_p6_00", .Start = 0, .End = 21,.InterTime = 0.05f, .Loop = false });
	BackGround->CreateAnimation({ .AnimationName = "7",  .TextureName = "book_p7_00", .Start = 0, .End = 23,.InterTime = 0.05f, .Loop = false });
	BackGround->CreateAnimation({ .AnimationName = "8",  .TextureName = "book_p8_00", .Start = 0, .End = 23,.InterTime = 0.05f, .Loop = false });
	BackGround->CreateAnimation({ .AnimationName = "9",  .TextureName = "book_p9_00", .Start = 0, .End = 23,.InterTime = 0.05f, .Loop = false });
	BackGround->CreateAnimation({ .AnimationName = "10",  .TextureName = "book_p10_turn_00", .Start = 0, .End = 23,.InterTime = 0.05f, .Loop = false });
	BackGround->ChangeAnimation("1");

	if (false == GameEngineInput::IsKey("SpaceBar"))
	{
		GameEngineInput::CreateKey("SpaceBar", VK_SPACE);
	}
}
void StoryObject::Update(float _DeltaTime)
{
	if (true == BackGround->IsAnimationEnd())
	{
		WaitingTime -= _DeltaTime;
	}


	if (WaitingTime <= 0 )
	{
		++Page;
		WaitingTime = 5.0f;
		BackGround->ChangeAnimation(std::to_string(Page));
	}
	if (true == GameEngineInput::IsPress("SpaceBar"))
	{
		WaitingTime = 0.0f;
	}
}