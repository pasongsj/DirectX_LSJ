#include "PrecompileHeader.h"
#include "GameEngineSpriteRenderer.h"
#include "GameEngineTexture.h"

void GameEngineSpriteRenderer::FrameAnimation::Render(float _DeltaTime)
{
	CurrentTime -= _DeltaTime;

	if (CurrentTime <= 0.0f)
	{
		++CurrentIndex;

		if (FrameIndex.size() <= CurrentIndex)
		{
			if (true == Loop)
			{
				CurrentIndex = 0;
			}
			else {
				CurrentIndex = static_cast<int>(FrameIndex.size()) - 1;
			}
		}

		CurrentTime += FrameTime[CurrentIndex];
	}
}

bool GameEngineSpriteRenderer::FrameAnimation::IsEnd()
{
	int Value = (static_cast<int>(FrameIndex.size()) - 1);
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
		//CurrentAnimation->Render(_Delta);
		//int Frame = CurrentAnimation->FrameIndex[CurrentAnimation->CurrentIndex];
		//GameEngineTexture& Image = CurrentAnimation->Texture[Frame];

		//for (; NameStartIter != NameEndIter; ++NameStartIter)
		//{
		//	GameEngineTextureSetter& Setter = NameStartIter->second;
		//	Setter.Res = FindTex;

		//	// (NameStartIter->second).Res = FindTex;
		//}
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
		MsgAssert("�������� �ʴ� �̹��� �Դϴ�.");
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
	// �����ϴ� �ִϸ��̼����� üũ
	std::string UpperAnimationName = GameEngineString::ToUpper(_Paramter.AnimationName);
	if (Animation.end() != Animation.find(UpperAnimationName) || 0 == UpperAnimationName.size())
	{
		MsgAssert("�̹� �����ϰų� �Է����� ���� �̸��� �ִϸ��̼� �Դϴ�." + UpperAnimationName);
	}

	FrameAnimation& NewAnimation = Animation[UpperAnimationName];

	std::string UpperTextureName = GameEngineString::ToUpper(_Paramter.AnimationName);
	for (int frame = _Paramter.Start; frame <= _Paramter.End; ++frame)
	{
		std::shared_ptr<GameEngineTexture> FindTex = GameEngineTexture::Find(UpperTextureName + std::to_string(frame));
		if (nullptr == FindTex)
		{
			Animation.erase(UpperAnimationName);
			MsgAssert("�������� �ʴ� �̹��� �Դϴ�.");
			return;
		}
		NewAnimation.Texture.push_back(FindTex);
	}
	
	// �� �����Ӻ� �ð��� ����Ѵ�.
	if (0 != _Paramter.FrameTime.size())
	{
		NewAnimation.FrameTime = _Paramter.FrameTime;
	}
	else
	{
		for (int i = 0; i < NewAnimation.FrameIndex.size(); ++i)
		{
			NewAnimation.FrameTime.push_back(_Paramter.InterTime);
		}
	}

	NewAnimation.Loop = _Paramter.Loop;
}

void GameEngineSpriteRenderer::ChangeAnimation(const std::string_view& _AnimationName)
{
	std::string UpperName = GameEngineString::ToUpper(_AnimationName);

	if (Animation.end() == Animation.find(UpperName))
	{
		MsgAssert("�������� �ʴ� �ִϸ��̼����� �ٲٷ��� �߽��ϴ�." + UpperName);
	}

	if (CurrentAnimation == &Animation[UpperName])
	{
		return;
	}

	CurrentAnimation = &Animation[UpperName];

	CurrentAnimation->CurrentIndex = 0;
	// 0.1
	CurrentAnimation->CurrentTime = CurrentAnimation->FrameTime[CurrentAnimation->CurrentIndex];
}

