#pragma once
#include <QOpenGLWindow>
#include <QTime>
#include "RainOpenGL.h"
#include "RainTypes.h"
#include "MouseStatus.h"

namespace Rain
{
	class Layer;
	class LayerManager;
	class RainView;
	
	class RainRenderingWindow : public QOpenGLWindow, public RainOpenGLFuncs
	{
		Q_OBJECT

	public:
		RainRenderingWindow();
		~RainRenderingWindow();

	public:
		void initializeGL() override;
		void resizeGL(int w, int h) override;

		void paintUnderGL() override;
		void paintGL() override;
		void paintOverGL() override;

		LayerManager* getLayerManager();

        glm::mat4x4 getProjMatrix();
        glm::mat4x4 getViewMatrix();
        glm::mat4x4 getProjViewMatrix();

        void zoomin(float delta = 0.05f);
        void zoomout(float delta = 0.05f);
        void rotate(float pitch, float yaw);
        void pan(float right_offset, float up_offset);
        void fitview();

        void setView(RainView* pView) { m_view = pView; }

	signals:
		void afterRenderingWindowInit(RainRenderingWindow*);
		void beforeRenderingWindowUpdate(RainRenderingWindow*);

    protected slots:
        void onFrameSwapped();

    protected:
        void keyPressEvent(QKeyEvent* ev) override;
        void keyReleaseEvent(QKeyEvent* ev) override;

        void mousePressEvent(QMouseEvent* ev) override;
        void mouseReleaseEvent(QMouseEvent* ev) override;
        void mouseMoveEvent(QMouseEvent* ev) override;
        void wheelEvent(QWheelEvent *ev) override;


	protected:
		QOpenGLPaintDevice* m_paintDevice;
		QTime               m_fpsTimer;
		LayerManager*       m_layerManager;
		RainView*           m_view;
        int                 m_lastFrameTime = 0;
        float               m_scale = 1.f;
        MouseStatus         m_mouseStatus;
        glm::mat4x4         m_rotatationMatrix;
        glm::vec2           m_translate;
        float               m_cameraPos = -20;
	};
}


