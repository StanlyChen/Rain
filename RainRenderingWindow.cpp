#include "RainRenderingWindow.h"
#include <QOpenGLPaintDevice>
#include < QPainter>
#include "Layer.h"

namespace Rain
{
	RainRenderingWindow::RainRenderingWindow()
		:  QOpenGLWindow()
	{
		m_layerManager = new LayerManager();
	}


	RainRenderingWindow::~RainRenderingWindow()
	{
		if (m_layerManager)
			delete m_layerManager;
	}


	void RainRenderingWindow::initializeGL()
	{
		initializeOpenGLFunctions();

		glClearColor(1, 1, 1, 1);

		m_paintDevice = new QOpenGLPaintDevice;

	}

	void  RainRenderingWindow::resizeGL(int w, int h)
	{
		m_paintDevice->setSize(QSize(w,h));
	}

	void  RainRenderingWindow::paintGL()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		glColor3b(255, 124, 85);
		glBegin(GL_TRIANGLES);
		glVertex3f(-0.5f, -0.5f, 1);
		glVertex3f(0.f, 0.5f, 1);
		glVertex3f(0.5f, -0.5f, 1);
		glEnd();

	}

	void RainRenderingWindow::paintUnderGL()
	{
		m_fpsTimer.restart();
	}

	void RainRenderingWindow::paintOverGL()
	{
		glFlush();
		
		//output FPS
		int frameTime = m_fpsTimer.restart();;
		QPainter painter(m_paintDevice);
		QString strFrameTime("FrameTime: %1 ms (%2)");
		painter.drawText(QPoint(20, 20), strFrameTime.arg(frameTime).arg(frameTime ? 1000/frameTime : 1000) );

	}

	LayerManager* RainRenderingWindow::getLayerManager()
	{
		return m_layerManager;
	}
}
