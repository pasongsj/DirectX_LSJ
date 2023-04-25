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

void ContentsCore::ContentsResourcesCreate()
{
	// �ؽ�ó �ε常 �� �������� �ϵ��� ��


}

void ContentsCore::GameStart() 
{
	// ������ �Ž��� ������� �־�� �Ѵ�.

	new int();

	ContentsResourcesCreate();

	GameEngineCore::CreateLevel<TitleLevel>();
	GameEngineCore::CreateLevel<PlayLevel>();
	GameEngineCore::CreateLevel<TestLevel>();
	GameEngineCore::ChangeLevel("PlayLevel");
}

void ContentsCore::GameEnd() 
{

}