#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class PlanePlayer : public GameEngineActor
{
public:
	// constrcuter destructer
	PlanePlayer();
	~PlanePlayer();

	// delete Function
	PlanePlayer(const PlanePlayer& _Other) = delete;
	PlanePlayer(PlanePlayer&& _Other) noexcept = delete;
	PlanePlayer& operator=(const PlanePlayer& _Other) = delete;
	PlanePlayer& operator=(PlanePlayer&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineRenderer> Player;
};

