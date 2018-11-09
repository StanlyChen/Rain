#pragma once
#include "IRenderable.h"
#include "IRenderMethod.h"
#include "Singleton.h"

namespace Rain
{
	class BackgroundRenderMethod;

	class BackgroundImage : public IRenderable
	{
	public:
		void render(RainOpenGLFuncs* pContext) override;
		void create(RainOpenGLFuncs* pContext)  override;
		void destory(RainOpenGLFuncs* pContext) override;

	private:
		GLuint m_vbo = 0;
		BackgroundRenderMethod* m_renderMothod = nullptr;
	};

	class BackgroundRenderMethod : public IRenderMethod
	{
	public:
		void create(RainOpenGLFuncs* pContext) override;
		void bind(RainOpenGLFuncs* pContext);
		void unbind(RainOpenGLFuncs* pContext);

	private:
		GLuint m_vertexShader = 0;
		GLuint m_fragShader = 0;
		GLuint m_shaderProgram = 0;
	};
}