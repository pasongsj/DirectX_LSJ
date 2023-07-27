#include "PrecompileHeader.h"
#include "ContentsFxObject.h"

ContentsFxObject::ContentsFxObject() 
{
}

ContentsFxObject::~ContentsFxObject() 
{
}

void ContentsFxObject::Update(float _DeltaTime)
{
	if (nullptr != FxRender && true == FxRender->IsAnimationEnd())
	{
		Death();
		return;
	}
}
