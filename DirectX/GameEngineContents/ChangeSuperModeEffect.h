#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class ChangeSuperModeEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	ChangeSuperModeEffect();
	~ChangeSuperModeEffect();

	// delete Function
	ChangeSuperModeEffect(const ChangeSuperModeEffect& _Other) = delete;
	ChangeSuperModeEffect(ChangeSuperModeEffect&& _Other) noexcept = delete;
	ChangeSuperModeEffect& operator=(const ChangeSuperModeEffect& _Other) = delete;
	ChangeSuperModeEffect& operator=(ChangeSuperModeEffect&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> FX;

	void MakeSprite();

};

