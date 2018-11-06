#pragma once
#include "IRenderable.h"
#include "IRenderMethod.h"

namespace Rain
{
	class BackgroundImage : public IRenderable
	{
	public:
		void render(RainOpenGLFuncs* pContext) override;
		void create(RainOpenGLFuncs* pContext)  override;
		void destory(RainOpenGLFuncs* pContext) override;

	private:
		GLuint m_vbo;
	};

	class BackgroundRenderMethod : public IRenderMethod
	{

	};
}