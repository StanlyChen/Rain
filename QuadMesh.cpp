#include "QuadMesh.h"
#include "TirangleRenderable.h"
#include "Layer.h"

namespace Rain
{

    QuadMesh::QuadMesh( Point3DList&& vertices,  IndexList&& indices)
    {
        m_quadIndices.swap(indices);
        m_vertices.swap(vertices);

        size_t quadCout = indices.size()/4;
        m_triangleIndices.reserve( quadCout * 6 );
        for (int i = 0; i < quadCout; ++i)
        {
            m_triangleIndices.push_back(m_quadIndices[4 * i + 0]);
            m_triangleIndices.push_back(m_quadIndices[4 * i + 1]);
            m_triangleIndices.push_back(m_quadIndices[4 * i + 2]);

            m_triangleIndices.push_back(m_quadIndices[4 * i + 0]);
            m_triangleIndices.push_back(m_quadIndices[4 * i + 2]);
            m_triangleIndices.push_back(m_quadIndices[4 * i + 3]);
        }
    }


    QuadMesh::~QuadMesh()
    {

    }

    void QuadMesh::init(RainContext context)
    {
        m_pRenderable = new TriangleRenderable();
        m_pRenderable->create(context.pGLContext, m_vertices, m_triangleIndices);

        context.pView->getMainLayer()->addRenderable(m_pRenderable);

    }

    void QuadMesh::update(RainContext context)
    {
        
    }

    void QuadMesh::release(RainContext context)
    {
        if (m_pRenderable)
        {
            m_pRenderable->destroy(context.pGLContext);
            context.pView->getMainLayer()->removeRenderable(m_pRenderable);
        }
        
    }

}


