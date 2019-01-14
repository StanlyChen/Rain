#include "TirangleRenderable.h"
#include <iostream>
#include "RainRenderingWindow.h"
#include "ShaderManager.h"

namespace Rain
{
    TriangleRenderable::TriangleRenderable()
    {
    }


    TriangleRenderable::~TriangleRenderable()
    {
    }

    void TriangleRenderable::create(RainOpenGLFuncs* pContext, Point3DList vertices, IndexList indices)
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

        m_triangleCount = indices.size() / 3;

        m_triangleRenderMethod = new TriangleRenderMethod();
        m_triangleRenderMethod->create(pContext);
    }

    void TriangleRenderable::render(RenderConext context)
    {
        auto pContext = context.pContext;
        pContext->glEnable(GL_DEPTH_TEST);
        
        pContext->glEnable(GL_POLYGON_OFFSET_FILL);
        pContext->glPolygonOffset(TRIANGLE_DEPTH_BIAS, TRIANGLE_DEPTH_BIAS);

        m_triangleRenderMethod->bind(pContext);
        m_triangleRenderMethod->updateParams(pContext, IRenderMethod::getAutoParams(context) );
        pContext->glBindVertexArray(m_vao);
        pContext->glDrawElements(GL_TRIANGLES, m_triangleCount * 3, GL_UNSIGNED_INT, 0);
        m_triangleRenderMethod->unbind(pContext);
    }

    void TriangleRenderable::destroy(RainOpenGLFuncs* pContext)
    {
        pContext->glDeleteVertexArrays(1, &m_vao);
        pContext->glDeleteBuffers(1, &m_vbo);
        pContext->glDeleteBuffers(1, &m_ebo);
    }


    void TriangleRenderMethod::create(RainOpenGLFuncs* pContext)
    {
		const char* vertexShaderStr = ShaderManager::singleton().useShader("Triangle_VS", this).c_str();
		const char* fragShaderStr = ShaderManager::singleton().useShader("Triangle_FS", this).c_str();

        ShaderCompileResult ret = buildShaderProgram(pContext, vertexShaderStr, fragShaderStr, nullptr);
        if (ret.bSuccess)
        {
            m_vertexShader = ret.vertexShader;
            m_fragShader = ret.fragShader;
            m_shaderProgram = ret.program;
            m_gsShader = ret.geometryShader;
            m_viewMatrixLoc = pContext->glGetUniformLocation(m_shaderProgram, "viewMatrix");
            m_projMatrixLoc = pContext->glGetUniformLocation(m_shaderProgram, "projMatrix");
            m_lightUBOLoc = pContext->glGetUniformBlockIndex(m_shaderProgram, "LightInfosBlock");
        }
        else
        {
            std::cout << ret.errorMessage << std::endl;
        }
    }

    void TriangleRenderMethod::destory(RainOpenGLFuncs* pContext)
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

    void TriangleRenderMethod::reload(RainOpenGLFuncs* pContext)
    {
        m_bNeedReload = true;
    }

    void TriangleRenderMethod::bind(RainOpenGLFuncs* pContext)
    {
        if (m_bNeedReload)
        {
            destory(pContext);
            create(pContext);
            m_bNeedReload = false;
        }

        pContext->glUseProgram(m_shaderProgram);
    }

    void TriangleRenderMethod::updateParams(RainOpenGLFuncs* pContext, ShaderParams& params)
    {
        if (m_viewMatrixLoc == -1
            || m_projMatrixLoc == -1)
            return;

        auto viewMatrix = boost::get<glm::mat4x4>(params.at(RMP_ViewMatrix));
        pContext->glUniformMatrix4fv(m_viewMatrixLoc, 1, false, reinterpret_cast<float*>(&viewMatrix));

        auto projMatrix =boost::get<glm::mat4x4>(params.at(RMP_ProjMatrix));
        pContext->glUniformMatrix4fv(m_projMatrixLoc, 1, false, reinterpret_cast<float*>(&projMatrix));
        
        int bindingPos = boost::get<int>(params.at(RMP_LightsInfo));
        pContext->glUniformBlockBinding(m_shaderProgram, m_lightUBOLoc, bindingPos);
    }

    void TriangleRenderMethod::unbind(RainOpenGLFuncs* pContext)
    {
        pContext->glUseProgram(0);
    }


}


