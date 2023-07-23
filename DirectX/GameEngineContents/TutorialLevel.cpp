#include "PrecompileHeader.h"
#include "TutorialLevel.h"
#include <GameEngineCore/GameEngineSprite.h>
#include "TutorialBackGround.h"
#include "PlayerAirPlaneMode.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineActor.h>

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

	if (nullptr == GameEngineTexture::Find("shmup_tutorial_linework.png"))
	{
		GameEngineTexture::Load(Dir.GetPlusFileName("shmup_tutorial_linework.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("tutorial_pink_sphere_1.png").GetFullPath());
		GameEngineTexture::Load(Dir.GetPlusFileName("exit.png").GetFullPath());

	}
	else
	{
		GameEngineTexture::ReLoad("shmup_tutorial_linework.png");
		GameEngineTexture::ReLoad("tutorial_pink_sphere_1.png");
		GameEngineTexture::ReLoad("exit.png");
	}

}

void TutorialLevel::UnLoadSprite()
{
	GameEngineSprite::UnLoad("shmup_tutorial_BG");
	GameEngineTexture::UnLoad("shmup_tutorial_linework.png");
	GameEngineTexture::UnLoad("tutorial_pink_sphere_1.png");
	GameEngineTexture::UnLoad("exit.png");

	// Player
	GameEngineSprite::UnLoad("Cuphead_AirPlane_Origin_Idle");
	GameEngineSprite::UnLoad("Cuphead_AirPlane_Origin_Idleup");
	GameEngineSprite::UnLoad("Cuphead_AirPlane_Origin_Idledown");
	GameEngineSprite::UnLoad("Cuphead_AirPlane_Origin_intro");
	GameEngineSprite::UnLoad("Cuphead_AirPlane_Origin_transup");
	GameEngineSprite::UnLoad("Cuphead_AirPlane_Origin_transdown");
	GameEngineSprite::UnLoad("Cuphead_AirPlane_Super_Idle");
	GameEngineSprite::UnLoad("Cuphead_AirPlane_Super_Idleup");
	GameEngineSprite::UnLoad("Cuphead_AirPlane_Super_Idledown");
	GameEngineSprite::UnLoad("Cuphead_AirPlane_Super_intro");
	GameEngineSprite::UnLoad("Cuphead_AirPlane_Super_transup");
	GameEngineSprite::UnLoad("Cuphead_AirPlane_Super_transdown");
	GameEngineSprite::UnLoad("Cuphead_AirPlane_Shrink_Idle");
	GameEngineSprite::UnLoad("Cuphead_AirPlane_Shrink_Idleup");
	GameEngineSprite::UnLoad("Cuphead_AirPlane_Shrink_Idledown");
	GameEngineSprite::UnLoad("Cuphead_AirPlane_Shrink_intro");
	GameEngineSprite::UnLoad("Cuphead_AirPlane_Shrink_transup");
	GameEngineSprite::UnLoad("Cuphead_AirPlane_Shrink_transdown");
	GameEngineSprite::UnLoad("Cuphead_AirPlane_Parry");
	GameEngineSprite::UnLoad("Cuphead_AirPlane_Shoot_Up");
	GameEngineSprite::UnLoad("Cuphead_AirPlane_Shoot_Down");
	GameEngineSprite::UnLoad("Cuphead_AirPlane_Ghost");
	GameEngineSprite::UnLoad("Cuphead_AirPlane_Spark");
	GameEngineSprite::UnLoad("peashotFX");
	GameEngineSprite::UnLoad("Cuphead_AirPlane_Smoke_Idle");
	GameEngineSprite::UnLoad("Cuphead_AirPlane_Bullet");
	GameEngineSprite::UnLoad("shmup_super_boom");
	GameEngineSprite::UnLoad("shmup_super_explode");
	GameEngineSprite::UnLoad("Super_FX");
	GameEngineSprite::UnLoad("Cuphead_AirPlane_ExBullet");


}



void TutorialLevel::LevelChangeStart()
{
	ResetLiveTime();
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });
	GetMainCamera()->SetSortType(CupHeadRendererOrder::Boss, SortType::ZSort);
	
	std::shared_ptr<GameEngineCamera> Camera = GetLevel()->GetCamera(100);
	Camera->SetProjectionType(CameraType::Orthogonal);
	Camera->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });
	//LoadSprite();


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