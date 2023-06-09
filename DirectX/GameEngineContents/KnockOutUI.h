#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class KnockOutUI : public GameEngineActor
{
public:
	// constrcuter destructer
	KnockOutUI();
	~KnockOutUI();

	// delete Function
	KnockOutUI(const KnockOutUI& _Other) = delete;
	KnockOutUI(KnockOutUI&& _Other) noexcept = delete;
	KnockOutUI& operator=(const KnockOutUI& _Other) = delete;
	KnockOutUI& operator=(KnockOutUI&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineUIRenderer> KnockOutRender = nullptr;

};

