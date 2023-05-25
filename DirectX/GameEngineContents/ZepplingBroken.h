#pragma once
#include <GameEngineCore/GameEngineActor.h>
// Ό³Έν :
class ZepplingBroken : public GameEngineActor
{
	friend class Zeplling;
public:
	// constrcuter destructer
	ZepplingBroken();
	~ZepplingBroken();

	// delete Function
	ZepplingBroken(const ZepplingBroken& _Other) = delete;
	ZepplingBroken(ZepplingBroken&& _Other) noexcept = delete;
	ZepplingBroken& operator=(const ZepplingBroken& _Other) = delete;
	ZepplingBroken& operator=(ZepplingBroken&& _Other) noexcept = delete;
	void SetColor(const std::string_view& _Color)
	{
		ZepColor = _Color;
		ChangeAnimationAll();
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;


private:

	std::string ZepColor = "Purple_";
	std::shared_ptr<class GameEngineSpriteRenderer> A = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> B = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> C = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> D = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> E = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> F = nullptr;

	float4 Dir = float4(0, 2);

	float4 DirA = float4::Zero;
	float4 DirB = float4::Zero;
	float4 DirC = float4::Zero;
	float4 DirD = float4::Zero;
	float4 DirE = float4::Zero;
	float4 DirF = float4::Zero;

	std::shared_ptr<class GameEngineSpriteRenderer> Spark = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> Explode = nullptr;

	void MakeSprite();

	void MovePieces(float _DeltaTime);
	
	void ChangeAnimationAll();
	bool CheckEnd();

	void MakePiecesDir();

};

