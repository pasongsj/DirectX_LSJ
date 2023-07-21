#include "PrecompileHeader.h"
#include "Drawer_L.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

Drawer_L::Drawer_L()
{
}

Drawer_L::~Drawer_L()
{
}

void Drawer_L::Start()
{
	DrawerRender = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::BackGround);
	DrawerRender->SetScaleToTexture("shop_drawer_left.png");
	GetTransform()->SetLocalPosition(StartPos);

}

void Drawer_L::Update(float _DeltaTime)
{
	if (false == isClosed)
	{
		return;
	}
	CloseTimer += _DeltaTime;
	GetTransform()->SetLocalPosition(float4::Zero.LerpClamp(StartPos, DestPos, CloseTimer * 2.0f));


}
