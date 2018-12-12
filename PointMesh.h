#pragma once

#include "IMesh.h"

namespace Rain
{
    class PointRenderable;

    class PointMesh : public IMesh
    {
    public:
        PointMesh(Point3DList&& vertices, IndexList&& indices);
        ~PointMesh();

        void init(RainContext context) override;
        void update(RainContext context) override;
        void release(RainContext context) override;

    public:
        Point3DList m_vertices;
        IndexList   m_indices;

        PointRenderable * m_pRenderable;
    };
}

