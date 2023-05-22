#include "PrecompileHeader.h"
#include "ContentsCore.h"
#include <GameEngineCore/GameEngineCoreWindow.h>
#include "PlayLevel.h"
#include "TitleLevel.h"
#include "TestLevel.h"
#include "HildaBergLevel.h"
#include "IntroStoryLevel.h"
#include "LoadingLevel.h"

ContentsCore::ContentsCore() 
{
}

ContentsCore::~ContentsCore() 
{
}

void ContentsCore::ContentsResourcesCreate()
{
	// 텍스처 로드만 각 레벨별로 하도록 함


}

void ContentsCore::GameStart() 
{
	// 이전에 매쉬는 만들어져 있어야 한다.

	new int();

	ContentsResourcesCreate();

	GameEngineGUI::GUIWindowCreate<GameEngineCoreWindow>("Controller");



	GameEngineCore::CreateLevel<TitleLevel>();
	GameEngineCore::CreateLevel<PlayLevel>();
	//GameEngineCore::CreateLevel<TestLevel>();
	GameEngineCore::CreateLevel<HildaBergLevel>();
	GameEngineCore::CreateLevel<IntroStoryLevel>();
	GameEngineCore::CreateLevel<LoadingLevel>();
	GameEngineCore::ChangeLevel("LoadingLevel");
}

void ContentsCore::GameEnd() 
{

}