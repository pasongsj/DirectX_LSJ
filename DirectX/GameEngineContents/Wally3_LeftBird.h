#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Wally3_LeftBird : public GameEngineActor
{
	friend class Wally3;
public:
	// constrcuter destructer
	Wally3_LeftBird();
	~Wally3_LeftBird();

	// delete Function
	Wally3_LeftBird(const Wally3_LeftBird& _Other) = delete;
	Wally3_LeftBird(Wally3_LeftBird&& _Other) noexcept = delete;
	Wally3_LeftBird& operator=(const Wally3_LeftBird& _Other) = delete;
	Wally3_LeftBird& operator=(Wally3_LeftBird&& _Other) noexcept = delete;

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

