#include <gtc/matrix_transform.hpp>
#include "ViewManipulator.h"
#include "RainRenderingWindow.h"
#include "RainView.h"
#include "AABB.h"

namespace Rain
{

    ViewManipulator::ViewManipulator(RainRenderingWindow* pRenderingWindow)
        :m_pRenderingWindow(pRenderingWindow)
    {
    }


    ViewManipulator::~ViewManipulator()
    {
    }


    void ViewManipulator::fitview(RainView* pView)
    {
        const AABB& box = pView->getBoundingBox();

        m_viewCenter = box.center();
        m_rotateCenter = box.center();
        m_cameraPos = box.center();
        m_cameraPos.z = box.min().z - 10;

        glm::mat4 viewMatrix = glm::mat4();
        viewMatrix = glm::translate(viewMatrix, glm::vec3(-m_cameraPos));

        m_pRenderingWindow->setViewMatrix(viewMatrix);
        m_pRenderingWindow->setProjMatrix(glm::mat4());
    }

    void ViewManipulator::rotate(float pitch, float yaw)
    {

    }

    void ViewManipulator::pan(int x, int y)
    {

    }

    void ViewManipulator::zoomin()
    {

    }

    void ViewManipulator::zoomout()
    {

    }
}

