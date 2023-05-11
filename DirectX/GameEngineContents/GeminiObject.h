#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GeminiObject : public GameEngineActor
{
public:
	// constrcuter destructer
	GeminiObject();
	~GeminiObject();

	// delete Function
	GeminiObject(const GeminiObject& _Other) = delete;
	GeminiObject(GeminiObject&& _Other) noexcept = delete;
	GeminiObject& operator=(const GeminiObject& _Other) = delete;
	GeminiObject& operator=(GeminiObject&& _Other) noexcept = delete;


	void ChangeGeminiAnimation(const std::string_view& _Str, size_t _index);
	void ChangeGeminiAnimation(const std::string_view& _Str);

	bool isGeminiAnimationEnd();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	std::shared_ptr<class GameEngineSpriteRenderer> BossObject = nullptr;
	void MakeSprite();
};

