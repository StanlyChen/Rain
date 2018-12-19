#include "LineRenderable.h"
#include <iostream>
#include "RainRenderingWindow.h"
#include "ShaderManager.h"

namespace Rain
{
    LineRenderable::LineRenderable()
    {
    }


    LineRenderable::~LineRenderable()
    {
    }

    void LineRenderable::create(RainOpenGLFuncs* pContext, Point3DList vertices, IndexList indices)
    {
        pContext->glGenVertexArrays(1, &m_vao);
        pContext->glBindVertexArray(m_vao);
        pContext->glGenBuffers(1, &m_vbo);

        pContext->glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        pContext->glBufferData(GL_ARRAY_BUFFER, sizeof(Point3D)*vertices.size(), vertices.data(), GL_STATIC_DRAW);
        pContext->glEnableVertexAttribArray(0);
        pContext->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
        pContext->glGenBuffers(1, &m_ebo);
        pContext->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        pContext->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned)*indices.size(), indices.data(), GL_STATIC_DRAW);

        pContext->glBindVertexArray(0);

        m_lineCount = indices.size() / 2;

        m_lineRenderMethod = new LineRenderMethod();
        m_lineRenderMethod->create(pContext);
    }

    void LineRenderable::render(RainRenderingWindow* pContext)
    {
        //pContext->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        //pContext->glEnable(GL_BLEND);

        pContext->glEnable(GL_DEPTH_TEST);
        m_lineRenderMethod->bind(pContext);
        m_lineRenderMethod->updateParams(pContext, IRenderMethod::getAutoParams(pContext));
        pContext->glBindVertexArray(m_vao);
        
        pContext->glEnable(GL_LINE_SMOOTH);
        pContext->glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

        pContext->glEnable(GL_POLYGON_OFFSET_FILL);
        pContext->glPolygonOffset(Line_DEPTH_BIAS, Line_DEPTH_BIAS);

        pContext->glDrawElements(GL_LINES, m_lineCount * 2, GL_UNSIGNED_INT, 0);
        m_lineRenderMethod->unbind(pContext);
    }

    void LineRenderable::destroy(RainOpenGLFuncs* pContext)
    {
        pContext->glDeleteVertexArrays(1, &m_vao);
        pContext->glDeleteBuffers(1, &m_vbo);
        pContext->glDeleteBuffers(1, &m_ebo);
    }


    void LineRenderMethod::create(RainOpenGLFuncs* pContext)
    {
		const char* vertexShaderStr = ShaderManager::singleton().useShader("Line_VS", this).c_str();
		const char* fragShaderStr = ShaderManager::singleton().useShader("Line_FS", this).c_str();
		const char* geomtryShaderStr = ShaderManager::singleton().useShader("Line_GS", this).c_str();

        ShaderCompileResult ret = buildShaderProgram(pContext, vertexShaderStr, fragShaderStr, geomtryShaderStr);
        if (ret.bSuccess)
        {
            m_vertexShader = ret.vertexShader;
            m_fragShader = ret.fragShader;
            m_shaderProgram = ret.program;
            m_gsShader = ret.geometryShader;
            m_viewMatrixLoc = pContext->glGetUniformLocation(m_shaderProgram, "viewMatrix");
            m_projMatrixLoc = pContext->glGetUniformLocation(m_shaderProgram, "projMatrix");
            m_lineWidthLoc = pContext->glGetUniformLocation(m_shaderProgram, "linewidth");
            m_inverseResulotionLoc = pContext->glGetUniformLocation(m_shaderProgram, "reverse_resolution");
            m_colorLoc = pContext->glGetUniformLocation(m_shaderProgram, "color");
        }
        else
        {
            std::cout << ret.errorMessage << std::endl;
        }
    }


    void LineRenderMethod::destory(RainOpenGLFuncs* pContext)
    {
        pContext->glUseProgram(0);
        pContext->glDeleteProgram(m_shaderProgram);
        m_shaderProgram = 0;
        pContext->glDeleteShader(m_vertexShader);
        m_vertexShader = 0;
        pContext->glDeleteShader(m_fragShader);
        m_fragShader = 0;
        pContext->glDeleteShader(m_gsShader);
        m_gsShader = 0;
    }

    void LineRenderMethod::reload(RainOpenGLFuncs* pContext)
    {
        m_bNeedReload = true;
    }

    void LineRenderMethod::bind(RainOpenGLFuncs* pContext)
    {
        if (m_bNeedReload)
        {
            destory(pContext);
            create(pContext);
            m_bNeedReload = false;
        }

        pContext->glUseProgram(m_shaderProgram);
    }

    void LineRenderMethod::updateParams(RainOpenGLFuncs* pContext, ShaderParams& params)
    {
        if (m_viewMatrixLoc == -1
            || m_projMatrixLoc == -1)
            return;

        auto viewMatrix = boost::get<glm::mat4x4>(params.at(RMP_ViewMatrix));
        pContext->glUniformMatrix4fv(m_viewMatrixLoc, 1, false, reinterpret_cast<float*>(&viewMatrix));

        auto projMatrix = boost::get<glm::mat4x4>(params.at(RMP_ProjMatrix));
        pContext->glUniformMatrix4fv(m_projMatrixLoc, 1, false, reinterpret_cast<float*>(&projMatrix));


        pContext->glUniform1f(m_lineWidthLoc, m_LineWidth);
        pContext->glUniform2f(m_inverseResulotionLoc,
            boost::get<float>(params.at(RMP_InverseResolutionX)),
            boost::get<float>(params.at(RMP_InverseResolutionY)));
        pContext->glUniform3f(m_colorLoc, m_color.r, m_color.g, m_color.b);
    }

    void LineRenderMethod::unbind(RainOpenGLFuncs* pContext)
    {
        pContext->glUseProgram(0);
    }


}


