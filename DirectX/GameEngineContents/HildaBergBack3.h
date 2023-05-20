#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <queue>

// Ό³Έν :
class HildaBergBack3 : public GameEngineActor
{
public:
	// constrcuter destructer
	HildaBergBack3();
	~HildaBergBack3();

	// delete Function
	HildaBergBack3(const HildaBergBack3& _Other) = delete;
	HildaBergBack3(HildaBergBack3&& _Other) noexcept = delete;
	HildaBergBack3& operator=(const HildaBergBack3& _Other) = delete;
	HildaBergBack3& operator=(HildaBergBack3&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;


private:
	std::queue< std::shared_ptr<class GameEngineSpriteRenderer>> LargeHill;


	int LastX = 0;

	int BGRange = 0;
	int BGLimit = 0;

	int TextureIndex = 0;

	void SetNextBackGround();
};

