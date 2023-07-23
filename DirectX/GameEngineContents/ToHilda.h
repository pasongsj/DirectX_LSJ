#pragma once
#include "OverWorldInteractObject.h"

// Ό³Έν :
class ToHilda : public OverWorldInteractObject
{
public:
	// constrcuter destructer
	ToHilda();
	~ToHilda();

	// delete Function
	ToHilda(const ToHilda& _Other) = delete;
	ToHilda(ToHilda&& _Other) noexcept = delete;
	ToHilda& operator=(const ToHilda& _Other) = delete;
	ToHilda& operator=(ToHilda&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

