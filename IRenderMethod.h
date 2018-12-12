#pragma once
#include "RainOpenGL.h"
#include <string>
#include <RainTypes.h>

namespace Rain
{
    class RainRenderingWindow;
	struct ShaderCompileResult
	{
		bool bSuccess = false;
		std::string errorMessage;
		GLuint vertexShader = 0;
		GLuint geometryShader = 0;
		GLuint fragShader = 0;
		GLuint program = 0;
	};

    const std::string RMP_ViewMatrix = "RMP::ViewMatrix";
    const std::string RMP_ProjMatrix = "RMP::ProjMatrix";
    const std::string RMP_InverseResolutionX = "RMP::InverseResolutionX";
    const std::string RMP_InverseResolutionY = "RMP::InverseResolutionY";


    const float POINT_DEPTH_BIAS = 0.0;
    const float Line_DEPTH_BIAS = 1.0f;
    const float TRIANGLE_DEPTH_BIAS = 2.0f;

	class IRenderMethod
	{
	public:
		virtual ~IRenderMethod() {};
		virtual void reload(RainOpenGLFuncs* pContext) {};
		virtual void create(RainOpenGLFuncs* pContext) {};
        virtual void bind(RainOpenGLFuncs* pContext) {};
        virtual void unbind(RainOpenGLFuncs* pContext) {};
        virtual void updateParams(RainOpenGLFuncs* pContext, ShaderParams& params) {};
		
        static  ShaderCompileResult buildShaderProgram(RainOpenGLFuncs* pContext, const char* vertexStr = nullptr, const char* fragStr = nullptr, const char* gemoStr = nullptr, std::function<void(RainOpenGLFuncs*, ShaderCompileResult&)> preLinkCallback = {} );
		static  ShaderCompileResult clearFailedBuild(RainOpenGLFuncs* pContext,  ShaderCompileResult& result);
		static bool compileShader(RainOpenGLFuncs* pContext, GLuint shader, const char* source, std::string& errorMsg);

        static ShaderParams getAutoParams(RainRenderingWindow* pRenderWindow);
	};
}


