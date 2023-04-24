#include "PrecompileHeader.h"
#include "ContentsCore.h"
#include <GameEngineCore\GameEngineCore.h>
#include "PlayLevel.h"
#include "TitleLevel.h"
#include "TestLevel.h"

ContentsCore::ContentsCore() 
{
}

ContentsCore::~ContentsCore() 
{
}

void ContentsCore::GameStart() 
{
	// ������ �Ž��� ������� �־�� �Ѵ�.

	new int();

	GameEngineCore::CreateLevel<TitleLevel>();
	//GameEngineCore::CreateLevel<PlayLevel>();
	GameEngineCore::CreateLevel<TestLevel>();
	GameEngineCore::ChangeLevel("TestLevel");
}

void ContentsCore::GameEnd() 
{

}