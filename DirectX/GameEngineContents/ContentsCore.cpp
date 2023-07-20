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
#include "WallyLevel.h"
#include "ShopLevel.h"

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
	GameEngineGUI::GUIWindowCreate<postitionkit>("Controller");



	GameEngineCore::CreateLevel<PlayLevel>();
	GameEngineCore::CreateLevel<HildaBergLevel>();
	GameEngineCore::CreateLevel<StoryLevel>();
	GameEngineCore::CreateLevel<LoadingLevel>();
	GameEngineCore::CreateLevel<TutorialLevel>();
	GameEngineCore::CreateLevel<ResultLevel>();
	GameEngineCore::CreateLevel<TitleLevel>();
	GameEngineCore::CreateLevel<OverWorldLevel>();
	GameEngineCore::CreateLevel<WallyLevel>();
	GameEngineCore::CreateLevel<ShopLevel>();

	GameEngineCore::ChangeLevel("ShopLevel");
}

void ContentsCore::GameEnd() 
{

}