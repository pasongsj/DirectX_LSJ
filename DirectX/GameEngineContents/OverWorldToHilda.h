#pragma once
#include "OverWorldInteractObject.h"
// Ό³Έν :
class OverWorldToHilda : public OverWorldInteractObject
{
public:
	// constrcuter destructer
	OverWorldToHilda();
	~OverWorldToHilda();

	// delete Function
	OverWorldToHilda(const OverWorldToHilda& _Other) = delete;
	OverWorldToHilda(OverWorldToHilda&& _Other) noexcept = delete;
	OverWorldToHilda& operator=(const OverWorldToHilda& _Other) = delete;
	OverWorldToHilda& operator=(OverWorldToHilda&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> BlimpRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> FRender = nullptr;
	void MakeSprite();
};

