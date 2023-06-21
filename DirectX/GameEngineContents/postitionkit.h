#pragma once
#include <GameEngineCore/GameEngineGUI.h>
#include <GameEngineCore/GameEngineLevel.h>


// Ό³Έν :
class postitionkit : public GameEngineGUIWindow
{
public:
	// constrcuter destructer
	postitionkit();
	~postitionkit();

	// delete Function
	postitionkit(const postitionkit& _Other) = delete;
	postitionkit(postitionkit&& _Other) noexcept = delete;
	postitionkit& operator=(const postitionkit& _Other) = delete;
	postitionkit& operator=(postitionkit&& _Other) noexcept = delete;

	void OnGUI(std::shared_ptr<GameEngineLevel> Level, float _DeltaTime) override;


protected:

private:

};

