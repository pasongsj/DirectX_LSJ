#include "PrecompileHeader.h"
#include "SagittariusArrow.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

SagittariusArrow::SagittariusArrow() 
{
}

SagittariusArrow::~SagittariusArrow() 
{
}

void SagittariusArrow::MakeSprite()
{
	if (nullptr == GameEngineSprite::Find("Sagitarius_Arrow"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources\\Texture\\stage1\\Boss\\Hilda\\Sagittarius\\Arrow");

		GameEngineSprite::LoadFolder("Sagitarius_Arrow",Dir.GetPlusFileName("Arrow").GetFullPath());
		GameEngineSprite::LoadFolder("Sagitarius_AppearFX",Dir.GetPlusFileName("AppearFX").GetFullPath());

	}
}

void SagittariusArrow::Start()
{
	MakeSprite();

	ArrowRender = CreateComponent<GameEngineSpriteRenderer>();
	ArrowRender->CreateAnimation({ .AnimationName = "Shoot", .SpriteName = "Sagitarius_Arrow", .FrameInter = 0.05f, .ScaleToTexture = true });
	ArrowRender->ChangeAnimation("Shoot");
}

void SagittariusArrow::Update(float _DeltaTime)
{
	if (nullptr == ArrowRender)
	{
		MsgAssert("Sagittarius �� Arrow �� �������� �ʾҽ��ϴ�");
		return;
	}
	GetTransform()->AddLocalPosition(float4::Left * ArrowSpeed * _DeltaTime);

	// �� ���������� ȭ���̵��� �ƴ� ����̵��̱� ������ ���� ������ ��
	float4 ArrowPos = GetTransform()->GetWorldPosition();
	float4 ScreenSize = GameEngineWindow::GetScreenSize() + (GetTransform()->GetLocalScale()).half();
	if (ArrowPos.x< -ScreenSize.hx() || ArrowPos.x >ScreenSize.hx() ||
		ArrowPos.y< -ScreenSize.hy() || ArrowPos.y >ScreenSize.hy())
	{
		Death();
		// ȭ�� ������ ����!
	}
}