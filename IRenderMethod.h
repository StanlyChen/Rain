#pragma once
#include "RainOpenGL.h"

namespace Rain
{
	class IRenderMethod
	{
	public:
		virtual ~IRenderMethod() {};
		virtual void reload(RainOpenGLFuncs* pContext) {};
		virtual void create(RainOpenGLFuncs* pContext) {};
	};
}


