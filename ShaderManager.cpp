#include "ShaderManager.h"
#include "IRenderMethod.h"
#include "const_ref.h"
namespace Rain
{

    std::set<std::string> ShaderManager::listShaders() const
    {
        std::set<std::string> result;
        for (const auto it : m_shaders)
            result.insert(it.first);
        return result;
    }

    bool ShaderManager::getShader(const std::string& name, std::string& content) const
    {
        const auto it = m_shaders.find(name);
        if (it != m_shaders.end())
        {
            content = it->second.context;
            return true;
        }
        else
        {
            return false;
        }

    }

    bool ShaderManager::setShader(const std::string& name, std::string&& content, RainOpenGLFuncs* pContext)
    {
        auto it = m_shaders.find(name);
        if (it != m_shaders.end())
        {
            it->second.context.swap(content);
            for (IRenderMethod* pMethod : it->second.rendermethods)
            {
                pMethod->reload(pContext);
            }
            return true;
        }
        else
        {
            return false;
        }
    }

    const std::string&  ShaderManager::useShader(const std::string& name, IRenderMethod* user)
    {
        auto it = m_shaders.find(name);
        if (it != m_shaders.end())
        {
            it->second.rendermethods.insert(user);
            return it->second.context;
        }
        else
        {
            return Rain::EmptyString;
        }
    }

    bool  ShaderManager::addShader(const std::string& name, std::string&& content)
    {
        auto it = m_shaders.find(name);
        if (it != m_shaders.end())
            return false;

        m_shaders.insert(std::make_pair(name, ShaderInfo{ name, content, std::set<IRenderMethod*>() }));
        return true;
    }
}



