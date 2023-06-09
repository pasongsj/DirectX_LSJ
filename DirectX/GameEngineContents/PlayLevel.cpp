#include "PrecompileHeader.h"
#include "PlayLevel.h"
//#include "TestObject.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineVideo.h>
#include <GameEngineCore/GameEngineCoreWindow.h>
#include "PlayerAirPlaneMode.h"

//std::shared_ptr<Player> Object0 = nullptr;
//std::shared_ptr<TestObject> Object1 = nullptr;
//std::shared_ptr<GameEngineSpriteRenderer> RenderTest = nullptr;

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}

void PlayLevel::Update(float _DeltaTime)
{
	//if (nullptr != Object1 && 1.0f <= Object1->GetLiveTime())
	//{
	//	if (nullptr == Object1)
	//	{
	//		return;
	//	}
	//	// RenderTest->Death();
	//	Object1->Death();
	//	Object1 = nullptr;
	//}
}

void PlayLevel::PlayerCreate(/*Playlevel* this*/)
{
	//if (nullptr != Object1)
	//{
	//	Object1->Render->Death();
	//	Object1 = nullptr;
	//}
}

void PlayLevel::Start()
{

	//{
	//	GameEngineDirectory NewDir;
	//	NewDir.MoveParentToDirectory("ContentResources");
	//	NewDir.Move("ContentResources");

	//	std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });


	//	for (size_t i = 0; i < File.size(); i++)
	//	{
	//		GameEngineTexture::Load(File[i].GetFullPath());
	//	}
	//}



	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });


	//std::shared_ptr<GameEngineCoreWindow> Window = GameEngineGUI::FindGUIWindowConvert<GameEngineCoreWindow>("CoreWindow");

	{
		//if (nullptr == Window)
		//{
		//	MsgAssert("윈도우 테스트 코드 미작동");
		//}

		//Window->Test = std::bind(&PlayLevel::PlayerCreate, this);

		//Object0 = CreateActor<Player>(0);
		//Object0->GetTransform()->SetLocalPosition({ -100.0f, 0.0f, 0.0f });

		/*Object1 = CreateActor<TestObject>(-20);
		Object1->GetTransform()->SetLocalPosition({ 150.0f, 0.0f, 0.0f });
		Object1->Render->GetTransform()->SetLocalScale({ 100.0f, 100.0f, 100.0f });

		RenderTest = Object1->CreateComponent<GameEngineSpriteRenderer>();

		RenderTest->GetTransform()->SetLocalPosition({ 100.0f, 0.0f, 0.0f });
		RenderTest->GetTransform()->SetLocalScale({ 100.0f, 100.0f, 100.0f });

		Object1->GetTransform()->SetParent(Object0->GetTransform());


		std::shared_ptr<TestObject> Object2 = CreateActor<TestObject>(-20);
		Object2->GetTransform()->SetLocalPosition({ 400.0f, 0.0f, 0.0f });
		Object2->Render->GetTransform()->SetLocalScale({ 100.0f, 100.0f, 100.0f });

		Object2->GetTransform()->SetParent(Object1->GetTransform());*/
	}

	//CreateActor< PlayerAirPlaneMode>();
	//{
	//	std::shared_ptr<TestObject> Object = CreateActor<TestObject>(-20);
	//	Object->GetTransform()->SetLocalScale({ 1000, 1000, 1000 });
	//	Object->GetTransform()->SetLocalPosition({ 0, 0, 100.0f });
	//}



}
void PlayLevel::LevelChangeStart()
{
	GameEngineLevel::LevelChangeStart();
	int a = 0;
}

void PlayLevel::LevelChangeEnd()
{
	GameEngineLevel::LevelChangeEnd();
	int a = 0;
}