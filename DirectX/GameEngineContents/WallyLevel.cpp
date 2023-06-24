#include "PrecompileHeader.h"
#include "WallyLevel.h"

#include "Wally1.h"

WallyLevel::WallyLevel()
{
}

WallyLevel::~WallyLevel()
{
}
void WallyLevel::Start()
{
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

	CreateActor< Wally1>(CupHeadActorOrder::Boss);
}

void WallyLevel::LevelChangeEnd()
{
	AllActorDestroy();
}