#include "PrecompileHeader.h"
#include "CircleTransEffect.h"

CircleTransEffect::CircleTransEffect() 
{
}

CircleTransEffect::~CircleTransEffect() 
{
}


void CircleTransEffect::Start(GameEngineRenderTarget* _Target)
{
	CircleTransUnit = std::make_shared<GameEngineRenderUnit>();
	CircleTransUnit->SetMesh("FullRect");
	CircleTransUnit->SetPipeLine("CircleTrans");
	CircleTransUnit->ShaderResHelper.SetConstantBufferLink("TIMEDATA", TimeData);


	ResultTarget = GameEngineRenderTarget::Create(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, GameEngineWindow::GetScreenSize(), float4::Null);

}

void CircleTransEffect::Effect(GameEngineRenderTarget* _Target, float _DeltaTime)
{

	if (CurState == CircleTransOption::None)
	{
		return;
	}

	float Delta = _DeltaTime / TimeRatio;

	if (CurState == CircleTransOption::FadeOut)
	{
		TimeData.x += Delta;
		if (1.2f <= TimeData.x)
		{
			TimeData.x = 1.2f;
			StateEnd = true;
		}
	}
	else { // Fade In
		TimeData.x -= Delta;
		if (0.0f >= TimeData.x)
		{
			TimeData.x = 0.0f;
			StateEnd = true;
		}

	}


	ResultTarget->Clear();
	CircleTransUnit->ShaderResHelper.SetTexture("DiffuseTex", _Target->GetTexture(0));
	ResultTarget->Setting();
	CircleTransUnit->Render(_DeltaTime);
	CircleTransUnit->ShaderResHelper.AllResourcesReset();

	_Target->Clear();
	_Target->Merge(ResultTarget);

}
