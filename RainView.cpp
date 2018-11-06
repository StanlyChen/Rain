#include "RainView.h"
#include "Layer.h"
#include "RainRenderingWindow.h"
#include "BackgroundImg.h"

namespace Rain{

	RainView::RainView()
	{
	}


	RainView::~RainView()
	{
	}

	RainRenderingWindow* RainView::getWindow()
	{
		return m_window;
	}

	void RainView::onRenderingWindowInit(RainRenderingWindow* pRenderingWindow)
	{
		if (m_window)
			throw std::exception("Program Error");

		m_window = pRenderingWindow;

		m_backgroundLayer = new Layer();
		LayerManager* pLayerManger = pRenderingWindow->getLayerManager();
		pLayerManger->insertBack(m_backgroundLayer);
		pLayerManger->setLayerName(m_backgroundLayer,BACKGROUND_LAYER_NAME);

		m_background = new BackgroundImage();
		m_background->create(pRenderingWindow);
		m_backgroundLayer->addRenderable(m_background);


		m_mainLayer = new Layer();
		pLayerManger->insertFront(m_mainLayer);
		pLayerManger->setLayerName(m_backgroundLayer, MAIN_LAYER_NAME);

		m_overlapLayer = new Layer();
		pLayerManger->insertFront(m_overlapLayer);
		pLayerManger->setLayerName(m_overlapLayer, OVERLAP_LAYER_NAME);
	}

	void RainView::onRenderingWindowUpdate(RainRenderingWindow* pView)
	{

	}

}

