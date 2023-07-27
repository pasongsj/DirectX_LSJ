#include "PrecompileHeader.h"
#include "StoryLevel.h"
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSprite.h>

#include "StoryObject.h"
#include "OldFilmEffect.h"
#include "LoadingLevel.h"
#include "CircleTransEffect.h"

StoryLevel::StoryLevel() 
{
}

StoryLevel::~StoryLevel() 
{
}

void StoryLevel::Start()
{
	//GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	//GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });
	if (false == GameEngineInput::IsKey("ChangeLevel"))
	{
		GameEngineInput::CreateKey("ChangeLevel", VK_F4);
	}
	GetLastTarget()->CreateEffect<OldFilmEffect>();
	GameEngineDirectory Dir;
	if (false == GameEngineSound::Find("cutscene_pageturn_01.wav"))
	{
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources\\Sound\\Story");
		GameEngineSound::Load(Dir.GetPlusFileName("cutscene_pageturn_01.wav").GetFullPath());
	}

}
void StoryLevel::Update(float _DeltaTime) 
{
	if ((true == Story->isEnd() || true == GameEngineInput::IsDown("ChangeLevel")) && 0.0f == LevelChangeTime)
	{
		FadeEffect->SetFade(CircleTransOption::FadeIn);
		LevelChangeTime = GetLiveTime() + 1.0f;
		GameEngineSound::Play("WorldMap_LevelSelect_StartLevel.wav");
		BackGroundSound.SoundFadeOut(1.0f);


	}
	if (0.0f < LevelChangeTime && LevelChangeTime < GetLiveTime() && true == FadeEffect->IsEnd())
	{
		LoadingLevel::SetLevel(CupheadLevel::OVERWORLD);
		GameEngineCore::ChangeLevel("LoadingLevel");

	}
}
	
void StoryLevel::LevelChangeStart()
{
	ResetLiveTime();
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });

	std::shared_ptr<GameEngineCamera> Camera = GetLevel()->GetCamera(100);
	Camera->SetProjectionType(CameraType::Orthogonal);
	Camera->GetTransform()->SetLocalPosition({ 0, 0, -1000.0f });

	if (nullptr == FadeEffect)
	{
		FadeEffect = GetLastTarget()->CreateEffect<CircleTransEffect>();
	}
	if (nullptr == GameEngineSprite::Find("story0"))
	{

		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources\\Texture\\story\\before");


		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("Page 00-01").GetFullPath(),"story0");
		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("Page 01-02").GetFullPath(),"story1");
		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("Page 02-03").GetFullPath(),"story2");
		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("Page 03-04").GetFullPath(),"story3");
		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("Page 04-05").GetFullPath(),"story4");
		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("Page 05-06").GetFullPath(),"story5");
		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("Page 06-07").GetFullPath(),"story6");
		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("Page 07-08").GetFullPath(),"story7");
		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("Page 08-09").GetFullPath(),"story8");
		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("Page 09-10").GetFullPath(),"story9");
		GameEngineSprite::ReLoad(NewDir.GetPlusFileName("Page 10-11").GetFullPath(),"story10");


	}
	LevelChangeTime = 0.0f;
	Story = CreateActor<StoryObject>(CupHeadActorOrder::BackGround);
	FadeEffect->SetFade(CircleTransOption::FadeOut);

	BackGroundSound = GameEngineSound::Play("MUS_Intro.wav");
	BackGroundSound.SetLoop(-1);
	BackGroundSound.SetVolume(0.5f);
}
void StoryLevel::LevelChangeEnd()
{
	GameEngineSprite::UnLoad("story0");
	GameEngineSprite::UnLoad("story1");
	GameEngineSprite::UnLoad("story2");
	GameEngineSprite::UnLoad("story3");
	GameEngineSprite::UnLoad("story4");
	GameEngineSprite::UnLoad("story5");
	GameEngineSprite::UnLoad("story6");
	GameEngineSprite::UnLoad("story7");
	GameEngineSprite::UnLoad("story8");
	GameEngineSprite::UnLoad("story9");
	GameEngineSprite::UnLoad("story10");
	Story->Death();
	Story = nullptr;

	AllActorDestroy();
	GetLastTarget()->ReleaseEffect(FadeEffect);
	FadeEffect = nullptr;
	BackGroundSound.Stop();
}