#pragma once
#include <GameEngineCore/GameEngineUIRenderer.h>

// ���� :


class GameContentsUIRenderer : public GameEngineUIRenderer
{
public:
	// constrcuter destructer
	GameContentsUIRenderer();
	~GameContentsUIRenderer();

	// delete Function
	GameContentsUIRenderer(const GameContentsUIRenderer& _Other) = delete;
	GameContentsUIRenderer(GameContentsUIRenderer&& _Other) noexcept = delete;
	GameContentsUIRenderer& operator=(const GameContentsUIRenderer& _Other) = delete;
	GameContentsUIRenderer& operator=(GameContentsUIRenderer&& _Other) noexcept = delete;

	void SetAtlasData(float _StartX, float _StartY, float _SizeX, float _SizeY);
	void SetCutTexture(const std::string_view& _Name, float _StartX, float _StartY, float _SizeX, float _SizeY);
	void SetScaleToCutTexture(const std::string_view& _Name, float _StartX, float _StartY, float _SizeX, float _SizeY);


protected:
	void Update(float _DeltaTime) override;

private:

};

