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
		RainRenderingWindow* m_window;
		Layer*               m_backgroundLayer;
		Layer*               m_mainLayer;
		Layer*               m_overlapLayer;

		BackgroundImage*     m_background;
	};
}


