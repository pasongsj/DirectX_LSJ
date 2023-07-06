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

private:

};

