#include <gtc/matrix_transform.hpp>
#include "RainRenderingWindow.h"
#include <QOpenGLPaintDevice>
#include < QPainter>
#include "Layer.h"
#include "RainTypes.h"
#include <QWheelEvent>
#include <QMouseEvent>
#include <iostream>

namespace Rain
{
	RainRenderingWindow::RainRenderingWindow()
		:  QOpenGLWindow()
	{
		m_layerManager = new LayerManager();
		m_view = nullptr;

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
        return glm::mat4();
    }

    glm::mat4x4 RainRenderingWindow::getViewMatrix()
    {
        return glm::scale(glm::mat4(), glm::vec3(1.f, 1.f, 1.f)*m_scale)
            * glm::translate(glm::mat4(), glm::vec3( m_translate, 0 ))
            * m_rotatationMatrix;
    }

    void RainRenderingWindow::keyPressEvent(QKeyEvent* ev)
    {

    }

    void RainRenderingWindow::keyReleaseEvent(QKeyEvent* ev)
    {

    }

    void RainRenderingWindow::mousePressEvent(QMouseEvent* ev)
    {
        m_mouseStatus.setPosition(ev->localPos());
        m_mouseStatus.onMouseButtonPress(ev->button());
        if (m_mouseStatus.isLeftRightDown())
            fitview();
    }

    void RainRenderingWindow::mouseReleaseEvent(QMouseEvent* ev)
    {
        m_mouseStatus.setPosition(ev->localPos());
        m_mouseStatus.onMouseButtonRelease(ev->button());
    }

    void RainRenderingWindow::mouseMoveEvent(QMouseEvent* ev) 
    {
        m_mouseStatus.setPosition(ev->localPos());
        if (m_mouseStatus.isMiddleDown())
        {
            QVector2D delta = m_mouseStatus.getLastDeltaPosition();
            //
            float pitchDegree = 720.0f * delta.y() / size().height();
            float yawDegree = 720.0f * delta.x() / size().width();
            rotate(pitchDegree, yawDegree);
        }
        else if (m_mouseStatus.isRightDown())
        {
            QVector2D delta = m_mouseStatus.getLastDeltaPosition();
            //screen's original is at the left-top
            pan(delta.x()*0.01f, -delta.y()*0.01f);
        }
    }

    void RainRenderingWindow::wheelEvent(QWheelEvent *ev)
    {
        // x() is always 0
        float angle = ev->angleDelta().y();
        if (angle == 120) // roll up, zoom in
        {
            zoomin();
        }
        else if ( angle == -120 ) // roll down, zoom out
        {
            zoomout();
        }
        ev->accept();
    }

    void RainRenderingWindow::zoomin( float delta )
    {
        m_scale *= (1+delta);
        update();
    }

    void RainRenderingWindow::zoomout(float delta)
    {
        m_scale *= (1-delta);
        update();
    }

    void RainRenderingWindow::rotate(float pitch, float yaw)
    {
        auto inverseMatrix = glm::inverse(m_rotatationMatrix);
        if (pitch)
        {
            glm::vec4 rotationAxis = inverseMatrix *glm::vec4(1, 0, 0, 0);
            m_rotatationMatrix = glm::rotate(m_rotatationMatrix, glm::radians(pitch), glm::vec3(rotationAxis.x, rotationAxis.y, rotationAxis.z ));
        }
            
        if (yaw)
        {
            glm::vec4 rotationAxis = inverseMatrix * glm::vec4(0, 1, 0, 0);
            m_rotatationMatrix = glm::rotate(m_rotatationMatrix, glm::radians(yaw), glm::vec3(rotationAxis.x, rotationAxis.y, rotationAxis.z) );
        }

        update();
    }

    void RainRenderingWindow::fitview()
    {
        m_scale = 1.f;
        m_rotatationMatrix = glm::mat4x4();
        m_translate = glm::vec2();
        update();
    }

    void  RainRenderingWindow::pan(float right_offset, float up_offset)
    {
        m_translate += glm::vec2(right_offset, up_offset);
        update();
    }
}
