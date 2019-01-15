#include <gtc/matrix_transform.hpp>
#include "RainRenderingWindow.h"
#include <QOpenGLPaintDevice>
#include < QPainter>
#include "Layer.h"
#include "RainTypes.h"
#include <QWheelEvent>
#include <QMouseEvent>
#include <iostream>
#include "RainView.h"

namespace Rain
{
	RainRenderingWindow::RainRenderingWindow()
		:  QOpenGLWindow()
	{
		m_layerManager = new LayerManager();
        connect(this, SIGNAL(frameSwapped()), this, SLOT(onFrameSwapped()) );
	}

	


	RainRenderingWindow::~RainRenderingWindow()
	{
		if (m_layerManager)
			delete m_layerManager;
	}


	void RainRenderingWindow::initializeGL()
	{
		initializeOpenGLFunctions();

		glClearColor(0, 0, 0, 1);

		m_paintDevice = new QOpenGLPaintDevice;

		emit afterRenderingWindowInit(this);

	}

	void  RainRenderingWindow::resizeGL(int w, int h)
	{
		m_paintDevice->setSize(QSize(w,h));
	}

	void  RainRenderingWindow::paintGL()
	{
		emit beforeRenderingWindowUpdate(this);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		auto layers = m_layerManager->getOrderedLayer();
		for (auto it = layers.rbegin(); it != layers.rend(); ++it )
		{
			(*it)->render( this );
			glClear(GL_DEPTH_BUFFER_BIT);
		}
	}

	void RainRenderingWindow::paintUnderGL()
	{
		m_fpsTimer.restart();
	}

	void RainRenderingWindow::paintOverGL()
	{
		glFlush();
		
		//output FPS
		QPainter painter(m_paintDevice);
        QFont font = painter.font();
        int fontHeight = 15;
        font.setBold(true);
        font.setPixelSize(fontHeight);
        painter.setFont(font);

        painter.setPen(Qt::yellow);
		QString strFrameTime("FrameTime: %1 ms (%2)");

		painter.drawText(QPoint(5, fontHeight), strFrameTime.arg(m_lastFrameTime).arg(m_lastFrameTime ? 1000/m_lastFrameTime : 1000) );
	}

	LayerManager* RainRenderingWindow::getLayerManager()
	{
		return m_layerManager;
	}

    void RainRenderingWindow::onFrameSwapped()
    {
        m_lastFrameTime = m_fpsTimer.restart();
    }

    glm::mat4x4 RainRenderingWindow::getProjMatrix()
    {

        return glm::mat4()/*m_projMatrix*/;
    }

    glm::mat4x4 RainRenderingWindow::getViewMatrix()
    {
        return glm::mat4()/*m_viewMatrix*/;
    }

    glm::mat4x4 RainRenderingWindow::getProjViewMatrix()
    {
        return getProjMatrix()*getViewMatrix();
    }

    void RainRenderingWindow::keyPressEvent(QKeyEvent* ev)
    {
        emit onKeyPressEvent(ev);
    }

    void RainRenderingWindow::keyReleaseEvent(QKeyEvent* ev)
    {
        emit onKeyReleaseEvent(ev);
    }

    void RainRenderingWindow::mousePressEvent(QMouseEvent* ev)
    {
        emit onMousePressEvent(ev);
    }

    void RainRenderingWindow::mouseReleaseEvent(QMouseEvent* ev)
    {
        emit onMouseReleaseEvent(ev);
    }

    void RainRenderingWindow::mouseMoveEvent(QMouseEvent* ev) 
    {
        emit onMouseMoveEvent(ev);
    }

    void RainRenderingWindow::wheelEvent(QWheelEvent *ev)
    {
        emit onWheelEvent(ev);
    }

    void RainRenderingWindow::setViewMatrix(const glm::mat4x4 matrix)
    {
        m_viewMatrix = matrix;
    }

    void RainRenderingWindow::setProjMatrix(const glm::mat4x4 matrix)
    {
        m_projMatrix = matrix;
    }


}
