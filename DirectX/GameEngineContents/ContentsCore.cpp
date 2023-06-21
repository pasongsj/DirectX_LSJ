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
#include "ResultLevel.h"
#include "TitleLevel.h"
#include "OverWorldLevel.h"
#include "postitionkit.h"

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
	GameEngineGUI::GUIWindowCreate<postitionkit>("Controller");



	GameEngineCore::CreateLevel<PlayLevel>();
	GameEngineCore::CreateLevel<HildaBergLevel>();
	GameEngineCore::CreateLevel<StoryLevel>();
	GameEngineCore::CreateLevel<LoadingLevel>();
	GameEngineCore::CreateLevel<TutorialLevel>();
	GameEngineCore::CreateLevel<ResultLevel>();
	GameEngineCore::CreateLevel<TitleLevel>();
	GameEngineCore::CreateLevel<OverWorldLevel>();

	GameEngineCore::ChangeLevel("TitleLevel");
}

void ContentsCore::GameEnd() 
{

}