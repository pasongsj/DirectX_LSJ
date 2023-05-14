#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class SagittariusArrow : public GameEngineActor
{
public:
	// constrcuter destructer
	SagittariusArrow();
	~SagittariusArrow();

	// delete Function
	SagittariusArrow(const SagittariusArrow& _Other) = delete;
	SagittariusArrow(SagittariusArrow&& _Other) noexcept = delete;
	SagittariusArrow& operator=(const SagittariusArrow& _Other) = delete;
	SagittariusArrow& operator=(SagittariusArrow&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
		 
private:
	std::shared_ptr<class GameEngineSpriteRenderer> ArrowRender = nullptr;
	void MakeSprite();

};

