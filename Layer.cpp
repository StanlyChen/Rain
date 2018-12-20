#include <Layer.h>
#include <IRenderable.h>
#include "RainOpenGL.h"
#include "RainRenderingWindow.h"
#include "Light.h"
#include "const.h"

namespace Rain
{
    void Layer::addLight(const std::shared_ptr<Light>  light)
    {
        m_lights.push_back(light);
        m_bLightsDirty = true;
    }

	void Layer::addRenderable(IRenderable* pRenderable)
	{
		m_renderList.push_back(pRenderable);
	}

	void Layer::removeRenderable(IRenderable* pRenderable)
	{
		m_renderList.erase(pRenderable);
	}

    void Layer::_updateLights(RainRenderingWindow* pContext)
    {
        if (!m_bLightsDirty)
            return;
        m_bLightsDirty = false;
        if (m_lightsUBOId)
        {
            pContext->glBindBufferBase(GL_UNIFORM_BUFFER, LIGHTS_UBO_SLOT, 0);
            pContext->glDeleteBuffers(1, &m_lightsUBOId);
            m_lightsUBOId = 0;
        }

        if (m_lights.empty())
            return;

        GLint maxLightCount;
        pContext->glGetIntegerv(GL_MAX_LIGHTS, &maxLightCount);
        maxLightCount = std::min(maxLightCount, 8);

        GLint currentLightCount = m_lights.size();
        LightInfo lightsData[8]{};
        for (int i = 0; i < std::min( maxLightCount, (int)m_lights.size()); ++i)
        {
            m_lights[i]->apply(i, lightsData);
        }

        pContext->glGenBuffers(1, &m_lightsUBOId);



        if (m_lightsUBOId != 0)
        {
            pContext->glBindBuffer(GL_UNIFORM_BUFFER, m_lightsUBOId);
            pContext->glBufferData(GL_UNIFORM_BUFFER, 8*sizeof(float)*8, nullptr, GL_STATIC_DRAW);
            unsigned offset = 0;
            for (int i = 0; i < 8; ++i)
            {
                pContext->glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(float) * 4, lightsData[i].lightColor);
                offset += sizeof(float) * 4;
                pContext->glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(float) * 4, lightsData[i].lightDirection);
                offset += sizeof(float) * 4;
            }
            pContext->glBindBufferBase(GL_UNIFORM_BUFFER, LIGHTS_UBO_SLOT, m_lightsUBOId);
        }

        pContext->glBindBuffer(GL_UNIFORM_BUFFER, 0 );
    }

	void Layer::render(RainRenderingWindow* pContext)
	{
        _updateLights(pContext);

        RenderConext context;
        context.pContext = pContext;
        context.pLayer = this;
		for (auto renderObj : m_renderList)
		{
			renderObj->render(context);
		}
	}

	void Layer::setLayerName(const std::string name)
	{
		m_name = name;
	}

	std::string Layer::getName() const
	{
		return m_name;
	}

	void LayerManager::insertFront(Layer* pLayer)
	{
		m_layers.push_front(pLayer);
	}

	void LayerManager::insertBack(Layer* pLayer)
	{
		m_layers.push_back(pLayer);
	}

	void LayerManager::removeLayer(Layer* pLayer)
	{
		m_layers.erase(pLayer);
	}

	void LayerManager::setLayerName(Layer* pLayer, std::string name)
	{
		auto it = m_layers.find(pLayer);
		if( it != m_layers.end() )
		{	
			pLayer->setLayerName(name);
		}
	}

	Layer* LayerManager::getLayerByName(std::string name)
	{
		for ( auto pLayer : m_layers)
		{
			if (pLayer->getName() == name) {
				return pLayer;
			}
		}
		return nullptr;
	}


	util::OrderList<Layer*>::ORDER_TYPE LayerManager::getOrderedLayer()
	{
		util::OrderList<Layer*>::ORDER_TYPE retList;
		retList.assign(m_layers.begin(), m_layers.end());
		return retList;
	}
}