#pragma once
#include "RainOpenGL.h"

namespace Rain
{
    class RainRenderingWindow;

	enum RainPrimType
	{
		Point,
		Line,
		Triangle,
		Quad,
	};


	class IRenderable
	{
	public:
		virtual ~IRenderable() {};
		virtual void render(RainRenderingWindow* pContext) = 0 {};
	};
}