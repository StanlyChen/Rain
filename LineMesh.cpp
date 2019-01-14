#include "LineMesh.h"
#include "LineRenderable.h"
#include "Layer.h"

namespace Rain
{

    LineMesh::LineMesh(Point3DList&& vertices, IndexList&& indices)
    {
        m_indices.swap(indices);
        m_vertices.swap(vertices);
        initBoundingBox(m_vertices, m_indices);
    }


    LineMesh::~LineMesh()
    {

    }

    void LineMesh::init(RainContext context)
    {
        m_pRenderable = new LineRenderable();
        m_pRenderable->create(context.pGLContext, m_vertices, m_indices);

        context.pView->getMainLayer()->addRenderable(m_pRenderable);

    }

    void LineMesh::update(RainContext context)
    {

    }

    void LineMesh::release(RainContext context)
    {
        if (m_pRenderable)
        {
            m_pRenderable->destroy(context.pGLContext);
            context.pView->getMainLayer()->removeRenderable(m_pRenderable);
        }

    }

}


