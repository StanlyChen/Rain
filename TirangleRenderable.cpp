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
        pContext->glEnable(GL_DEPTH_TEST);
        
        pContext->glEnable(GL_POLYGON_OFFSET_FILL);
        pContext->glPolygonOffset(TRIANGLE_DEPTH_BIAS, TRIANGLE_DEPTH_BIAS);

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


			layout(location =0) in vec3 position;
			void main()
			{
				gl_Position = viewMatrix*vec4(position, 1.0);
			}
		)";

        const char* geomtryShaderStr = R"(
            #version 450 core

            layout(triangles) in;
            layout(triangle_strip, max_vertices = 3) out;

            uniform mat4x4 projMatrix;
            layout( location = 0 ) out vec3 outNormal;


            vec3 getNormal( vec3 v1, vec3 v2, vec3 v3)
            {
                return normalize( cross( v3-v1, v2 - v1));
            }

            void main()
            {
                outNormal = getNormal( vec3(gl_in[0].gl_Position) , vec3(gl_in[1].gl_Position), vec3(gl_in[2].gl_Position) );
                gl_Position = projMatrix*gl_in[0].gl_Position;
                EmitVertex(); 
                gl_Position = projMatrix*gl_in[1].gl_Position;
                EmitVertex(); 
                gl_Position = projMatrix*gl_in[2].gl_Position;
                EmitVertex();
                EndPrimitive();
            }

           )";

        const char* fragShaderStr = R"(
			#version 450 core

            layout( location = 0 ) in vec3 normal;
			layout( location  = 0) out vec4 outColor;
            
            uniform vec3 ambient = vec3(0.3, 0.3, 0.3);
            uniform vec3 diffuse_l = vec3(0.7, 0, 0 );

			void main()
			{
                float diffuse = abs( dot( vec3(0,0,1) , -normal) );
                outColor = vec4( ambient + diffuse_l*diffuse, 1 );
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


