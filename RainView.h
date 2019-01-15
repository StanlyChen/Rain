#pragma once
#include <QObject>
#include "OrderList.h"
#include "RainOpenGL.h"
#include "AABB.h"
#include "MouseStatus.h"
#include "ViewManipulator.h"


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


        void onKeyPress(QKeyEvent* ev);
        void onKeyRelease(QKeyEvent* ev);
        void onMousePress(QMouseEvent* ev);
        void onMouseRelease(QMouseEvent* ev);
        void onMouseMove(QMouseEvent* ev);
        void onWheel(QWheelEvent *ev);


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

        MouseStatus         m_mouseStatus;
        ViewManipulator*    m_viewManipulator;

        util::OrderList<IMesh*>  m_meshes;
        util::OrderList<IMesh*>  m_newMeshes;
        util::OrderList<IMesh*>  m_deleteMeshes;
	};
}


