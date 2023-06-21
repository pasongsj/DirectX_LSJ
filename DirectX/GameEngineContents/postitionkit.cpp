#include "PrecompileHeader.h"
#include "postitionkit.h"
#include "Player.h"

postitionkit::postitionkit() 
{
}

postitionkit::~postitionkit() 
{
}

void postitionkit::OnGUI(std::shared_ptr<GameEngineLevel> Level, float _DeltaTime)
{
	float4 Pos = float4::Zero;
	if (nullptr != Player::MainPlayer)
	{
		float4 Pos = Player::MainPlayer->GetTransform()->GetWorldPosition();
		ImGui::Text("Player Position - X : %f, Y : %f, Z : %f", Pos.x, Pos.y, Pos.z);

	}
	std::shared_ptr< GameEngineTexture> ColMapTexture = GameEngineTexture::Find("Overworld_Map.png");
	if (nullptr != ColMapTexture)
	{
		GameEnginePixelColor Color = ColMapTexture->GetPixel(Pos.ix(), -Pos.iy());
		ImGui::Text("Pixel Color - r : %f, g : %f, b : %f, a : %f", Color.r, Color.g, Color.b, Color.a);
	}
}