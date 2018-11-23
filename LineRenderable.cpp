#include "LineRenderable.h"
#include <iostream>
#include "RainRenderingWindow.h"

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
        pContext->glEnable(GL_DEPTH_TEST);
        m_lineRenderMethod->bind(pContext);
        m_lineRenderMethod->updateParams(pContext, IRenderMethod::getAutoParams(pContext));
        pContext->glBindVertexArray(m_vao);
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
        const char* vertexShaderStr = R"(
			#version 450 core

            uniform mat4x4 viewMatrix;
            uniform mat4x4 projMatrix;

			layout(location =0) in vec3 position;
			void main()
			{
				gl_Position = projMatrix*viewMatrix*vec4(position, 1.0);
			}
		)";

        const char* geomtryShaderStr = R"(
            #version 450 core

            layout(lines) in;
            layout(line_strip, max_vertices = 2) out;

            void main()
            {
                gl_Position = gl_in[0].gl_Position;
                EmitVertex(); 
                gl_Position = gl_in[1].gl_Position;
                EmitVertex(); 
                gl_Position = gl_in[1].gl_Position;
                EmitVertex();
                EndPrimitive();
            }

           )";

        const char* fragShaderStr = R"(
			#version 450 core
			layout( location  = 0) out vec4 outColor;
            
			void main()
			{
                outColor = vec4( 0,0,0, 1 );
			}
		)";

        ShaderCompileResult ret = buildShaderProgram(pContext, vertexShaderStr, fragShaderStr, geomtryShaderStr);
        if (ret.bSuccess)
        {
            m_vertexShader = ret.vertexShader;
            m_fragShader = ret.fragShader;
            m_shaderProgram = ret.program;
            m_gsShader = ret.geometryShader;
            m_viewMatrixLoc = pContext->glGetUniformLocation(m_shaderProgram, "viewMatrix");
            m_projMatrixLoc = pContext->glGetUniformLocation(m_shaderProgram, "projMatrix");
        }
        else
        {
            std::cout << ret.errorMessage << std::endl;
        }
    }


    void LineRenderMethod::bind(RainOpenGLFuncs* pContext)
    {
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
    }

    void LineRenderMethod::unbind(RainOpenGLFuncs* pContext)
    {
        pContext->glUseProgram(0);
    }


}


