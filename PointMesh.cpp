#include "PointMesh.h"
#include "PointRenderable.h"
#include "Layer.h"

namespace Rain
{

    PointMesh::PointMesh(Point3DList&& vertices, IndexList&& indices)
    {
        m_indices.swap(indices);
        m_vertices.swap(vertices);
    }


    PointMesh::~PointMesh()
    {

    }

    void PointMesh::init(RainContext context)
    {
        m_pRenderable = new PointRenderable();
        m_pRenderable->create(context.pGLContext, m_vertices, m_indices);

        context.pView->getMainLayer()->addRenderable(m_pRenderable);

    }

    void PointMesh::update(RainContext context)
    {

    }

    void PointMesh::release(RainContext context)
    {
        if (m_pRenderable)
        {
            m_pRenderable->destroy(context.pGLContext);
            context.pView->getMainLayer()->removeRenderable(m_pRenderable);
        }

    }

}


