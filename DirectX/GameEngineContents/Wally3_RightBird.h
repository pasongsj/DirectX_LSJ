#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Wally3_RightBird : public GameEngineActor
{
	friend class Wally3;
public:
	// constrcuter destructer
	Wally3_RightBird();
	~Wally3_RightBird();

	// delete Function
	Wally3_RightBird(const Wally3_RightBird& _Other) = delete;
	Wally3_RightBird(Wally3_RightBird&& _Other) noexcept = delete;
	Wally3_RightBird& operator=(const Wally3_RightBird& _Other) = delete;
	Wally3_RightBird& operator=(Wally3_RightBird&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> BirdRender = nullptr;
	bool AvailableAttack = false;

	void MakeSprite();
	inline void SetAvailable(bool _Avail)
	{
		AvailableAttack = _Avail;
	}
};

