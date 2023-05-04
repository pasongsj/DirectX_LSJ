#pragma once
#include "GameEngineRenderer.h"

class FrameAnimationParameter
{
public:
	std::string_view AnimationName = "";
	std::string_view TextureName = "";

	int Start = 0;
	int End = 0;
	int CurrentIndex = 0;
	float InterTime = 0.1f;
	bool Loop = true;
	std::vector<int> FrameIndex = std::vector<int>();
	std::vector<float> FrameTime = std::vector<float>();
};

// Ό³Έν :
class GameEngineSpriteRenderer : public GameEngineRenderer
{
public:
	// constrcuter destructer
	GameEngineSpriteRenderer();
	~GameEngineSpriteRenderer();

	// delete Function
	GameEngineSpriteRenderer(const GameEngineSpriteRenderer& _Other) = delete;
	GameEngineSpriteRenderer(GameEngineSpriteRenderer&& _Other) noexcept = delete;
	GameEngineSpriteRenderer& operator=(const GameEngineSpriteRenderer& _Other) = delete;
	GameEngineSpriteRenderer& operator=(GameEngineSpriteRenderer&& _Other) noexcept = delete;

	void SetTexture(const std::string_view& _Name);
	void SetScaleToTexture(const std::string_view& _Name);

	void SetFlipX();
	void SetFlipY();

	void CreateAnimation(const FrameAnimationParameter& _Paramter);
	void ChangeAnimation(const std::string_view& _AnimationName);

protected:

	void Render(float _Delta) override;

private:
	void Start() override;

	int TaxtureIndex = 0;
	class FrameAnimation
	{
	public:
		//std::shared_ptr <GameEngineSpriteRenderer> Parent = nullptr;

		std::vector<std::string> TextureName;
		//std::vector<std::shared_ptr<GameEngineTexture>> Texture;
		//std::vector<int> TextureIndex;
		std::vector<float> TextureTime;
		int CurrentIndex = 0;
		float CurrentTime = 0.0f;
		bool Loop = true;

		bool IsEnd();

		void Render(float _DeltaTime);

		void Reset()
		{
			CurrentIndex = 0;
			CurrentTime = 0.0f;
		}
	};


	std::map<std::string, FrameAnimation> Animation;
	FrameAnimation* CurrentAnimation = nullptr;

};

