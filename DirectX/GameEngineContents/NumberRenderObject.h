#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class SortNumber
{
	LEFT,
	CENTER,
	RIGHT,
};
enum class NumberColor
{
	WHITE,
	YELLOW,
};
// Ό³Έν :
class NumberRenderObject : public GameEngineActor
{
public:
	// constrcuter destructer
	NumberRenderObject();
	~NumberRenderObject();

	// delete Function
	NumberRenderObject(const NumberRenderObject& _Other) = delete;
	NumberRenderObject(NumberRenderObject&& _Other) noexcept = delete;
	NumberRenderObject& operator=(const NumberRenderObject& _Other) = delete;
	NumberRenderObject& operator=(NumberRenderObject&& _Other) noexcept = delete;
	
	void SetValue(const std::string_view& _Value);


	inline void SetSortOption(SortNumber _Sort)
	{
		SortOption = _Sort;
		Sort();
	}

	inline void SetColorOption(NumberColor _Color)
	{
		ColorOption = _Color;
		SetValue(Value);
	}

protected:
	void Start() override;

private:
	std::string Value = "0";

	SortNumber SortOption = SortNumber::CENTER;
	NumberColor ColorOption = NumberColor::WHITE;
	const float NumXSize = 18.0f;

	std::vector<std::shared_ptr<class GameEngineUIRenderer>> NumberRenders;

	void Setting(size_t index, char _Num);
	void Sort();

};

