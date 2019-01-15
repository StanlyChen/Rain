#pragma once
#include "RainTypes.h"

namespace Rain {

    class AABB
    {
    public:
        AABB();
        ~AABB();

        void merge(const Point3D& point);
        void merge(const AABB& box);
        Point3D center() const;
        Point3D min() const;
        Point3D max() const;

    private:
        Point3D m_minPoint = glm::vec3();
        Point3D m_maxPoint = glm::vec3();
    };

}


