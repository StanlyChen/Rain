#include "BackgroundImg.h"
#include <iostream>

namespace Rain
{

	void BackgroundImage::create(RainOpenGLFuncs* pContext)
	{
		m_renderMothod = new BackgroundRenderMethod();
		m_renderMothod->create(pContext);

		float quad_vertices[] = {
			-0.5f,  -0.5f, 1.0f,
			 0.f,  0.5f, 1.0f,
			0.5f,-0.5f,1,
			};

		pContext->glGenBuffers(1, &m_vbo);
		pContext->glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		pContext->glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertices), quad_vertices, GL_STATIC_DRAW);
	}

	void BackgroundImage::render(RainOpenGLFuncs* pContext)
	{
		m_renderMothod->bind(pContext);
		pContext->glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

		pContext->glEnableVertexAttribArray(0);
		pContext->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

		
		pContext->glDrawArrays(GL_TRIANGLES, 0, 3);
		

		pContext->glDisableVertexAttribArray(0);
		m_renderMothod->unbind(pContext);
	}


	void BackgroundImage::destory(RainOpenGLFuncs* pContext)
	{
		pContext->glDeleteBuffers(1, &m_vbo);
		m_vbo = 0;
	}

	void BackgroundRenderMethod::create(RainOpenGLFuncs* pContext)
	{
		const char* vertexShaderStr = R"(
			#version 150 core

			in vec3 position;

			void main()
			{
				gl_Position = vec4(position, 1.0);
			}
		)";

		const char* fragShaderStr = R"(
			#version 150 core

			out vec4 outColor;

			void main()
			{
				outColor = vec4(1.0, 1.0, 1.0, 1.0);
			}
		)";

		ShaderCompileResult ret = buildShaderProgram(pContext, vertexShaderStr, fragShaderStr);
		if (ret.bSuccess)
		{
			m_vertexShader = ret.vertexShader;
			m_fragShader = ret.fragShader;
			m_shaderProgram = ret.program;
		}
		else
		{
			std::cout << ret.errorMessage << std::endl;
		}
	}

	void BackgroundRenderMethod::bind(RainOpenGLFuncs* pContext)
	{
		pContext->glUseProgram(m_shaderProgram);
	}

	void BackgroundRenderMethod::unbind(RainOpenGLFuncs* pContext)
	{
		pContext->glUseProgram(0);
	}
}