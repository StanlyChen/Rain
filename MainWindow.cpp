#include "MainWindow.h"
#include <QTextEdit>
#include <RainRenderingWindow.h>
#include <QHBoxLayout>
#include <QAction>
#include <QFileDialog>
#include "ModelDisplayManager.h"



namespace Rain
{
	MainWindow::MainWindow(QWidget *parent)
		: QMainWindow(parent)
	{
		ui.setupUi(this);

        initMenu();

		QWidget* centerWidet = new QWidget(this);
		setCentralWidget(centerWidet);

		m_renderingWindow = new RainRenderingWindow;
		QWidget* pRenderWidget =createWindowContainer(m_renderingWindow, centerWidet);
		pRenderWidget->resize(800, 600);

		QHBoxLayout* layout = new QHBoxLayout;
		layout->addWidget(pRenderWidget);
		centerWidet->setLayout(layout);

		m_view = new RainView();
        m_mdm = new ModelDisplayManager(this);

		connect(m_renderingWindow, SIGNAL(afterRenderingWindowInit(RainRenderingWindow*)), m_view, SLOT(onAfterRenderingWindowInit(RainRenderingWindow*)));
		connect(m_renderingWindow, SIGNAL(beforeRenderingWindowUpdate(RainRenderingWindow*)), m_view, SLOT(onBeforeRenderingWindowUpdate(RainRenderingWindow*)));
	}

    void MainWindow::initMenu()
    {
        QMenu* menuFile = new QMenu("File", ui.menuBar);
        ui.menuBar->addAction(menuFile->menuAction());

        QAction* actionOpen = new QAction("Open", this);
        menuFile->addAction(actionOpen);
        connect(actionOpen, SIGNAL(triggered(bool)), this, SLOT(actionOpenTriggered(bool)));

        QAction* actionClose = new QAction("Close", this);
        menuFile->addAction(actionClose);
        connect(actionClose, SIGNAL(triggered(bool)), this, SLOT(actionCloseTriggered(bool)));

    }

    void MainWindow::actionOpenTriggered(bool checked/* = false*/)
    {
        QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
        if (fileName.isEmpty())
            return;
        m_mdm->importModel( m_view, fileName.toStdString());

    }

    void MainWindow::actionCloseTriggered(bool checked/* = false*/)
    {
        m_mdm->close(m_view);
    }

}
