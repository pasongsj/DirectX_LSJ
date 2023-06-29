#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Wally1_House_Death : public GameEngineActor
{
public:
	// constrcuter destructer
	Wally1_House_Death();
	~Wally1_House_Death();

	// delete Function
	Wally1_House_Death(const Wally1_House_Death& _Other) = delete;
	Wally1_House_Death(Wally1_House_Death&& _Other) noexcept = delete;
	Wally1_House_Death& operator=(const Wally1_House_Death& _Other) = delete;
	Wally1_House_Death& operator=(Wally1_House_Death&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float MoveSpeed = 2000;
	std::shared_ptr<class GameEngineSpriteRenderer> BackRender		= nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> BottomRender	= nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> FrontRender		= nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> LeftRender		= nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> RightRender		= nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> TopRender		= nullptr;
	void MakeSprite();

};

