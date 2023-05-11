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
		NewDir.Move("ContentResources");
		NewDir.Move("Texture");
		NewDir.Move("stage1\\Boss\\Hilda\\Gemini");


		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Idle").GetFullPath(), "Gemini_Idle");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Attack (A)").GetFullPath(), "Gemini_AttackA");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Attack (B)").GetFullPath(), "Gemini_AttackB");

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