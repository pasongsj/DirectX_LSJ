#include "PrecompileHeader.h"
#include "FadeEffect.h"

FadeEffect::FadeEffect()
{
}

FadeEffect::~FadeEffect()
{
}

void FadeEffect::Start(GameEngineRenderTarget* _Target)
{
	FadeUnit = std::make_shared<GameEngineRenderUnit>();
	FadeUnit->SetMesh("FullRect");
	FadeUnit->SetPipeLine("Fade");

	FadeUnit->ShaderResHelper.SetConstantBufferLink("FADEDATA", FadeData);
	// 
	ResultTarget = GameEngineRenderTarget::Create(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, GameEngineWindow::GetScreenSize(), float4::Null);
}

void FadeEffect::Effect(GameEngineRenderTarget* _Target, float _DeltaTime)
{
	if (State == FadeState::None || true == StateEnd )
	{
		return;
	}

	float Delta = _DeltaTime / TimeRatio;

	if (State == FadeState::FadeOut)
	{
		FadeData.x += Delta;
		if (1.0f <= FadeData.x)
		{
			FadeData.x = 1.0f;
			StateEnd = true;
		}
	}
	else { // Fade In
		FadeData.x -= Delta;
		if (0.0f >= FadeData.x)
		{
			StateEnd = true;
			FadeData.x = 0.0f;
		}

	}


	ResultTarget->Clear();
	FadeUnit->ShaderResHelper.SetTexture("DiffuseTex", _Target->GetTexture(0));
	ResultTarget->Setting();
	FadeUnit->Render(_DeltaTime);
	FadeUnit->ShaderResHelper.AllResourcesReset();

	_Target->Clear();
	_Target->Merge(ResultTarget);

	int a = 0;
}