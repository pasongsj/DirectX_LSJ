#include "PrecompileHeader.h"
#include "HildaBergBack1.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineResource.h>

HildaBergBack1::HildaBergBack1() 
{
}

HildaBergBack1::~HildaBergBack1() 
{
}

//void HildaBergBack1::MakeSprite()
//{
//
//	GameEngineDirectory NewDir;
//	NewDir.MoveParentToDirectory("ContentResources");
//	NewDir.Move("ContentResources\\Texture\\stage1\\Boss\\Hilda\\Level");
//	std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });
//	for (size_t i = 0; i < File.size(); i++)
//	{
//		GameEngineTexture::Load(File[i].GetFullPath());
//	}
//}

void HildaBergBack1::Start()
{
	//MakeSprite();

	//MainBG = CreateComponent<GameEngineSpriteRenderer>();
	//MainBG->SetScaleToTexture("blimp_sky.png");

	//BGRange = MainBG->GetTransform()->GetLocalScale().ix();

	//SubBG = CreateComponent<GameEngineSpriteRenderer>();
	//SubBG->SetScaleToTexture("blimp_sky.png");
	//SubBG->GetTransform()->SetLocalPosition(MainBG->GetTransform()->GetLocalPosition() + float4(static_cast<float>(BGRange),0));

	//BGLimit = (BGRange - GameEngineWindow::GetScreenSize().ix()) / 2;



	MainHill= CreateComponent<GameEngineSpriteRenderer>();
	MainHill->SetScaleToTexture("blimp_dark_hills.png");
	MainHill->GetTransform()->SetLocalPosition( float4(0,134 - GameEngineWindow::GetScreenSize().hy()));

	HillRange = MainHill->GetTransform()->GetLocalScale().ix();

	SubHill	= CreateComponent<GameEngineSpriteRenderer>();
	SubHill->SetScaleToTexture("blimp_dark_hills.png");
	SubHill->GetTransform()->SetLocalPosition(MainHill->GetTransform()->GetLocalPosition() + float4(static_cast<float>(HillRange), 0));

	HillLimit = (HillRange - GameEngineWindow::GetScreenSize().ix()) / 2;


}

void HildaBergBack1::Update(float _DeltaTime)
{

	GetTransform()->AddLocalPosition(float4(-50 * _DeltaTime, 0));

	if (nullptr == GetLevel()->GetMainCamera())
	{
		MsgAssert("카메라를 가져오지 못했습니다");
		return;
	}
	int CamX = (GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition()).ix();

	// MainHill과 SubHill을 교체해주는 작업
	if ((SubHill->GetTransform()->GetWorldPosition().ix() - HillRange / 2) < CamX && CamX < (SubHill->GetTransform()->GetWorldPosition().ix() + HillRange / 2)) {

		std::shared_ptr<class GameEngineSpriteRenderer> tempHill = MainHill;
		MainHill = SubHill;
		SubHill = tempHill;
		tempHill = nullptr;
	}



	//float4 WorldBGPos = MainBG->GetTransform()->GetWorldPosition();

	//float4 NextBGPos = MainBG->GetTransform()->GetLocalPosition();

	//if (CamX - WorldBGPos.ix() > BGLimit)
	//{
	//	NextBGPos.x += BGRange;
	//}
	//else if (CamX - WorldBGPos.ix() < -BGLimit) {
	//	NextBGPos.x -= BGRange;
	//}

	//if (NextBGPos != SubBG->GetTransform()->GetLocalPosition()) {
	//	SubBG->GetTransform()->SetLocalPosition(NextBGPos);
	//}



	float4 WorldHillPos = MainHill->GetTransform()->GetWorldPosition();

	float4 NextHillPos = MainHill->GetTransform()->GetLocalPosition();
	if (CamX - WorldHillPos.ix() > HillLimit)
	{
		NextHillPos.x += HillRange;
	}
	else if (CamX - WorldHillPos.ix() < -HillLimit) {
		NextHillPos.x -= HillRange;
	}

	if (NextHillPos != SubHill->GetTransform()->GetLocalPosition()) {
		SubHill->GetTransform()->SetLocalPosition(NextHillPos);
	}
}