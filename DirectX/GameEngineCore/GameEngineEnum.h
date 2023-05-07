#pragma once

enum class ShaderType
{
	None,
	Vertex,
	Pixel,
};

enum class CameraType
{
	None,
	Perspective,
	Orthogonal,
};

enum class CupHeadRendererOrder
{
	BackGround,
	Monster,
	Boss,
	Player,
	UI,
	MAX,
};