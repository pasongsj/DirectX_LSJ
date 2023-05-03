#pragma once

// Ό³Έν :
class Sagittarius
{
public:
	// constrcuter destructer
	Sagittarius();
	~Sagittarius();

	// delete Function
	Sagittarius(const Sagittarius& _Other) = delete;
	Sagittarius(Sagittarius&& _Other) noexcept = delete;
	Sagittarius& operator=(const Sagittarius& _Other) = delete;
	Sagittarius& operator=(Sagittarius&& _Other) noexcept = delete;

protected:

private:

};

