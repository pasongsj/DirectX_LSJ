#include "PrecompileHeader.h"
#include "Constellation.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineRenderer.h>

Constellation::Constellation() 
{
}

Constellation::~Constellation() 
{
}

void Constellation::Start()
{
	if (nullptr == GameEngineSprite::Find("Taurus_Constellation"))
	{
		MsgAssert("���ڸ� Sprite�� �������� �ʾҽ��ϴ�.");
		return;
	}
	ConstellationRender = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::UI);
	ConstellationRender->CreateAnimation({ .AnimationName = "Gemini", .SpriteName = "Gemini_Constellation", .Loop = true, .ScaleToTexture = true });
	ConstellationRender->CreateAnimation({ .AnimationName = "Taurus", .SpriteName = "Taurus_Constellation", .Loop = true, .ScaleToTexture = true });
	ConstellationRender->CreateAnimation({ .AnimationName = "Sagittarius", .SpriteName = "Sagittarius_Constellation", .Loop = true, .ScaleToTexture = true });

	ConstellationRender->ChangeAnimation("Gemini");
}

void Constellation::SetConstellation(const std::string_view& _Constellation)
{
	if ("Gemini" != _Constellation && "Taurus" != _Constellation && "Sagittarius" != _Constellation)
	{
		MsgAssert("�߸��� ������ ���ڸ��� �Է��Ͽ����ϴ�.");
		return;
	}
	ConstellationRender->ChangeAnimation(_Constellation);
}

void Constellation::Update(float _DeltaTime)
{
	ConstellationRender->ColorOptionValue.MulColor = float4::One;
	ConstellationRender->ColorOptionValue.MulColor.w = GetLiveTime();
	if (GetLiveTime() > 2.5f)
	{
		Death();
	}
}