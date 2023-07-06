#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class OverWorldInteractObject : public GameEngineActor
{
public:
	// constrcuter destructer
	OverWorldInteractObject();
	~OverWorldInteractObject();

	// delete Function
	OverWorldInteractObject(const OverWorldInteractObject& _Other) = delete;
	OverWorldInteractObject(OverWorldInteractObject&& _Other) noexcept = delete;
	OverWorldInteractObject& operator=(const OverWorldInteractObject& _Other) = delete;
	OverWorldInteractObject& operator=(OverWorldInteractObject&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void SetInteractRange(float _Range);
	bool GetisInteract()
	{
		return isInteract;
	}

private:
	std::shared_ptr<class GameEngineCollision> InteractCol = nullptr;
	bool isInteract = false;


};

