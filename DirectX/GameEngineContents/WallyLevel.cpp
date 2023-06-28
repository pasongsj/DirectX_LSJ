#include "PrecompileHeader.h"
#include "WallyLevel.h"

#include "OldFilmEffect.h"



#include "PlayerAirPlaneMode.h"
#include "Wally1.h"
#include "Wally2.h"
#include "WallyBack.h"


WallyLevel::WallyLevel()
{
}

WallyLevel::~WallyLevel()
{
}
void WallyLevel::Start()
{
	//GetLastTarget()->CreateEffect<OldFilmEffect>();
}

void WallyLevel::Update(float _DeltaTime)
{
}

void WallyLevel::LevelChangeStart()
{
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentResources");
	Dir.Move("ContentResources\\Texture\\stage2\\Boss\\Wally\\Level");
	std::vector<GameEngineFile> AllLoadFile = Dir.GetAllFile({ ".png"});
	for (size_t i = 0; i < AllLoadFile.size(); i++)
	{
		GameEngineTexture::Load(AllLoadFile[i].GetFullPath());
	}

	// BackGround
	std::shared_ptr<WallyBack> BG0 = CreateActor<WallyBack>(CupHeadActorOrder::BackGround);
	BG0->Setting("birdhouse_bg_0008.png", 1000,0.0f, 50.0f,WallyBackGroundSort::CENTER);

	std::shared_ptr<WallyBack> BG1 = CreateActor<WallyBack>(CupHeadActorOrder::BackGround);
	BG1->Setting("birdhouse_bg_0007.png", 950, 0.0f, 100.0f, WallyBackGroundSort::TOP);

	std::shared_ptr<WallyBack> BG2 = CreateActor<WallyBack>(CupHeadActorOrder::BackGround);
	BG2->Setting("birdhouse_bg_0006.png", 900, 0.0f, 150.0f, WallyBackGroundSort::BOT);

	std::shared_ptr<WallyBack> BG3 = CreateActor<WallyBack>(CupHeadActorOrder::BackGround);
	BG3->Setting("birdhouse_bg_0005.png", 850, 0.0f, 200.0f, WallyBackGroundSort::BOT);

	std::shared_ptr<WallyBack> BG4 = CreateActor<WallyBack>(CupHeadActorOrder::BackGround);
	BG4->Setting("birdhouse_bg_0004.png", 800, 0.0f, 250.0f, WallyBackGroundSort::BOT);

	std::shared_ptr<WallyBack> BG5 = CreateActor<WallyBack>(CupHeadActorOrder::BackGround);
	BG5->Setting("birdhouse_bg_0003.png", 750, 0.0f, 300.0f, WallyBackGroundSort::BOT);
	 
	std::shared_ptr<WallyBack> BG6 = CreateActor<WallyBack>(CupHeadActorOrder::BackGround);
	BG6->Setting("birdhouse_bg_0002.png", 700, 0.0f, 350.0f, WallyBackGroundSort::BOT);

	std::shared_ptr<WallyBack> BG7 = CreateActor<WallyBack>(CupHeadActorOrder::BackGround);
	BG7->Setting("birdhouse_bg_0001.png", 650, 0.0f, 400.0f, WallyBackGroundSort::BOT);



	//CreateActor<Wally1>(CupHeadActorOrder::Boss);
	CreateActor<Wally2>(CupHeadActorOrder::Boss);
	CreateActor<PlayerAirPlaneMode>(CupHeadActorOrder::Player);
}

void WallyLevel::LevelChangeEnd()
{
	AllActorDestroy();


	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentResources");
	Dir.Move("ContentResources\\Texture\\stage2\\Boss\\Wally\\Level");
	std::vector<GameEngineFile> AllLoadFile = Dir.GetAllFile({ ".png" });
	for (size_t i = 0; i < AllLoadFile.size(); i++)
	{
		GameEngineTexture::UnLoad(AllLoadFile[i].GetFullPath());
	}
}