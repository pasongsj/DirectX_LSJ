#pragma once
#include "HildaBergBack.h"

// Ό³Έν :
class HildaBergBack2 : public HildaBergBack
{
public:
	// constrcuter destructer
	HildaBergBack2();
	~HildaBergBack2();

	// delete Function
	HildaBergBack2(const HildaBergBack2& _Other) = delete;
	HildaBergBack2(HildaBergBack2&& _Other) noexcept = delete;
	HildaBergBack2& operator=(const HildaBergBack2& _Other) = delete;
	HildaBergBack2& operator=(HildaBergBack2&& _Other) noexcept = delete;

protected:
	void Start() override;
	void ChangeNight() override;

private:
};

