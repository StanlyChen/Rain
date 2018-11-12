#include "IRenderMethod.h"

namespace Rain
{
	bool IRenderMethod::compileShader(RainOpenGLFuncs* pContext, GLuint shader, const char* source, std::string& errorMsg)
	{
		pContext->glShaderSource(shader, 1, &source, NULL);
		pContext->glCompileShader(shader);
		GLint status;
		pContext->glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if (!status)
		{
			char buffer[512];
			pContext->glGetShaderInfoLog(shader, 512, NULL, buffer);
			errorMsg = std::string(buffer);
			return false;
		}
		else
		{
			return true;
		}
	}

	ShaderCompileResult IRenderMethod::buildShaderProgram(RainOpenGLFuncs* pContext, 
        const char* vertexStr /*= nullptr*/, const char* fragStr/* = nullptr*/, const char* gemoStr /*= nullptr*/,
        std::function<void(RainOpenGLFuncs*, ShaderCompileResult&)> preLinkCallback /*= {}*/)
	{
		ShaderCompileResult ret;
		if (!vertexStr && !fragStr && !gemoStr)
			return ret;

		ret.bSuccess = true;

		if (vertexStr)
		{
			ret.vertexShader = pContext->glCreateShader(GL_VERTEX_SHADER);
			ret.bSuccess &= compileShader(pContext, ret.vertexShader, vertexStr, ret.errorMessage);

			if (!ret.bSuccess)
				return clearFailedBuild(pContext, ret);
		}

		if (fragStr)
		{
			ret.fragShader = pContext->glCreateShader(GL_FRAGMENT_SHADER);
			ret.bSuccess &= compileShader(pContext, ret.fragShader, fragStr, ret.errorMessage);
			if (!ret.bSuccess)
				return clearFailedBuild(pContext, ret);

		}
			
		if( gemoStr  )
		{
			ret.geometryShader = pContext->glCreateShader(GL_GEOMETRY_SHADER);
			ret.bSuccess &= compileShader(pContext, ret.geometryShader, gemoStr, ret.errorMessage);
			if (!ret.bSuccess)
				return clearFailedBuild(pContext, ret);
		}

		ret.program = pContext->glCreateProgram();
		if(ret.vertexShader)
			pContext->glAttachShader(ret.program, ret.vertexShader);
		if (ret.geometryShader)
			pContext->glAttachShader(ret.program, ret.geometryShader);
		if(ret.fragShader)
			pContext->glAttachShader(ret.program, ret.fragShader);

        if (preLinkCallback)
            preLinkCallback(pContext, ret);

		pContext->glLinkProgram(ret.program);
		GLint status;
		pContext->glGetProgramiv(ret.program, GL_LINK_STATUS, &status);
		if (!status)
		{
			char buffer[512];
			pContext->glGetProgramInfoLog(ret.program, 512, NULL, buffer);
			ret.errorMessage = std::string(buffer);
			ret.bSuccess = false;
			return clearFailedBuild(pContext, ret);
		}

		return ret;
	}

	ShaderCompileResult IRenderMethod::clearFailedBuild(RainOpenGLFuncs* pContext, ShaderCompileResult& result)
	{
		if (result.bSuccess)
			return result;

		if (result.program)
			pContext->glDeleteProgram(result.program);

		if (result.vertexShader)
			pContext->glDeleteShader(result.vertexShader);

		if (result.geometryShader)
			pContext->glDeleteShader(result.geometryShader);

		if (result.fragShader)
			pContext->glDeleteShader(result.fragShader);

		return result;
	}
}