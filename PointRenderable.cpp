#include "PointRenderable.h"
#include <iostream>
#include "RainRenderingWindow.h"
#include "ShaderManager.h"

namespace Rain
{
    PointRenderable::PointRenderable()
    {
    }


    PointRenderable::~PointRenderable()
    {
    }

    void PointRenderable::create(RainOpenGLFuncs* pContext, Point3DList vertices, IndexList indices)
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

        m_pointCount = indices.size();

        m_pointRenderMethod = new PointRenderMethod();
        m_pointRenderMethod->create(pContext);
    }

    void PointRenderable::render(RenderConext context)
    {
        auto pContext = context.pContext;
        m_pointRenderMethod->bind(pContext);
        m_pointRenderMethod->updateParams(pContext, IRenderMethod::getAutoParams(context));
        pContext->glBindVertexArray(m_vao);

        pContext->glEnable(GL_POLYGON_OFFSET_FILL);
        pContext->glPolygonOffset(POINT_DEPTH_BIAS, POINT_DEPTH_BIAS);

        pContext->glDrawElements(GL_POINTS, m_pointCount , GL_UNSIGNED_INT, 0);
        m_pointRenderMethod->unbind(pContext);
    }

    void PointRenderable::destroy(RainOpenGLFuncs* pContext)
    {
        pContext->glDeleteVertexArrays(1, &m_vao);
        pContext->glDeleteBuffers(1, &m_vbo);
        pContext->glDeleteBuffers(1, &m_ebo);
    }


    void PointRenderMethod::create(RainOpenGLFuncs* pContext)
    {
		const char* vertexShaderStr = ShaderManager::singleton().useShader("Point_VS", this).c_str();
		const char* fragShaderStr = ShaderManager::singleton().useShader("Point_FS", this).c_str();
        const char* geomtryShaderStr = nullptr;// ShaderManager::singleton().useShader("Point_GS", this).c_str();

        ShaderCompileResult ret = buildShaderProgram(pContext, vertexShaderStr, fragShaderStr, geomtryShaderStr);
        if (ret.bSuccess)
        {
            m_vertexShader = ret.vertexShader;
            m_fragShader = ret.fragShader;
            m_shaderProgram = ret.program;
            m_gsShader = ret.geometryShader;
            m_viewMatrixLoc = pContext->glGetUniformLocation(m_shaderProgram, "viewMatrix");
            m_projMatrixLoc = pContext->glGetUniformLocation(m_shaderProgram, "projMatrix");
            m_pointSizeLoc = pContext->glGetUniformLocation(m_shaderProgram, "pointSize");
            m_inverseResulotionLoc = pContext->glGetUniformLocation(m_shaderProgram, "reverse_resolution");
            m_colorLoc = pContext->glGetUniformLocation(m_shaderProgram, "color");
        }
        else
        {
            std::cout << ret.errorMessage << std::endl;
        }
    }

    void PointRenderMethod::destory(RainOpenGLFuncs* pContext)
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

    void PointRenderMethod::reload(RainOpenGLFuncs* pContext)
    {
        m_bNeedReload = true;
    }

    void PointRenderMethod::bind(RainOpenGLFuncs* pContext)
    {
        if (m_bNeedReload)
        {
            destory(pContext);
            create(pContext);
            m_bNeedReload = false;
        }

        pContext->glUseProgram(m_shaderProgram);
    }

    void PointRenderMethod::updateParams(RainOpenGLFuncs* pContext, ShaderParams& params)
    {
        if (m_viewMatrixLoc == -1
            || m_projMatrixLoc == -1)
            return;

        auto viewMatrix = boost::get<glm::mat4x4>(params.at(RMP_ViewMatrix));
        pContext->glUniformMatrix4fv(m_viewMatrixLoc, 1, false, reinterpret_cast<float*>(&viewMatrix));

        auto projMatrix = boost::get<glm::mat4x4>(params.at(RMP_ProjMatrix));
        pContext->glUniformMatrix4fv(m_projMatrixLoc, 1, false, reinterpret_cast<float*>(&projMatrix));
        pContext->glUniform1f(m_pointSizeLoc, m_pointSize);
        pContext->glUniform2f(m_inverseResulotionLoc,
            boost::get<float>(params.at(RMP_InverseResolutionX)),
            boost::get<float>(params.at(RMP_InverseResolutionY)));
        pContext->glUniform3f(m_colorLoc, m_color.r, m_color.g, m_color.b);
    }

    void PointRenderMethod::unbind(RainOpenGLFuncs* pContext)
    {
        pContext->glUseProgram(0);
    }


}


