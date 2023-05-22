#pragma once
#include "HildaBergBack.h"


// Ό³Έν : BackGround dark hill
class HildaBergBack1 : public HildaBergBack
{
public:
	// constrcuter destructer
	HildaBergBack1();
	~HildaBergBack1();

	// delete Function
	HildaBergBack1(const HildaBergBack1& _Other) = delete;
	HildaBergBack1(HildaBergBack1&& _Other) noexcept = delete;
	HildaBergBack1& operator=(const HildaBergBack1& _Other) = delete;
	HildaBergBack1& operator=(HildaBergBack1&& _Other) noexcept = delete;

protected:

	void Start() override;


private:


};

