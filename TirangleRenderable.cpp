#include "TirangleRenderable.h"
#include <iostream>
#include "RainRenderingWindow.h"

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

    void TriangleRenderable::render(RainRenderingWindow* pContext)
    {
        m_triangleRenderMethod->bind(pContext);
        m_triangleRenderMethod->updateParams(pContext, IRenderMethod::getAutoParams(pContext) );
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
        const char* vertexShaderStr = R"(
			#version 450 core

            uniform mat4x4 viewMatrix;
            uniform mat4x4 projMatrix;

			layout(location =0) in vec3 position;
			void main()
			{
				gl_Position = viewMatrix*projMatrix*vec4(position, 1.0);
			}
		)";

        const char* fragShaderStr = R"(
			#version 450 core

			layout( location  = 0) out vec4 outColor;
            
			void main()
			{
                outColor = vec4( 1,1,0, 1 );
			}
		)";

        ShaderCompileResult ret = buildShaderProgram(pContext, vertexShaderStr, fragShaderStr);
        if (ret.bSuccess)
        {
            m_vertexShader = ret.vertexShader;
            m_fragShader = ret.fragShader;
            m_shaderProgram = ret.program;

            m_viewMatrixLoc = pContext->glGetUniformLocation(m_shaderProgram, "viewMatrix");
            m_projMatrixLoc = pContext->glGetUniformLocation(m_shaderProgram, "projMatrix");
        }
        else
        {
            std::cout << ret.errorMessage << std::endl;
        }
    }


    void TriangleRenderMethod::bind(RainOpenGLFuncs* pContext)
    {
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
    }

    void TriangleRenderMethod::unbind(RainOpenGLFuncs* pContext)
    {
        pContext->glUseProgram(0);
    }


}


