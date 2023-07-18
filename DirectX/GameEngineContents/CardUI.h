#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 :
class CardUI : public GameEngineActor
{
	friend class PlayerUI;
public:
	// constrcuter destructer
	CardUI();
	~CardUI();

	// delete Function
	CardUI(const CardUI& _Other) = delete;
	CardUI(CardUI&& _Other) noexcept = delete;
	CardUI& operator=(const CardUI& _Other) = delete;
	CardUI& operator=(CardUI&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	
private:
	bool isFlip = false;
	bool isFront = false;
	bool isRot = false; // full Energy 인지 체크

	std::shared_ptr<class GameEngineUIRenderer> CardRender = nullptr;

	float4 CardSize = float4{ 20,30,1 };
	float4 Pivot = float4::Zero;

	inline void SetPivot(const float4& _Pos)
	{
		Pivot = _Pos;
	}
	void MakeSprite();

	void SetEnergy(int _En, bool Rot = false);
};

