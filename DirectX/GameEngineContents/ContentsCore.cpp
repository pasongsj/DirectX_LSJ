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
	// ������ �Ž��� ������� �־�� �Ѵ�.

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