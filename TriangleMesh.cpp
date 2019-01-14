#include "TriangleMesh.h"
#include "TirangleRenderable.h"
#include "Layer.h"

namespace Rain
{

    TriangleMesh::TriangleMesh( Point3DList&& vertices,  IndexList&& indices)
    {
        m_indices.swap(indices);
        m_vertices.swap(vertices);

        initBoundingBox(m_vertices, m_indices);
    }


    TriangleMesh::~TriangleMesh()
    {

    }

    void TriangleMesh::init(RainContext context)
    {
        m_pRenderable = new TriangleRenderable();
        m_pRenderable->create(context.pGLContext, m_vertices, m_indices);

        context.pView->getMainLayer()->addRenderable(m_pRenderable);

    }

    void TriangleMesh::update(RainContext context)
    {
        
    }

    void TriangleMesh::release(RainContext context)
    {
        if (m_pRenderable)
        {
            m_pRenderable->destroy(context.pGLContext);
            context.pView->getMainLayer()->removeRenderable(m_pRenderable);
        }
        
    }

}


