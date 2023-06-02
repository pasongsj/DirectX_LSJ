#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class PeashotFX : public GameEngineActor
{
public:
	// constrcuter destructer
	PeashotFX();
	~PeashotFX();

	// delete Function
	PeashotFX(const PeashotFX& _Other) = delete;
	PeashotFX(PeashotFX&& _Other) noexcept = delete;
	PeashotFX& operator=(const PeashotFX& _Other) = delete;
	PeashotFX& operator=(PeashotFX&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	std::shared_ptr<class GameEngineSpriteRenderer> ExplodeFX = nullptr;
	void MakeSprite();


};

