#pragma once
#include "RainOpenGL.h"
#include <string>

namespace Rain
{
	struct ShaderCompileResult
	{
		bool bSuccess = false;
		std::string errorMessage;
		GLuint vertexShader = 0;
		GLuint geometryShader = 0;
		GLuint fragShader = 0;
		GLuint program = 0;
	};

	class IRenderMethod
	{
	public:
		virtual ~IRenderMethod() {};
		virtual void reload(RainOpenGLFuncs* pContext) {};
		virtual void create(RainOpenGLFuncs* pContext) {};

		
        static  ShaderCompileResult buildShaderProgram(RainOpenGLFuncs* pContext, const char* vertexStr = nullptr, const char* fragStr = nullptr, const char* gemoStr = nullptr, std::function<void(RainOpenGLFuncs*, ShaderCompileResult&)> preLinkCallback = {} );
		static  ShaderCompileResult clearFailedBuild(RainOpenGLFuncs* pContext,  ShaderCompileResult& result);
		static bool compileShader(RainOpenGLFuncs* pContext, GLuint shader, const char* source, std::string& errorMsg);
	};
}


