#include "PrecompileHeader.h"
#include "GeminiObject.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

GeminiObject::GeminiObject() 
{
}

GeminiObject::~GeminiObject() 
{
}

void GeminiObject::MakeSprite()
{
	if (nullptr == GameEngineSprite::Find("Gemini_Idle"))
	{

		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("ContentResources");
		NewDir.Move("ContentResources\\Texture\\stage1\\Boss\\Hilda\\Gemini");


		GameEngineSprite::LoadFolder("Gemini_Idle", NewDir.GetPlusFileName("Idle").GetFullPath());
		GameEngineSprite::LoadFolder("Gemini_AttackA", NewDir.GetPlusFileName("Attack (A)").GetFullPath());
		GameEngineSprite::LoadFolder("Gemini_AttackB", NewDir.GetPlusFileName("Attack (B)").GetFullPath());

	}
}

void GeminiObject::Start()
{
	MakeSprite();
	BossObject = CreateComponent<GameEngineSpriteRenderer>();
	BossObject->CreateAnimation({ .AnimationName = "Idle",  .SpriteName = "Gemini_Idle", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
	BossObject->CreateAnimation({ .AnimationName = "AttackA",  .SpriteName = "Gemini_AttackA",  .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	//BossB->CreateAnimation({ .AnimationName = "Idle",  .SpriteName = "gemini_idle_00", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
	BossObject->CreateAnimation({ .AnimationName = "AttackB",  .SpriteName = "Gemini_AttackB",  .FrameInter = 0.05f, .Loop = false , .ScaleToTexture = true });
}

void GeminiObject::Update(float _DeltaTime)
{
}

void GeminiObject::ChangeGeminiAnimation(const std::string_view& _Str, size_t _index)
{
	BossObject->ChangeAnimation(_Str,_index,false);
}
void GeminiObject::ChangeGeminiAnimation(const std::string_view& _Str)
{
	BossObject->ChangeAnimation(_Str);
}

bool GeminiObject::isGeminiAnimationEnd()
{
	return BossObject->IsAnimationEnd();
}