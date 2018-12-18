#pragma once
#include <string>
#include <set>
#include <map>
#include "Singleton.h"
#include "RainOpenGL.h"

namespace Rain
{
    class IRenderMethod;
    

    struct ShaderInfo
    {
        std::string name;
        std::string context;
        std::set<IRenderMethod*> rendermethods;
    };

    class ShaderManager
    {


    public:
		ShaderManager();

        std::set<std::string> listShaders() const;
        bool getShader(const std::string& name,  std::string& content) const;
        bool setShader( const std::string& name, std::string&& content, RainOpenGLFuncs* pContext);

        const std::string&  useShader(const std::string& name, IRenderMethod* user);
        bool  addShader(const std::string& name, std::string&& content);

		static ShaderManager& singleton();

    private:
        std::map<std::string, ShaderInfo> m_shaders;
    };
}

#define ADD_SHADER(x)  addShader( #x, x)

