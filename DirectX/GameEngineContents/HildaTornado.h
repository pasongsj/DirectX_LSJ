#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class HildaTornado : public GameEngineActor
{
public:
	// constrcuter destructer
	HildaTornado();
	~HildaTornado();

	// delete Function
	HildaTornado(const HildaTornado& _Other) = delete;
	HildaTornado(HildaTornado&& _Other) noexcept = delete;
	HildaTornado& operator=(const HildaTornado& _Other) = delete;
	HildaTornado& operator=(HildaTornado&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);

private:
	std::shared_ptr<class GameEngineSpriteRenderer> TornatoRender;
	bool isIntro = true;
	void MakeSprite();

};

