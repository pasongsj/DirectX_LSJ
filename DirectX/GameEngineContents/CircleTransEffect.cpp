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

	ResultTarget = GameEngineRenderTarget::Create(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, GameEngineWindow::GetScreenSize(), float4::Null);

}

void CircleTransEffect::Effect(GameEngineRenderTarget* _Target, float _DeltaTime)
{
	ResultTarget->Clear();
	CircleTransUnit->ShaderResHelper.SetTexture("DiffuseTex", _Target->GetTexture(0));
	ResultTarget->Setting();
	CircleTransUnit->Render(_DeltaTime);
	CircleTransUnit->ShaderResHelper.AllResourcesReset();

	_Target->Clear();
	_Target->Merge(ResultTarget);

}
