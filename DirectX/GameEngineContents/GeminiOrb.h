#pragma once
#include <GameEngineCore/GameEngineActor.h>
// Ό³Έν :

class GeminiOrb : public GameEngineActor
{
public:
	// constrcuter destructer
	GeminiOrb();
	~GeminiOrb();

	// delete Function
	GeminiOrb(const GeminiOrb& _Other) = delete;
	GeminiOrb(GeminiOrb&& _Other) noexcept = delete;
	GeminiOrb& operator=(const GeminiOrb& _Other) = delete;
	GeminiOrb& operator=(GeminiOrb&& _Other) noexcept = delete;


protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> Orb = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> OrbAttackEffect = nullptr;

	bool isLoop = false;
	bool isEnd = false;
	
	float ScatterInterval = 0.12f;

	void MakeSprite();



	
};

