#pragma once
#include "IMesh.h"

namespace Rain
{
    class TriangleRenderable;

    class QuadMesh : public IMesh
    {
    public:
        QuadMesh( Point3DList&& vertices,  IndexList&& indices);
        ~QuadMesh();

        void init(RainContext context) override;
        void update(RainContext context) override;
        void release(RainContext context) override;

    public:
        Point3DList m_vertices;
        IndexList   m_quadIndices;
        IndexList   m_triangleIndices;

        TriangleRenderable * m_pRenderable;
    };


}

