#include "MouseStatus.h"

namespace Rain
{
    void MouseStatus::onMouseButtonPress(Qt::MouseButton btn)
    {
        switch (btn)
        {
        case Qt::LeftButton:
            m_bLeftDown = true;
            break;
        case Qt::RightButton:
            m_bRightDown = true;
            break;
        case Qt::MiddleButton:
            m_bMiddleDown = true;
            break;
        default:
            break;
        }
    }

    void MouseStatus::onMouseButtonRelease(Qt::MouseButton btn)
    {
        switch (btn)
        {
        case Qt::LeftButton:
            m_bLeftDown = false;
            break;
        case Qt::RightButton:
            m_bRightDown = false;
            break;
        case Qt::MiddleButton:
            m_bMiddleDown = false;
            break;
        default:
            break;
        }
    }
}


