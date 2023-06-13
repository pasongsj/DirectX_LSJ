#include "PrecompileHeader.h"
#include "TutorialLevel.h"
#include "TutorialBackGround.h"
#include "PlayerAirPlaneMode.h"

TutorialLevel::TutorialLevel() 
{
}

TutorialLevel::~TutorialLevel() 
{
}

void TutorialLevel::Start()
{

}

void TutorialLevel::Update(float _DeltaTime)
{

}

void TutorialLevel::LevelChangeStart()
{
	CreateActor<TutorialBackGround>(CupHeadActorOrder::BackGround);
	std::shared_ptr<PlayerAirPlaneMode> NewPlayer7 = CreateActor<PlayerAirPlaneMode>(CupHeadActorOrder::Player);
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	//GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });
	GetMainCamera()->SetSortType(CupHeadRendererOrder::Boss, SortType::ZSort);


}
void TutorialLevel::LevelChangeEnd()
{
	Player::MainPlayer->Death();
	Player::MainPlayer = nullptr;
	AllActorDestroy();
}