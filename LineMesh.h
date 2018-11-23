#pragma once

#include "IMesh.h"

namespace Rain
{
    class LineRenderable;

    class LineMesh : public IMesh
    {
    public:
        LineMesh(Point3DList&& vertices, IndexList&& indices);
        ~LineMesh();

        void init(RainContext context) override;
        void update(RainContext context) override;
        void release(RainContext context) override;

    public:
        Point3DList m_vertices;
        IndexList   m_indices;

        LineRenderable * m_pRenderable;
    };
}

