#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class OverWorldBack : public GameEngineActor
{
public:
	// constrcuter destructer
	OverWorldBack();
	~OverWorldBack();

	// delete Function
	OverWorldBack(const OverWorldBack& _Other) = delete;
	OverWorldBack(OverWorldBack&& _Other) noexcept = delete;
	OverWorldBack& operator=(const OverWorldBack& _Other) = delete;
	OverWorldBack& operator=(OverWorldBack&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTiime) override;

private:
};

