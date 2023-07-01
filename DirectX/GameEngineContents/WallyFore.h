#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class WallyForeGroundSort
{
	TOP,
	BOT,
	CENTER,
};

// Ό³Έν :
class WallyFore : public GameEngineActor
{
public:
	// constrcuter destructer
	WallyFore();
	~WallyFore();

	// delete Function
	WallyFore(const WallyFore& _Other) = delete;
	WallyFore(WallyFore&& _Other) noexcept = delete;
	WallyFore& operator=(const WallyFore& _Other) = delete;
	WallyFore& operator=(WallyFore&& _Other) noexcept = delete;
	void Setting(const std::string_view& _TextureName, float _ZPos, float _InterVal, float _BackGroundMoveSpeed, WallyForeGroundSort _Sort);

protected:
	void Update(float _DeltaTime) override;

	std::shared_ptr<class GameEngineSpriteRenderer> MainBack = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> SubBack = nullptr;

	float Interval = 0.0f;
	float BackGroundMoveSpeed = 50.0f;

private:

};

