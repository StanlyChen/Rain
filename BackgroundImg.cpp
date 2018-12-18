#include "BackgroundImg.h"
#include <iostream>
#include <SOIL.h>
#include <QFile>
#include <QImage>
#include "RainRenderingWindow.h"
#include "ShaderManager.h"

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
            -1.f,  1.f, 1.0f,
            1.f,-1.f,1.0f,
            -1.0f, -1.0f, 1.0f
			};

        pContext->glGenVertexArrays(1, &m_vao);
        pContext->glGenBuffers(1, &m_vbo);

        pContext->glBindVertexArray(m_vao);
		pContext->glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		pContext->glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertices), quad_vertices, GL_STATIC_DRAW);
        pContext->glEnableVertexAttribArray(0);
        pContext->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
        pContext->glBindVertexArray(0);

      

		//QFile bgImg(":/res/background.png");
		//bgImg.open(QFile::ReadOnly);
		//QByteArray dataArray = bgImg.readAll();
		//int arraySize = dataArray.size();
		//bgImg.close();
		//m_texture = SOIL_load_OGL_texture_from_memory((unsigned char*)dataArray.constData(), dataArray.size(), 0, 0, SOIL_FLAG_MIPMAPS);
        //m_texture = SOIL_load_OGL_texture(R"(G:\Projs\gui\Rain\res\background.png)", 0, 0, SOIL_FLAG_MIPMAPS);

		QImage bgImg(":/res/background.png");
		QImage::Format format = bgImg.format();
		int width = bgImg.width();
		int height = bgImg.height();
		QImage convertedImg = bgImg.convertToFormat(QImage::Format::Format_RGBA8888);

        pContext->glGenTextures(1, &m_texture);
        pContext->glBindTexture(GL_TEXTURE_2D, m_texture);
        pContext->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, convertedImg.width(), convertedImg.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, convertedImg.bits());
		pContext->glGenerateMipmap(GL_TEXTURE_2D);

        pContext->glGenSamplers(1, &linearSampler);
        pContext->glSamplerParameteri(linearSampler, GL_TEXTURE_WRAP_S, GL_REPEAT);
        pContext->glSamplerParameteri(linearSampler, GL_TEXTURE_WRAP_T, GL_REPEAT);
        pContext->glSamplerParameteri(linearSampler, GL_TEXTURE_WRAP_R, GL_REPEAT);

        pContext->glSamplerParameteri(linearSampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        pContext->glSamplerParameteri(linearSampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

        pContext->glSamplerParameteri(linearSampler, GL_TEXTURE_COMPARE_FUNC, GL_NEVER);

        pContext->glSamplerParameterf(linearSampler, GL_TEXTURE_MIN_LOD, 0);
        pContext->glSamplerParameterf(linearSampler, GL_TEXTURE_MAX_LOD, GL_TEXTURE_MAX_LOD);
        

	}

	void BackgroundImage::render(RainRenderingWindow* pContext)
	{
		m_renderMothod->bind(pContext);
        pContext->glBindVertexArray(m_vao);
        pContext->glBindSampler(0, linearSampler);
        pContext->glBindTexture(GL_TEXTURE_2D, m_texture);

        ShaderParams params;
        params[BackgroundRMP_IMAGE_LOC] = 0;
        m_renderMothod->updateParams(pContext, params);
 
		pContext->glDrawArrays(GL_TRIANGLES, 0, 6);
		
		m_renderMothod->unbind(pContext);
	}


	void BackgroundImage::destory(RainOpenGLFuncs* pContext)
	{
		pContext->glDeleteBuffers(1, &m_vbo);
		m_vbo = 0;
	}

	void BackgroundRenderMethod::create(RainOpenGLFuncs* pContext)
	{
		const char* vertexShaderStr =  ShaderManager::singleton().useShader("bgImg_VS", this).c_str();
		const char* fragShaderStr = ShaderManager::singleton().useShader("bgImg_FS", this).c_str();

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

    void BackgroundRenderMethod::updateParams(RainOpenGLFuncs* pContext, ShaderParams& params)
    {
        pContext->glUniform1i(m_img_loc, boost::get<GLint>(params.at(BackgroundRMP_IMAGE_LOC)));
    }
    
	void BackgroundRenderMethod::unbind(RainOpenGLFuncs* pContext)
	{
		pContext->glUseProgram(0);
	}
}