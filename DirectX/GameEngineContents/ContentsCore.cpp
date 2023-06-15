#include "PrecompileHeader.h"
#include "ContentsCore.h"
#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineVertexShader.h>
#include <GameEngineCore/GameEnginePixelShader.h>
#include <GameEngineCore/GameEngineRenderingPipeLine.h>


#include "PlayLevel.h"
#include "TitleLevel.h"
#include "TestLevel.h"
#include "HildaBergLevel.h"
#include "StoryLevel.h"
#include "LoadingLevel.h"
#include "TutorialLevel.h"

ContentsCore::ContentsCore() 
{
}

ContentsCore::~ContentsCore() 
{
}


void ContentsCore::GameStart() 
{
	// 이전에 매쉬는 만들어져 있어야 한다.

	new int();

	ContentsResourcesCreate();

	//GameEngineGUI::GUIWindowCreate<GameEngineCoreWindow>("Controller");



	GameEngineCore::CreateLevel<TitleLevel>();
	GameEngineCore::CreateLevel<PlayLevel>();
	//GameEngineCore::CreateLevel<TestLevel>();
	GameEngineCore::CreateLevel<HildaBergLevel>();
	GameEngineCore::CreateLevel<StoryLevel>();
	GameEngineCore::CreateLevel<LoadingLevel>();
	GameEngineCore::CreateLevel<TutorialLevel>();

	GameEngineCore::ChangeLevel("LoadingLevel");
}

void ContentsCore::GameEnd() 
{

}