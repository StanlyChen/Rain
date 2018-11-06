#include "BackgroundImg.h"

namespace Rain
{

	void BackgroundImage::create(RainOpenGLFuncs* pContext)
	{
		float quad_vertices[] = {
			-1,1,1,
			1,1,1,
			1,-1,1,
			-1,-1,1,
			};

		pContext->glGenBuffers(1, &m_vbo);
		pContext->glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		pContext->glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertices), quad_vertices, GL_STATIC_DRAW);
	}

	void BackgroundImage::render(RainOpenGLFuncs* pContext)
	{
		pContext->glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glColor3b(124, 9, 58);
		glDrawArrays(GL_QUADS, 0, 4);
	}


	void BackgroundImage::destory(RainOpenGLFuncs* pContext)
	{
		pContext->glDeleteBuffers(1, &m_vbo);
		m_vbo = 0;
	}
}