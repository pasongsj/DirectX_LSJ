#include "PrecompileHeader.h"
#include "HIldaMoonUFO.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>


HIldaMoonUFO::HIldaMoonUFO() 
{
}

HIldaMoonUFO::~HIldaMoonUFO() 
{
}

void HIldaMoonUFO::MakeSprite()
{
	if (nullptr == GameEngineSprite::Find("Hilda_UFO_Red"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources\\Texture\\stage1\\Boss\\Hilda\\Moon\\Projectiles\\UFO");

		GameEngineSprite::LoadFolder("Hilda_UFO_Red", Dir.GetPlusFileName("Red").GetFullPath());
		GameEngineSprite::LoadFolder("Hilda_UFO_Bronze", Dir.GetPlusFileName("Bronze").GetFullPath());
		GameEngineSprite::LoadFolder("Hilda_UFO_Beam", Dir.GetPlusFileName("Beam").GetFullPath());
	}
}

void HIldaMoonUFO::Start()
{
	//MakeSprite();
	UFORender = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::Enemy);
	UFORender->CreateAnimation({.AnimationName = "Red", .SpriteName = "Hilda_UFO_Red", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true});
	UFORender->CreateAnimation({.AnimationName = "Bronze", .SpriteName = "Hilda_UFO_Bronze", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true});

	UFOBeamRender = CreateComponent<GameEngineSpriteRenderer>(CupHeadRendererOrder::EnemyWeapon);
	UFOBeamRender->CreateAnimation({ .AnimationName = "Beam", .SpriteName = "Hilda_UFO_Beam", .FrameInter = 0.07f, .Loop = false, .ScaleToTexture = true });
	UFOBeamRender->ChangeAnimation("Beam");
	UFOBeamRender->Off();


	if (0 == (GameEngineRandom::MainRandom.RandomInt(0, 4) == 4))
	{
		UFORender->ChangeAnimation("Red");
	}
	else
	{
		UFORender->ChangeAnimation("Bronze");
	}
	Point[0] = float4(GameEngineWindow::GetScreenSize().hx(), 50, 500);
	Point[1] = float4(GameEngineWindow::GetScreenSize().hx()/2, 50, 500);
	Point[2] = float4(0, GameEngineWindow::GetScreenSize().hy() - 50, 500);
	Point[3] = float4(-GameEngineWindow::GetScreenSize().hx(), GameEngineWindow::GetScreenSize().hy() - 50);


	UFOBeamCollision = CreateComponent<GameEngineCollision>(CupHeadCollisionOrder::EnemyWeapon);
	//UFOBeamCollision->SetRenderScaleToCollision(UFOBeamRender);
	UFOBeamCollision->SetColType(ColType::AABBBOX2D);
	UFOBeamCollision->Off();
	//GetTransform()->SetLocalPosition(float4(0, 0, 500));
}

void HIldaMoonUFO::Update(float _DeltaTime)
{

	switch (index)
	{
	case 0:
	{
		GetTransform()->SetLocalPosition(Point[0]);
		++index;
		break;
	}
	case 1:
	case 2:
	{
		UFOMove(_DeltaTime);
		break;
	}
	case 3:
	{
		UFOMove(_DeltaTime);
		UFOBeamRender->GetTransform()->SetLocalPosition(float4(0,-UFOBeamRender->GetTransform()->GetLocalScale().hy()));
		GameEngineTransform* RenderData = UFOBeamRender->GetTransform();
		UFOBeamCollision->GetTransform()->SetLocalPosition(RenderData->GetLocalPosition());
		if (UFOBeamRender->GetCurrentFrame() < 5 || true == UFOBeamRender->IsAnimationEnd())
		{
			UFOBeamCollision->GetTransform()->SetLocalScale(RenderData->GetLocalScale() * 0.6f);

		}
		else
		{
			UFOBeamCollision->GetTransform()->SetLocalScale(RenderData->GetLocalScale() * 0.6f + float4(0, 200));

		}
		break;
	}
	default:
		Death();
		break;
	}

	if (true == UFOBeamCollision->IsUpdate() && true == CollisionPlayer(UFOBeamCollision))
	{
		UFOBeamCollision->Off();
		GameEngineSound::Play("blimp_moon_ufo_laser_fire_01.wav");
	}


}

void HIldaMoonUFO::UFOMove(float _DeltaTime)
{
	float4 Dir = Point[index] - GetTransform()->GetLocalPosition();
	Dir.z = 0;
	if (Dir.Size() < 5)
	{
		++index;
		if (3 == index)
		{
			UFOBeamRender->On();
			UFOBeamCollision->On();
		}
		return;
	}
	Dir.Normalize();
	GetTransform()->AddLocalPosition(Dir * UFOSpeed * _DeltaTime);
	return;
}