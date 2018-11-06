#pragma once

namespace Rain
{
	class RainRenderingWindow;
	class Layer;
	class BackgroundImage;

	class RainView
	{
	public:
		RainView();
		~RainView();

		void onRenderingWindowInit(RainRenderingWindow* );
		void onRenderingWindowUpdate(RainRenderingWindow*);

		RainRenderingWindow* getWindow();

	private:
		RainRenderingWindow* m_window;
		Layer*               m_backgroundLayer;
		Layer*               m_mainLayer;
		Layer*               m_overlapLayer;

		BackgroundImage*     m_background;
	};
}


