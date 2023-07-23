#include "PrecompileHeader.h"
#include "NumberRenderObject.h"
#include <GameEngineCore/GameEngineUIRenderer.h>

NumberRenderObject::NumberRenderObject()
{
}

NumberRenderObject::~NumberRenderObject()
{
}

void NumberRenderObject::Start()
{
	//D:\project\DirectX_LSJ\DirectX\ContentResources\Texture\Number
	if (nullptr == GameEngineTexture::Find("0White.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources\\Texture\\Number");
		std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".png"});
		for (GameEngineFile _File : Files)
		{
			GameEngineTexture::Load(_File.GetFullPath());
		}
	}
	SetValue(Value);
}
void NumberRenderObject::Setting(size_t index, char _Num)
{
	std::string s(1, _Num);
	if (NumberColor::WHITE == ColorOption)
	{
		NumberRenders[index]->SetScaleToTexture(s + "White.png");
	}
	else
	{
		NumberRenders[index]->SetScaleToTexture(s + "Yellow.png");
	}
}



void NumberRenderObject::SetValue(const std::string_view& _Value)
{
	Value = _Value;
	//std::string Num = std::to_string(Value);


	for (size_t i = 0; i < Value.size() - NumberRenders.size(); ++i)
	{
		std::shared_ptr< GameEngineUIRenderer> NewNumber = CreateComponent< GameEngineUIRenderer>(CupHeadRendererOrder::UI);
		NumberRenders.push_back(NewNumber);
	}


	for (size_t i = 0; i < Value.size(); ++i)
	{
		Setting(i, Value[i]);
	}
	if (NumberRenders.size() > Value.size())
	{
		for (size_t i = Value.size(); i < NumberRenders.size(); ++i)
		{
			NumberRenders[i]->Off();
		}
	}
	Sort();
}


void NumberRenderObject::Sort()
{
	//std::string Num = std::to_string(Value);
	float4 StartPos = float4::Zero;
	int LenNum = static_cast<int>(Value.length());
	switch (SortOption)
	{
	case SortNumber::LEFT:
		break;
	case SortNumber::CENTER:
		StartPos.x = -(LenNum - 1) * NumXSize / 2;
		break;
	case SortNumber::RIGHT:
		StartPos.x = -(LenNum - 1) * NumXSize;
		break;
	default:
		break;
	}
	for (int i = 0; i < LenNum; ++i)
	{
		NumberRenders[i]->GetTransform()->SetLocalPosition(StartPos);
		StartPos.x += NumXSize;
	}
}
