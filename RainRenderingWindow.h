#pragma once
#include <QOpenGLWindow>
#include <QTime>
#include "RainOpenGL.h"
#include "RainTypes.h"

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

        void setViewMatrix(const glm::mat4x4 matrix);
        void setProjMatrix(const glm::mat4x4 matrix);


	signals:
		void afterRenderingWindowInit(RainRenderingWindow*);
		void beforeRenderingWindowUpdate(RainRenderingWindow*);
        void onKeyPressEvent(QKeyEvent* ev);
        void onKeyReleaseEvent(QKeyEvent* ev);
        void onMousePressEvent(QMouseEvent* ev);
        void onMouseReleaseEvent(QMouseEvent* ev);
        void onMouseMoveEvent(QMouseEvent* ev);
        void onWheelEvent(QWheelEvent *ev);

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
        glm::mat4           m_projMatrix;
        glm::mat4           m_viewMatrix;

		QOpenGLPaintDevice* m_paintDevice;
		QTime               m_fpsTimer;
		LayerManager*       m_layerManager;

        int                 m_lastFrameTime = 0;
	};
}


