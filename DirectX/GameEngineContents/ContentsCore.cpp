#include "PrecompileHeader.h"
#include "ContentsCore.h"
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCoreWindow.h>
#include "PlayLevel.h"
#include "TitleLevel.h"
#include "TestLevel.h"
#include "HildaBergLevel.h"

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

	GameEngineGUI::GUIWindowCreate<GameEngineCoreWindow>("CoreWindow");



	GameEngineCore::CreateLevel<TitleLevel>();
	GameEngineCore::CreateLevel<PlayLevel>();
	//GameEngineCore::CreateLevel<TestLevel>();
	GameEngineCore::CreateLevel<HildaBergLevel>();
	GameEngineCore::ChangeLevel("HildaBergLevel");
}

void ContentsCore::GameEnd() 
{

}