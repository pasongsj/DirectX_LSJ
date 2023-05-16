#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class LoadingBackGround : public GameEngineActor
{
public:
	// constrcuter destructer
	LoadingBackGround();
	~LoadingBackGround();

	// delete Function
	LoadingBackGround(const LoadingBackGround& _Other) = delete;
	LoadingBackGround(LoadingBackGround&& _Other) noexcept = delete;
	LoadingBackGround& operator=(const LoadingBackGround& _Other) = delete;
	LoadingBackGround& operator=(LoadingBackGround&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

