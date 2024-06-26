#pragma once
#include <GameEngineCore/GameEngineActor.h>
// ���� :
class TutorialBackGround : public GameEngineActor
{
	friend class TutorialLevel;
public:
	// constrcuter destructer
	TutorialBackGround();
	~TutorialBackGround();

	// delete Function
	TutorialBackGround(const TutorialBackGround& _Other) = delete;
	TutorialBackGround(TutorialBackGround&& _Other) noexcept = delete;
	TutorialBackGround& operator=(const TutorialBackGround& _Other) = delete;
	TutorialBackGround& operator=(TutorialBackGround&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	std::shared_ptr<class GameEngineSpriteRenderer> BackGround = nullptr;
	void MakeSprite();
	bool isBGAnimationEnd = false;

	std::shared_ptr<class PinkSphere> PinkObj = nullptr;
	float PinkObjTImer = 0.0f;


};

