#include "PrecompileHeader.h"
#include "ContentsSortRenderer.h"

ContentsSortRenderer::ContentsSortRenderer() 
{
}

ContentsSortRenderer::~ContentsSortRenderer() 
{
}

void ContentsSortRenderer::SetLocalSortPosition(const float4& _Pos, SortRenderer _Sort)
{
	if (true == _Pos.IsZero() && SortRenderer::CENTER == _Sort)
	{
		MsgAssert("Zero위치에 center sort를 사용할 수 없습니다");
	}
	PivotPos = _Pos;
	PivotSort = _Sort;
}

void ContentsSortRenderer::Update(float _Delta)
{
	GameContentsEnemyRenderer::Update(_Delta);
	if (SortRenderer::CENTER != PivotSort)
	{
		float4 HalfScale = GetTransform()->GetLocalScale().half();
		switch (PivotSort)
		{
		case SortRenderer::CENTER:
			break;
		case SortRenderer::TOP:
			GetTransform()->SetLocalPosition(PivotPos + float4(0, -HalfScale.y));
			break;
		case SortRenderer::BOT:
			GetTransform()->SetLocalPosition(PivotPos + float4(0, HalfScale.y));
			break;

		case SortRenderer::LEFT:
			GetTransform()->SetLocalPosition(PivotPos + float4(HalfScale.x, 0));
			break;
		case SortRenderer::RIGHT:
			GetTransform()->SetLocalPosition(PivotPos + float4(-HalfScale.x, 0));

			break;
		case SortRenderer::RTOP:
			GetTransform()->SetLocalPosition(PivotPos + float4(-HalfScale.x, -HalfScale.y));

			break;
		case SortRenderer::LTOP:
			GetTransform()->SetLocalPosition(PivotPos + float4(HalfScale.x, -HalfScale.y));

			break;
		case SortRenderer::RBOT:
			GetTransform()->SetLocalPosition(PivotPos + float4(-HalfScale.x, HalfScale.y));

			break;
		case SortRenderer::LBOT:
			GetTransform()->SetLocalPosition(PivotPos + float4(HalfScale.x, HalfScale.y));

			break;
		default:
			break;
		}
	}
}