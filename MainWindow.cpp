#include "MainWindow.h"
#include <QTextEdit>
#include <RainRenderingWindow.h>
#include <QHBoxLayout>

//------test-----------
#include "TriangleMesh.h"
//-------

namespace Rain
{
	MainWindow::MainWindow(QWidget *parent)
		: QMainWindow(parent)
	{
		ui.setupUi(this);

		QWidget* centerWidet = new QWidget(this);
		setCentralWidget(centerWidet);

		m_renderingWindow = new RainRenderingWindow;
		QWidget* pRenderWidget =createWindowContainer(m_renderingWindow, centerWidet);
		pRenderWidget->resize(800, 600);

		QHBoxLayout* layout = new QHBoxLayout;
		layout->addWidget(pRenderWidget);
		centerWidet->setLayout(layout);

		m_view = new RainView();

		connect(m_renderingWindow, SIGNAL(afterRenderingWindowInit(RainRenderingWindow*)), m_view, SLOT(onAfterRenderingWindowInit(RainRenderingWindow*)));
		connect(m_renderingWindow, SIGNAL(beforeRenderingWindowUpdate(RainRenderingWindow*)), m_view, SLOT(onBeforeRenderingWindowUpdate(RainRenderingWindow*)));

        Point3DList vertices;
        Point3D vertex;
        vertex.x = 0;
        vertex.y = 0.5f;
        vertex.z = 0.f;
        vertices.push_back(vertex);
        vertex.x = 0.5;
        vertex.y = -0.5f;
        vertex.z = 0.f;
        vertices.push_back(vertex);
        vertex.x = -0.5;
        vertex.y = -0.5f;
        vertex.z = 0.f;
        vertices.push_back(vertex);

        IndexList indices;
        indices.push_back(0);
        indices.push_back(1);
        indices.push_back(2);

        TriangleMesh* pFirstTriangle = new TriangleMesh(std::move(vertices), std::move( indices) ); 
        m_view->addMesh(pFirstTriangle);

	}
}
