#pragma once
#include <QOpenGLWindow>
#include <QTime>
#include "RainOpenGL.h"



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

	signals:
		void afterRenderingWindowInit(RainRenderingWindow*);
		void beforeRenderingWindowUpdate(RainRenderingWindow*);

	protected:
		QOpenGLPaintDevice* m_paintDevice;
		QTime               m_fpsTimer;
		LayerManager*       m_layerManager;
		RainView*           m_view;

	};
}


