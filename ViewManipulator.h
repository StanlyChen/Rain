#pragma once
#include "RainTypes.h"


namespace Rain
{
    class RainRenderingWindow;
    class RainView;

    class ViewManipulator
    {
    public:
        ViewManipulator(RainRenderingWindow*);
        ~ViewManipulator();

    public:
        void fitview(RainView* pView);
        void pan(int x, int y);
        void zoomin();
        void zoomout();
        void rotate(float pitch, float yaw);

    public:
        glm::vec3 m_viewCenter;
        glm::vec3 m_rotateCenter;
        glm::vec3 m_cameraPos;

        RainRenderingWindow* m_pRenderingWindow;
    };

}


