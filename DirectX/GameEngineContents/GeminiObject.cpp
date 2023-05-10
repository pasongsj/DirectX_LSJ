#include "PrecompileHeader.h"
#include "GeminiObject.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

GeminiObject::GeminiObject() 
{
}

GeminiObject::~GeminiObject() 
{
}

void GeminiObject::Start()
{
	BossObject = CreateComponent<GameEngineSpriteRenderer>();
	BossObject->CreateAnimation({ .AnimationName = "Idle",  .TextureName = "gemini_idle_00", .Start = 1, .End = 32,.InterTime = 0.05f, .Loop = true });
	BossObject->CreateAnimation({ .AnimationName = "AttackA",  .TextureName = "gemini_a_attack_00", .Start = 1, .End = 17, .InterTime = 0.05f, .Loop = false });
	//BossB->CreateAnimation({ .AnimationName = "Idle",  .TextureName = "gemini_idle_00", .Start = 1, .End = 32,.InterTime = 0.05f, .Loop = true });
	BossObject->CreateAnimation({ .AnimationName = "AttackB",  .TextureName = "gemini_b_attack_00", .Start = 1, .End = 17, .InterTime = 0.05f, .Loop = false });
}

void GeminiObject::Update(float _DeltaTime)
{

}

void GeminiObject::ChangeGeminiAnimation(const std::string_view& _Str, int _index)
{
	BossObject->ChangeAnimation(_Str,_index);
}
void GeminiObject::ChangeGeminiAnimation(const std::string_view& _Str)
{
	BossObject->ChangeAnimation(_Str);
}

bool GeminiObject::isGeminiAnimationEnd()
{
	return BossObject->IsAnimationEnd();
}