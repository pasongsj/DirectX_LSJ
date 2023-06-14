#include "PrecompileHeader.h"
#include "TutorialLevel.h"
#include <GameEngineCore/GameEngineSprite.h>
#include "TutorialBackGround.h"
#include "PlayerAirPlaneMode.h"

TutorialLevel::TutorialLevel()
{
}

TutorialLevel::~TutorialLevel()
{
}


void TutorialLevel::LoadSprite()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentResources");
	Dir.Move("ContentResources\\Texture\\Tutorial");
	GameEngineSprite::ReLoad(Dir.GetPlusFileName("shmup_tutorial_BG").GetFullPath(), "shmup_tutorial_BG");

	if (nullptr == GameEngineTexture::Find("shmup_tutorial_linework"))
	{
		GameEngineTexture::Load(Dir.GetPlusFileName("shmup_tutorial_linework.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("tutorial_pink_sphere_1.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("exit.png").GetFullPath());

	}
	else
	{
		GameEngineTexture::ReLoad(Dir.GetPlusFileName("shmup_tutorial_linework.png").GetFullPath());
		GameEngineTexture::ReLoad(Dir.GetPlusFileName("tutorial_pink_sphere_1.png").GetFullPath());
		GameEngineTexture::ReLoad(Dir.GetPlusFileName("exit.png").GetFullPath());
	}

}

void TutorialLevel::UnLoadSprite()
{
	GameEngineSprite::UnLoad("shmup_tutorial_BG");
	GameEngineTexture::UnLoad("shmup_tutorial_linework.png");
	GameEngineTexture::UnLoad("tutorial_pink_sphere_1.png");
	GameEngineTexture::UnLoad("exit.png");

}



void TutorialLevel::LevelChangeStart()
{
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });
	GetMainCamera()->SetSortType(CupHeadRendererOrder::Boss, SortType::ZSort);
	
	
	LoadSprite();


	CreateActor<TutorialBackGround>(CupHeadActorOrder::BackGround);
	std::shared_ptr<PlayerAirPlaneMode> NewPlayer7 = CreateActor<PlayerAirPlaneMode>(CupHeadActorOrder::Player);


}
void TutorialLevel::LevelChangeEnd()
{
	Player::MainPlayer->Death();
	Player::MainPlayer = nullptr;

	UnLoadSprite();
	AllActorDestroy();
}