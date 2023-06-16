#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class ResultBackGround : public GameEngineActor
{
public:
	// constrcuter destructer
	ResultBackGround();
	~ResultBackGround();

	// delete Function
	ResultBackGround(const ResultBackGround& _Other) = delete;
	ResultBackGround(ResultBackGround&& _Other) noexcept = delete;
	ResultBackGround& operator=(const ResultBackGround& _Other) = delete;
	ResultBackGround& operator=(ResultBackGround&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DetatTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> BGRender = nullptr;

};

