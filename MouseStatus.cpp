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

    void MouseStatus::setPosition(const QPointF f)
    {
        m_mousePosQueue.push_back(f);
    }

    QVector2D MouseStatus::getLastDeltaPosition()
    {
        auto it1 = m_mousePosQueue.rbegin();
        auto it2 = it1+1;
        if (it1 != m_mousePosQueue.rend() && it2 != m_mousePosQueue.rend())
        {
            auto ret =  QVector2D(it1->x() - it2->x(),
                             it1->y() - it2->y());
            return ret;
        }
        return QVector2D(0, 0);
    }
}


