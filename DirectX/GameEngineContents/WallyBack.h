#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class WallyBackGroundSort
{
	TOP,
	BOT,
	CENTER,
};

// Ό³Έν :
class WallyBack : public GameEngineActor
{
public:
	// constrcuter destructer
	WallyBack();
	~WallyBack();

	// delete Function
	WallyBack(const WallyBack& _Other) = delete;
	WallyBack(WallyBack&& _Other) noexcept = delete;
	WallyBack& operator=(const WallyBack& _Other) = delete;
	WallyBack& operator=(WallyBack&& _Other) noexcept = delete;

	void Setting(const std::string_view& _TextureName, float _ZPos, float _InterVal, float _BackGroundMoveSpeed, WallyBackGroundSort _Sort);

protected:
	void Update(float _DeltaTime) override;

	std::shared_ptr<class GameEngineSpriteRenderer> MainBack = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> SubBack = nullptr;

	float Interval = 0.0f;
	float BackGroundMoveSpeed = 50.0f;

private:

};

