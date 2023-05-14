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
		Dir.Move("Texture\\stage1\\Boss\\Hilda\\Sagittarius\\Arrow");

		GameEngineSprite::LoadFolder("Sagitarius_Arrow",Dir.GetPlusFileName("Arrow").GetFullPath());
		GameEngineSprite::LoadFolder("Sagitarius_AppearFX",Dir.GetPlusFileName("AppearFX").GetFullPath());

	}
}

void SagittariusArrow::Start()
{
	MakeSprite();
}

void SagittariusArrow::Update(float _DeltaTime)
{

}