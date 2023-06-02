#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class HIldaBigCloudFX : public GameEngineActor
{
public:
	// constrcuter destructer
	HIldaBigCloudFX();
	~HIldaBigCloudFX();

	// delete Function
	HIldaBigCloudFX(const HIldaBigCloudFX& _Other) = delete;
	HIldaBigCloudFX(HIldaBigCloudFX&& _Other) noexcept = delete;
	HIldaBigCloudFX& operator=(const HIldaBigCloudFX& _Other) = delete;
	HIldaBigCloudFX& operator=(HIldaBigCloudFX&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> ExplodeFX = nullptr;
	void MakeSprite();

};

