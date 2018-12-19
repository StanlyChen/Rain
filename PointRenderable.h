#pragma once

#include "IRenderable.h"
#include "RainTypes.h"
#include "IRenderMethod.h"

namespace Rain
{
    class PointRenderMethod;

    class PointRenderable : public IRenderable
    {
    public:
        PointRenderable();

        ~PointRenderable();


        void create(RainOpenGLFuncs* pContext, Point3DList vertices, IndexList indices);

        void render(RainRenderingWindow* pContext) override;

        void destroy(RainOpenGLFuncs* pContext);

    private:
        GLuint m_vao = 0;
        GLuint m_vbo = 0;
        GLuint m_ebo = 0;
        GLuint m_pointCount = 0;
        PointRenderMethod* m_pointRenderMethod;
    };

    class PointRenderMethod : public IRenderMethod
    {
    public:
        void create(RainOpenGLFuncs* pContext) override;
        void destory(RainOpenGLFuncs* pContext) override;
        void reload(RainOpenGLFuncs* pContext) override;
        void bind(RainOpenGLFuncs* pContext) override;
        void unbind(RainOpenGLFuncs* pContext) override;
        void updateParams(RainOpenGLFuncs* pContext, ShaderParams& params) override;

    private:
        float m_pointSize = 5;
        glm::vec3 m_color = { 1,1,0 };

        GLuint m_vertexShader = 0;
        GLuint m_fragShader = 0;
        GLuint m_gsShader = 0;
        GLuint m_shaderProgram = 0;

        GLint m_projMatrixLoc = -1;
        GLint m_viewMatrixLoc = -1;
        GLint m_pointSizeLoc = -1;
        GLint m_inverseResulotionLoc = -1;
        GLint m_colorLoc = -1;

        bool m_bNeedReload = false;
    };

}