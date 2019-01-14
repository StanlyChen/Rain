#pragma once
#include "RainTypes.h"
#include "RainView.h"
#include "AABB.h"

namespace Rain
{
    class IMesh
    {
    public:
        IMesh();
        virtual ~IMesh();

    public:
        virtual void init(RainContext context) {} ;
        virtual void update(RainContext context)  {};
        virtual void release(RainContext context) {};
        virtual const AABB& getBoundingBox() { return m_bbox; };

    protected:
        void initBoundingBox(const Point3DList& vertices, const IndexList& indices);
    private:
        AABB m_bbox;
    };

}

