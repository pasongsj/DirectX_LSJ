#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class SupermodeShadowEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	SupermodeShadowEffect();
	~SupermodeShadowEffect();

	// delete Function
	SupermodeShadowEffect(const SupermodeShadowEffect& _Other) = delete;
	SupermodeShadowEffect(SupermodeShadowEffect&& _Other) noexcept = delete;
	SupermodeShadowEffect& operator=(const SupermodeShadowEffect& _Other) = delete;
	SupermodeShadowEffect& operator=(SupermodeShadowEffect&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> ShadowRender = nullptr;
};

