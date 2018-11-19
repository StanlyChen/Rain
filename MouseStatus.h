#pragma once
#include <QMouseEvent>
#include <boost/circular_buffer.hpp>

namespace Rain
{
    class MouseStatus
    {
    public:
        bool isLeftDown() { return m_bLeftDown && !m_bMiddleDown && !m_bRightDown; }
        bool isRightDown() { return !m_bLeftDown && !m_bMiddleDown && m_bRightDown; }
        bool isMiddleDown() { return !m_bLeftDown && m_bMiddleDown && !m_bRightDown; }

        bool isLeftRightDown() { return m_bLeftDown && m_bRightDown && !m_bMiddleDown; }

        void onMouseButtonPress(Qt::MouseButton btn);
        void onMouseButtonRelease(Qt::MouseButton btn);

        void setPosition(const QPointF f);
        QVector2D getLastDeltaPosition();

    private:
        bool m_bLeftDown = false;
        bool m_bRightDown = false;
        bool m_bMiddleDown = false;

        boost::circular_buffer<QPointF> m_mousePosQueue = boost::circular_buffer<QPointF>(2);
    };
}

