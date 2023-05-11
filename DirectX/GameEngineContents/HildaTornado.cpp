#include "PrecompileHeader.h"
#include "HildaTornado.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

HildaTornado::HildaTornado() 
{
}

HildaTornado::~HildaTornado() 
{
}

void HildaTornado::MakeSprite()
{
	if (nullptr == GameEngineSprite::Find("Hilda_Tornado_Intro"))
	{

		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("stage1\\Boss\\Hilda\\HildaBerg\\Normal");


		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Tornado\\Tornado\\Attack").GetFullPath(), "Hilda_Tornado_Attack");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Tornado\\Tornado\\Intro").GetFullPath(), "Hilda_Tornado_Intro");

	}
}


void HildaTornado::Start()
{
	MakeSprite();
	TornatoRender = CreateComponent<GameEngineSpriteRenderer>();
	TornatoRender->CreateAnimation({ .AnimationName = "Intro",  .SpriteName = "Hilda_Tornado_Intro", .FrameInter = 0.05f, .Loop = true, .ScaleToImage = true });
	TornatoRender->CreateAnimation({ .AnimationName = "attack",  .SpriteName = "Hilda_Tornado_Attack",.FrameInter = 0.05f, .Loop = false , .ScaleToImage = true });
	TornatoRender->ChangeAnimation("Intro");
}

void HildaTornado::Update(float _DeltaTime)
{
	if (true == isIntro && GetLiveTime() > 1.6f)
	{
		isIntro = false;
		TornatoRender->ChangeAnimation("attack");
	}
	else if (false == isIntro)
	{
		GetTransform()->AddLocalPosition(float4(-1000 * _DeltaTime, 0));
	}
}