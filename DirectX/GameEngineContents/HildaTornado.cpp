#include "PrecompileHeader.h"
#include "HildaTornado.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

HildaTornado::HildaTornado() 
{
}

HildaTornado::~HildaTornado() 
{
}

void HildaTornado::Start()
{
	TornatoRender = CreateComponent<GameEngineSpriteRenderer>();
	TornatoRender->CreateAnimation({ .AnimationName = "Intro",  .TextureName = "tornado_intro_00", .Start = 1, .End = 12,.InterTime = 0.05f, .Loop = true });
	TornatoRender->CreateAnimation({ .AnimationName = "attack",  .TextureName = "tornado_attack_00", .Start = 1, .End = 16,.InterTime = 0.05f, .Loop = false });
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