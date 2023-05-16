#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Constellation : public GameEngineActor
{
public:
	// constrcuter destructer
	Constellation();
	~Constellation();

	// delete Function
	Constellation(const Constellation& _Other) = delete;
	Constellation(Constellation&& _Other) noexcept = delete;
	Constellation& operator=(const Constellation& _Other) = delete;
	Constellation& operator=(Constellation&& _Other) noexcept = delete;
	
	void SetConstellation(const std::string_view& _Constellation);

protected:
	void Start() override;
	void Update(float _DeltaTime);

private:
	std::shared_ptr<class GameEngineSpriteRenderer> ConstellationRender = nullptr;

};

