#include "BackgroundImg.h"
#include <iostream>
#include <SOIL.h>
#include <QFile>

namespace Rain
{

	void BackgroundImage::create(RainOpenGLFuncs* pContext)
	{
		m_renderMothod = new BackgroundRenderMethod();
		m_renderMothod->create(pContext);

		float quad_vertices[] = {
			-1.f,  1.f, 1.0f,
			1.f,  1.f, 1.0f,
			1.f,-1.f,1.0f,
            -1.f, -1.f, 1.0f
			};

		pContext->glGenBuffers(1, &m_vbo);
		pContext->glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		pContext->glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertices), quad_vertices, GL_STATIC_DRAW);

		QFile bgImg(":/res/background.png");
		bgImg.open(QFile::ReadOnly);
		QByteArray dataArray = bgImg.readAll();
		int arraySize = dataArray.size();
		bgImg.close();
		m_texture = SOIL_load_OGL_texture_from_memory((unsigned char*)dataArray.constData(), dataArray.size(), 0, 0, SOIL_FLAG_MIPMAPS);
        //m_texture = SOIL_load_OGL_texture(R"(G:\Projs\gui\Rain\res\background.png)", 0, 0, SOIL_FLAG_MIPMAPS);


        pContext->glGenSamplers(1, &linearSampler);
        pContext->glSamplerParameteri(linearSampler, GL_TEXTURE_WRAP_S, GL_REPEAT);
        pContext->glSamplerParameteri(linearSampler, GL_TEXTURE_WRAP_T, GL_REPEAT);
        pContext->glSamplerParameteri(linearSampler, GL_TEXTURE_WRAP_R, GL_REPEAT);

        pContext->glSamplerParameteri(linearSampler, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        pContext->glSamplerParameteri(linearSampler, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        pContext->glSamplerParameteri(linearSampler, GL_TEXTURE_COMPARE_FUNC, GL_NEVER);

        pContext->glSamplerParameterf(linearSampler, GL_TEXTURE_MIN_LOD, 0);
        pContext->glSamplerParameterf(linearSampler, GL_TEXTURE_MAX_LOD, 0);
        

	}

	void BackgroundImage::render(RainOpenGLFuncs* pContext)
	{
		m_renderMothod->bind(pContext);
		pContext->glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

		pContext->glEnableVertexAttribArray(0);
		pContext->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

        pContext->glActiveTexture(GL_TEXTURE0);
        pContext->glBindTexture(GL_TEXTURE_2D, m_texture);
        pContext->glBindSampler(0, linearSampler);


        pContext->glUniform1i(m_renderMothod->getImgLoc(), 0);

        //pContext->glDisable(GL_CULL_FACE);
		pContext->glDrawArrays(GL_QUADS, 0, 4);
		

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
            out vec2 texcoord;

			void main()
			{
				gl_Position = vec4(position, 1.0);
                texcoord =  (position.xy  + vec2(1,1) )/2 ;
			}
		)";

		const char* fragShaderStr = R"(
			#version 150 core

            uniform sampler2D  bgImg;
            in vec2 texcoord;
			out vec4 outColor;
            

			void main()
			{
				outColor = vec4(texture( bgImg, texcoord).xyz,1);
                //outColor = vec4( texcoord,0,1);
			}
		)";

		ShaderCompileResult ret = buildShaderProgram(pContext, vertexShaderStr, fragShaderStr);
		if (ret.bSuccess)
		{
			m_vertexShader = ret.vertexShader;
			m_fragShader = ret.fragShader;
			m_shaderProgram = ret.program;

            m_img_loc = pContext->glGetUniformLocation(m_shaderProgram, "bgImg");
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