#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineUIRenderer.h>

class ButtonTexturePara
{
public:
	std::string_view Release = "";
	std::string_view Hover = "";
	std::string_view Press = "";
	bool ScaleToTexture = false;
};


// 설명 :
class GameContentsButton : public GameEngineActor
{
public:
	// constrcuter destructer
	GameContentsButton();
	~GameContentsButton();

	// delete Function
	GameContentsButton(const GameContentsButton& _Other) = delete;
	GameContentsButton(GameContentsButton&& _Other) noexcept = delete;
	GameContentsButton& operator=(const GameContentsButton& _Other) = delete;
	GameContentsButton& operator=(GameContentsButton&& _Other) noexcept = delete;

	void SetEvent(std::function<void()> _Click)
	{
		Click = _Click;
	}

	std::shared_ptr<GameEngineUIRenderer> GetRender()
	{
		return Render;
	}

	void SetReleaseTexture(const std::string_view& _ImageName)
	{
		ReleaseImage = _ImageName;
	}

	void SetHoverTexture(const std::string_view& _ImageName)
	{
		HoverImage = _ImageName;
	}

	void SetPressTexture(const std::string_view& _ImageName)
	{
		PressImage = _ImageName;
	}
	void SetAllButtionTexture(const ButtonTexturePara& _Parameter)
	{
		if ("" != _Parameter.Release && nullptr == GameEngineTexture::Find(_Parameter.Release))
		{
			MsgAssert("존재하지 않는 버튼이미지를 설정하려 했습니다.");
			return;
		}
		ReleaseImage = _Parameter.Release;

		if ("" != _Parameter.Hover && nullptr == GameEngineTexture::Find(_Parameter.Hover))
		{
			MsgAssert("존재하지 않는 버튼이미지를 설정하려 했습니다.");
			return;
		}
		HoverImage = _Parameter.Hover;

		if ("" != _Parameter.Press && nullptr == GameEngineTexture::Find(_Parameter.Press))
		{
			MsgAssert("존재하지 않는 버튼이미지를 설정하려 했습니다.");
			return;
		}
		PressImage = _Parameter.Press;

		isScaleToTexture = _Parameter.ScaleToTexture;

	}
	void SetButtonRender(const std::string_view& _Name, bool _ScaleToTexture);

	void SetHover()
	{
		isHover = true;
	}

	void SetRelease()
	{
		isHover = false;
	}

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	bool isHover = false;
	bool isScaleToTexture = false;
	std::shared_ptr<GameEngineUIRenderer> Render;
	std::string_view ReleaseImage = "";
	std::string_view HoverImage = "";
	std::string_view PressImage = "";
	std::function<void()> Click;
};
