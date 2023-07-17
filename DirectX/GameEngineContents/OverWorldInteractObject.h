#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 :
class OverWorldInteractObject : public GameEngineActor
{
	friend class OverWorldLevel;
public:
	// constrcuter destructer
	OverWorldInteractObject();
	~OverWorldInteractObject();

	// delete Function
	OverWorldInteractObject(const OverWorldInteractObject& _Other) = delete;
	OverWorldInteractObject(OverWorldInteractObject&& _Other) noexcept = delete;
	OverWorldInteractObject& operator=(const OverWorldInteractObject& _Other) = delete;
	OverWorldInteractObject& operator=(OverWorldInteractObject&& _Other) noexcept = delete;

	void SetInteractFucntion(std::function<void()> _Func)
	{
		InteractFucntion = _Func;
	}

	void DoInteractFucntion()
	{
		if (nullptr != InteractFucntion)
		{
			InteractFucntion();
		}
	}


protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	//std::shared_ptr<class GameEngineSpriteRenderer> FRender = nullptr; // 상호작용 표시

	std::shared_ptr<class GameEngineSpriteRenderer> InteractRender = nullptr; // 상호작용할 객체 랜더
	std::shared_ptr<class GameEngineCollision> InteractCollision = nullptr; // 상호작용 범위용 콜리전
	std::function<void()> InteractFucntion = nullptr;


};

