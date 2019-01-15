#include "AABB.h"

namespace Rain {
    AABB::AABB()
    {
    }


    AABB::~AABB()
    {
    }


    void AABB::merge(const Point3D& point)
    {
        m_maxPoint.x = std::max(m_maxPoint.x, point.x);
        m_maxPoint.y = std::max(m_maxPoint.y, point.y);
        m_maxPoint.z = std::max(m_maxPoint.z, point.z);

        m_minPoint.x = std::min(m_minPoint.x, point.x);
        m_minPoint.y = std::min(m_minPoint.y, point.y);
        m_minPoint.z = std::min(m_minPoint.z, point.z);
    }

    void AABB::merge(const AABB& box)
    {
        merge(box.m_minPoint);
        merge(box.m_maxPoint);
    }

    Point3D AABB::center() const
    {
        return (m_minPoint + m_maxPoint) / 2.0f;
    }
    Point3D AABB::min() const
    {
        return m_minPoint;
    }

    Point3D AABB::max() const
    {
        return m_maxPoint;
    }
}


