#include "MainWindow.h"
#include <QTextEdit>
#include <RainRenderingWindow.h>
#include <QHBoxLayout>

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

	}
}
