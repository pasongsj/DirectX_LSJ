#include "PrecompileHeader.h"
#include "GameEngineSpriteRenderer.h"
#include "GameEngineTexture.h"

void GameEngineSpriteRenderer::FrameAnimation::Render(float _DeltaTime)
{
	CurrentTime -= _DeltaTime;

	if (CurrentTime <= 0.0f)
	{
		++CurrentIndex;

		if (TextureName.size() <= CurrentIndex)
		{
			if (true == Loop)
			{
				CurrentIndex = 0;
			}
			else {
				CurrentIndex = static_cast<int>(TextureName.size()) - 1;
			}
		}

		CurrentTime += TextureTime[CurrentIndex];
	}
}

bool GameEngineSpriteRenderer::FrameAnimation::IsEnd()
{
	int Value = (static_cast<int>(TextureName.size()) - 1);
	return CurrentIndex == Value;
}






GameEngineSpriteRenderer::GameEngineSpriteRenderer()
{
}

GameEngineSpriteRenderer::~GameEngineSpriteRenderer()
{
}


void GameEngineSpriteRenderer::Start()
{
	GameEngineRenderer::Start();

	SetPipeLine("2DTexture");
}


void GameEngineSpriteRenderer::Render(float _Delta)
{
	if (nullptr != CurrentAnimation)
	{
		CurrentAnimation->Render(_Delta);
		TaxtureIndex = CurrentAnimation->CurrentIndex;
		SetScaleToTexture(CurrentAnimation->TextureName[TaxtureIndex]);
	}

	GameEngineRenderer::Render(_Delta);
}

void GameEngineSpriteRenderer::SetTexture(const std::string_view& _Name)
{
	GetShaderResHelper().SetTexture("DiffuseTex", _Name);
}

void GameEngineSpriteRenderer::SetScaleToTexture(const std::string_view& _Name)
{
	GetShaderResHelper().SetTexture("DiffuseTex", _Name);
	std::shared_ptr<GameEngineTexture> FindTex = GameEngineTexture::Find(_Name);
	if (nullptr == FindTex)
	{
		MsgAssert("존재하지 않는 이미지 입니다.");
		return;
	}

	float4 Scale = float4(static_cast<float>(FindTex->GetWidth()), static_cast<float>(FindTex->GetHeight()),1);
	GetTransform()->SetLocalScale(Scale);
}

void GameEngineSpriteRenderer::SetFlipX()
{
	float4 LocalScale = GetTransform()->GetLocalScale();
	LocalScale.x = -LocalScale.x;
	GetTransform()->SetLocalScale(LocalScale);
}

void GameEngineSpriteRenderer::SetFlipY()
{

	float4 LocalScale = GetTransform()->GetLocalScale();
	LocalScale.y = -LocalScale.y;
	GetTransform()->SetLocalScale(LocalScale);
}


//class FrameAnimationParameter
//{
//public:
//	std::string_view AnimationName = "";
//	std::string_view TextureName = "";
//
//	int Start = 0;
//	int End = 0;
//	int CurrentIndex = 0;
//	float InterTime = 0.1f;
//	bool Loop = true;
//	std::vector<int> FrameIndex = std::vector<int>();
//	std::vector<float> FrameTime = std::vector<float>();
//};

void GameEngineSpriteRenderer::CreateAnimation(const FrameAnimationParameter& _Paramter)
{
	// 존재하는 애니메이션인지 체크
	std::string UpperAnimationName = GameEngineString::ToUpper(_Paramter.AnimationName);
	if (Animation.end() != Animation.find(UpperAnimationName) || 0 == UpperAnimationName.size())
	{
		MsgAssert("이미 존재하거나 입력하지 않은 이름의 애니메이션 입니다." + UpperAnimationName);
	}

	FrameAnimation& NewAnimation = Animation[UpperAnimationName];

	std::string UpperTextureName = GameEngineString::ToUpper(_Paramter.TextureName);

	size_t MaxLen = std::to_string(_Paramter.End).size();
	for (int frame = _Paramter.Start; frame <= _Paramter.End; ++frame)
	{
		std::string EachTextureName = UpperTextureName;
		for (size_t Zcnt = 0; Zcnt < (MaxLen)-std::to_string(frame).size(); Zcnt++)
		{
			EachTextureName += '0';
		}
		EachTextureName += (std::to_string(frame) + ".PNG");
		std::shared_ptr<GameEngineTexture> FindTex = GameEngineTexture::Find(EachTextureName);
		if (nullptr == FindTex)
		{
			Animation.erase(UpperAnimationName);
			MsgAssert("존재하지 않는 이미지 입니다.");
			return;
		}
		NewAnimation.TextureName.push_back(EachTextureName);
	}
	
	// 각 프레임별 시간을 계산한다.
	if (0 != _Paramter.FrameTime.size())
	{
		NewAnimation.TextureTime = _Paramter.FrameTime;
	}
	else
	{
		for (int i = 0; i < NewAnimation.TextureName.size(); ++i)
		{
			NewAnimation.TextureTime.push_back(_Paramter.InterTime);
		}
	}

	NewAnimation.Loop = _Paramter.Loop;
}

void GameEngineSpriteRenderer::ChangeAnimation(const std::string_view& _AnimationName)
{
	std::string UpperName = GameEngineString::ToUpper(_AnimationName);

	if (Animation.end() == Animation.find(UpperName))
	{
		MsgAssert("존재하지 않는 애니메이션으로 바꾸려고 했습니다." + UpperName);
	}

	if (CurrentAnimation == &Animation[UpperName])
	{
		return;
	}

	CurrentAnimation = &Animation[UpperName];

	CurrentAnimation->CurrentIndex = 0;
	// 0.1
	CurrentAnimation->CurrentTime = 0.0f;
}

bool GameEngineSpriteRenderer::IsAnimationEnd()
{
	return CurrentAnimation->IsEnd();
}
