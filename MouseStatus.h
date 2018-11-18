#pragma once
#include <QMouseEvent>

namespace Rain
{
    class MouseStatus
    {
    public:


        bool isLeftDown() { return m_bLeftDown; }
        bool isRightDown() { return m_bRightDown; }
        bool isMiddleDown() { return m_bMiddleDown; }

        bool isLeftRightDown() { return m_bLeftDown && m_bRightDown; }

        void onMouseButtonPress(Qt::MouseButton btn);
        void onMouseButtonRelease(Qt::MouseButton btn);

    private:
        bool m_bLeftDown = false;
        bool m_bRightDown = false;
        bool m_bMiddleDown = false;
    };
}

