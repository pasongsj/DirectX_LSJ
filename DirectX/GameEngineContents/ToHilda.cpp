#include "PrecompileHeader.h"
#include "ToHilda.h"
#include "LoadingLevel.h"

ToHilda::ToHilda() 
{
}

ToHilda::~ToHilda() 
{
}

void ToHilda::Start()
{
	OverWorldInteractObject::Start();
	InteractRender->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "OverWorld_To_Hilda",.FrameInter = 0.1f, .Loop = true, .ScaleToTexture = true });
	InteractRender->ChangeAnimation("Idle");
	TitleCard->SetScaleToTexture("title_card_background.png");
	EnterFucntion = [] {
		LoadingLevel::SetLevel(CupheadLevel::HILDA);
		GameEngineCore::ChangeLevel("LoadingLevel");
	};
}
