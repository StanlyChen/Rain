#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "RainView.h"
#include "RainRenderingWindow.h"

namespace Rain
{
    class ModelDisplayManager;

	class MainWindow : public QMainWindow
	{
		Q_OBJECT;

	public:
		MainWindow(QWidget *parent = Q_NULLPTR);

    private:
        void initMenu();

    public slots:
    void actionOpenTriggered(bool checked = false);
    void actionCloseTriggered(bool checked = false);
    void actionEditShaderTriggered(bool checked = false);

	private:
		Ui::MainWindowClass  ui;
		RainView*            m_view = nullptr;
		RainRenderingWindow* m_renderingWindow = nullptr;
        ModelDisplayManager* m_mdm = nullptr;
	};

}
