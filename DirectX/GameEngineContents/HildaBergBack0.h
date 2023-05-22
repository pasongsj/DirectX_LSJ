#pragma once
#include "HildaBergBack.h"

// Ό³Έν : BackGround Sky, Cloud
class HildaBergBack0 : public HildaBergBack
{
public:
	// constrcuter destructer
	HildaBergBack0();
	~HildaBergBack0();

	// delete Function
	HildaBergBack0(const HildaBergBack0& _Other) = delete;
	HildaBergBack0(HildaBergBack0&& _Other) noexcept = delete;
	HildaBergBack0& operator=(const HildaBergBack0& _Other) = delete;
	HildaBergBack0& operator=(HildaBergBack0&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

