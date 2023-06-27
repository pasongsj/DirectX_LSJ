#pragma once
#include "GameContentsEnemyRenderer.h"

enum class SortRenderer
{
	CENTER,
	TOP,
	BOT,
	LEFT,
	RIGHT,
	RTOP,
	LTOP,
	RBOT,
	LBOT,

};

// Ό³Έν :
class ContentsSortRenderer : public GameContentsEnemyRenderer
{
public:
	// constrcuter destructer
	ContentsSortRenderer();
	~ContentsSortRenderer();

	// delete Function
	ContentsSortRenderer(const ContentsSortRenderer& _Other) = delete;
	ContentsSortRenderer(ContentsSortRenderer&& _Other) noexcept = delete;
	ContentsSortRenderer& operator=(const ContentsSortRenderer& _Other) = delete;
	ContentsSortRenderer& operator=(ContentsSortRenderer&& _Other) noexcept = delete;

	void SetLocalSortPosition(const float4& _Pos, SortRenderer _Sort = SortRenderer::CENTER);

	inline void Reset()
	{
		PivotPos = float4::Zero;
		PivotSort = SortRenderer::CENTER;
	}

protected:
	void Update(float _DeltaTime) override;

private:
	float4 PivotPos = float4::Zero;
	SortRenderer PivotSort = SortRenderer::CENTER;

};