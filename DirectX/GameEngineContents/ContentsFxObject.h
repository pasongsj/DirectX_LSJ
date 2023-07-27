#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

// Ό³Έν :
class ContentsFxObject : public GameEngineActor
{
public:
	// constrcuter destructer
	ContentsFxObject();
	~ContentsFxObject();

	// delete Function
	ContentsFxObject(const ContentsFxObject& _Other) = delete;
	ContentsFxObject(ContentsFxObject&& _Other) noexcept = delete;
	ContentsFxObject& operator=(const ContentsFxObject& _Other) = delete;
	ContentsFxObject& operator=(ContentsFxObject&& _Other) noexcept = delete;
	
	std::shared_ptr<GameEngineSpriteRenderer> GetFxRender()
	{
		return FxRender;
	}

	void SetRenderType(CupHeadRendererOrder _Type)
	{
		FxRender = CreateComponent<GameEngineSpriteRenderer>(_Type);
	}

protected:
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> FxRender = nullptr;

};

