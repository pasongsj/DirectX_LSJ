#pragma once
#include <GameEngineCore/GameEngineActor.h>

class TestRectRotation : public GameEngineActor
{
public:
	// constrcuter destructer
	TestRectRotation() ;
	~TestRectRotation();

	// delete Function
	TestRectRotation(const TestRectRotation& _Other) = delete;
	TestRectRotation(TestRectRotation&& _Other) noexcept = delete;
	TestRectRotation& operator=(const TestRectRotation& _Other) = delete;
	TestRectRotation& operator=(TestRectRotation&& _Other) noexcept = delete;

protected:
	void Update(float _Delta) override;
	void Render(float _Delta) override;

private:
	float Angle = 0.0f;
};

