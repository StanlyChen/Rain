#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "RainView.h"
#include "RainRenderingWindow.h"

namespace Rain
{
	class MainWindow : public QMainWindow
	{
		Q_OBJECT

	public:
		MainWindow(QWidget *parent = Q_NULLPTR);

	private:
		Ui::MainWindowClass  ui;
		RainView*            m_view;
		RainRenderingWindow* m_renderingWindow;
	};

}
