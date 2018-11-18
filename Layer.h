#pragma once

#include  "OrderList.h"
#include <string>
#include "RainOpenGL.h"

namespace Rain
{
	class IRenderable;
	class LayerManager;
    class RainRenderingWindow;

	const std::string DefaultLayerName = "";
	const std::string BACKGROUND_LAYER_NAME = "BackgroundLayer";
	const std::string MAIN_LAYER_NAME = "MainLayer";
	const std::string OVERLAP_LAYER_NAME = "OverlapLayer";

	class Layer
	{
	public:
		void addRenderable(IRenderable* pRenderable);
		void removeRenderable(IRenderable* pRenderable);
		void render(RainRenderingWindow* pContext);
		std::string getName() const;


	private:
		util::OrderList<IRenderable*> m_renderList;
		std::string m_name = DefaultLayerName;

		void setLayerName(const std::string name);
		friend class LayerManager;	

		
	};

	class LayerManager
	{
	public:
		void insertFront(Layer* pLayer);
		void insertBack(Layer* pLayer);
		void removeLayer(Layer* pLayer);

		void setLayerName(Layer* pLayer, std::string name);
		Layer* getLayerByName(std::string name);
		util::OrderList<Layer*>::ORDER_TYPE getOrderedLayer();

	private:
		util::OrderList<Layer*> m_layers;
		
		;
	};


	
}