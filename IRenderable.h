#pragma once
#include "RainOpenGL.h"

namespace Rain
{
    class RainRenderingWindow;
    class Layer;

	enum RainPrimType
	{
		Point,
		Line,
		Triangle,
		Quad,
	};

    struct RenderConext
    {
        RainRenderingWindow* pContext;
        Layer*               pLayer;
    };

	class IRenderable
	{
	public:
		virtual ~IRenderable() {};
		virtual void render(RenderConext context) = 0 {};
	};
}