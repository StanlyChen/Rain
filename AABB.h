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


    private:
        Point3D minPoint = glm::vec3();
        Point3D maxPoint = glm::vec3();
    };

}


