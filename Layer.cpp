#include <Layer.h>
#include <IRenderable.h>
#include "RainOpenGL.h"
#include "RainRenderingWindow.h"

namespace Rain
{

	void Layer::addRenderable(IRenderable* pRenderable)
	{
		m_renderList.push_back(pRenderable);
	}

	void Layer::removeRenderable(IRenderable* pRenderable)
	{
		m_renderList.erase(pRenderable);
	}

	void Layer::render(RainRenderingWindow* pContext)
	{
		for (auto renderObj : m_renderList)
		{
			renderObj->render(pContext);
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