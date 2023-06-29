#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Wally3_Pepper : public GameEngineActor
{
public:
	// constrcuter destructer
	Wally3_Pepper();
	~Wally3_Pepper();

	// delete Function
	Wally3_Pepper(const Wally3_Pepper& _Other) = delete;
	Wally3_Pepper(Wally3_Pepper&& _Other) noexcept = delete;
	Wally3_Pepper& operator=(const Wally3_Pepper& _Other) = delete;
	Wally3_Pepper& operator=(Wally3_Pepper&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> PepperRender = nullptr;

	void MakeSprite();

};

