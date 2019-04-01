#pragma once
namespace dae
{
	enum CompType
	{
		BASECOMPONENT,
		TRANSFROMCOMPONENT,
		FPSCOMPONENT,
		TEXTCOMPONENT,
		RENDERCOMPONENT,
		TEXTURECOMPONENT
	};

	struct int2
	{
		int x{ 0 };
		int y{ 0 };
	};
}