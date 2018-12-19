#pragma once
#include "IRenderable.h"
#include "RainTypes.h"
#include "IRenderMethod.h"

namespace Rain
{
    class TriangleRenderMethod;

    class TriangleRenderable : public IRenderable
    {
    public:
        TriangleRenderable();

        ~TriangleRenderable();


        void create(RainOpenGLFuncs* pContext, Point3DList vertices, IndexList indices);

        void render(RainRenderingWindow* pContext) override;

        void destroy(RainOpenGLFuncs* pContext);

    private:
        GLuint m_vao = 0;
        GLuint m_vbo = 0;
        GLuint m_ebo = 0;
        GLuint m_triangleCount = 0;
        TriangleRenderMethod* m_triangleRenderMethod;
    };

    class TriangleRenderMethod : public IRenderMethod
    {
    public:
        void create(RainOpenGLFuncs* pContext) override;
        void destory(RainOpenGLFuncs* pContext) override;
        void reload(RainOpenGLFuncs* pContext) override;

        void bind(RainOpenGLFuncs* pContext) override ;
        void unbind(RainOpenGLFuncs* pContext) override;
        void updateParams(RainOpenGLFuncs* pContext, ShaderParams& params) override;
    private:
        GLuint m_vertexShader = 0;
        GLuint m_fragShader = 0;
        GLuint m_gsShader = 0;
        GLuint m_shaderProgram = 0;

        GLint m_projMatrixLoc = -1;
        GLint m_viewMatrixLoc = -1;

        bool m_bNeedReload = false;
    };

}


