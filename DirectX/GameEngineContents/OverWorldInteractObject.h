#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� :
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

	inline void SetInteractFucntion(std::function<void()> _Func)
	{
		InteractFucntion = _Func;
	}

	inline void SetEnterFunction(std::function<void()> _Func)
	{
		EnterFucntion = _Func;
	}

	inline void DoInteractFucntion()
	{
		if (nullptr != InteractFucntion)
		{
			InteractFucntion();
			isInteract = true;
		}
	}

	inline bool GetisInteract()
	{
		return isInteract;
	}


protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	//std::shared_ptr<class GameEngineSpriteRenderer> FRender = nullptr; // ��ȣ�ۿ� ǥ��

	std::shared_ptr<class GameEngineSpriteRenderer> InteractRender = nullptr; // ��ȣ�ۿ��� ��ü ����
	std::shared_ptr<class GameEngineCollision> InteractCollision = nullptr; // ��ȣ�ۿ� ������ �ݸ���


	std::shared_ptr<class GameEngineUIRenderer> TitleCard = nullptr;

	std::function<void()> InteractFucntion = nullptr;
	std::function<void()> EnterFucntion = nullptr;
	bool isInteract = false;


};
