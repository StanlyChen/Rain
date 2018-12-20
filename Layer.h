#pragma once

#include  "OrderList.h"
#include <string>
#include "RainOpenGL.h"
#include <vector>
#include "Light.h"
#include <memory>

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
        void addLight(const std::shared_ptr<Light> light);
        
    private:
        void _updateLights(RainRenderingWindow* pContext);

	private:
		util::OrderList<IRenderable*> m_renderList;
        std::vector< std::shared_ptr<Light> >   m_lights;

		std::string m_name = DefaultLayerName;
        GLuint m_lightsUBOId = 0;
        bool m_bLightsDirty = false;

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
	
	};


	
}