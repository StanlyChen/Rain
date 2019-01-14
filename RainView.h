#pragma once
#include <QObject>
#include "OrderList.h"
#include "RainOpenGL.h"
#include "AABB.h"

namespace Rain
{
	class RainRenderingWindow;
	class Layer;
	class BackgroundImage;
    class IMesh;
    class RainView;

    struct RainContext
    {
        RainView* pView;
        RainOpenGLFuncs* pGLContext;
    };

	class RainView : public QObject
	{
		Q_OBJECT;

	public:
		RainView();
		~RainView();


		RainRenderingWindow* getWindow();

    public:
        Layer * getMainLayer() { return m_mainLayer; };
        Layer * getBackroundLayer() { return m_backgroundLayer; };
        Layer * getOverlapLayer() { return m_overlapLayer; };

        void addMesh(IMesh* pMesh);
        void removeMesh(IMesh* pMesh);

	public slots:
		void onAfterRenderingWindowInit(RainRenderingWindow*);
		void onBeforeRenderingWindowUpdate(RainRenderingWindow*);
        void refreshView();

    public:
        const AABB& getBoundingBox();
	private:
		RainRenderingWindow* m_window = nullptr;
		Layer*               m_backgroundLayer = nullptr;
		Layer*               m_mainLayer = nullptr;
		Layer*               m_overlapLayer = nullptr;
		BackgroundImage*     m_background = nullptr;
        
        AABB                 m_bbox;
        bool                 m_bBBoxDirty = false;

        util::OrderList<IMesh*>  m_meshes;
        util::OrderList<IMesh*>  m_newMeshes;
        util::OrderList<IMesh*>  m_deleteMeshes;
	};
}


