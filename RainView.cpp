#include "RainView.h"
#include "Layer.h"
#include "RainRenderingWindow.h"
#include "BackgroundImg.h"
#include "IMesh.h"

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

	void RainView::onAfterRenderingWindowInit(RainRenderingWindow* pRenderingWindow)
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
		pLayerManger->setLayerName(m_mainLayer, MAIN_LAYER_NAME);

		m_overlapLayer = new Layer();
		pLayerManger->insertFront(m_overlapLayer);
		pLayerManger->setLayerName(m_overlapLayer, OVERLAP_LAYER_NAME);
	}

	void RainView::onBeforeRenderingWindowUpdate(RainRenderingWindow* pRenderingWIndow)
	{
        RainContext context;
        context.pGLContext = pRenderingWIndow;
        context.pView = this;

        for (auto it = m_newMeshes.begin(); it != m_newMeshes.end(); ++it)
        {
            m_meshes.push_back(*it);
            (*it)->init(context);
        }
        m_newMeshes.clear();

        for (auto it = m_meshes.begin(); it != m_meshes.end(); ++it)
        {
            (*it)->update(context);
        }
	}

    void RainView::addMesh(IMesh* pMesh)
    {
        if (!pMesh)
            return;

        if (m_meshes.find(pMesh) != m_meshes.end())
            return;

        m_newMeshes.push_back(pMesh);
    }

    void RainView::removeMesh(IMesh* pMesh)
    {
        m_newMeshes.erase(pMesh);
        m_meshes.erase(pMesh);
    }
}

