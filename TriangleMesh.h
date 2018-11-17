#pragma once
#include "IMesh.h"

namespace Rain
{
    class TriangleRenderable;

    class TriangleMesh : public IMesh
    {
    public:
        TriangleMesh( Point3DList&& vertices,  IndexList&& indices);
        ~TriangleMesh();

        void init(RainContext context) override;
        void update(RainContext context) override;

    public:
        Point3DList m_vertices;
        IndexList   m_indices;

        TriangleRenderable * m_pRenderable;
    };


}

