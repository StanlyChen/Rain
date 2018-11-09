#pragma once
#include <QObject>

namespace Rain
{
	class RainRenderingWindow;
	class Layer;
	class BackgroundImage;

	class RainView : public QObject
	{
		Q_OBJECT;

	public:
		RainView();
		~RainView();


		RainRenderingWindow* getWindow();

	public slots:
		void onAfterRenderingWindowInit(RainRenderingWindow*);
		void onBeforeRenderingWindowUpdate(RainRenderingWindow*);


	private:
		RainRenderingWindow* m_window = nullptr;
		Layer*               m_backgroundLayer = nullptr;
		Layer*               m_mainLayer = nullptr;
		Layer*               m_overlapLayer = nullptr;
		BackgroundImage*     m_background = nullptr;
	};
}


