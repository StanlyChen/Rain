#include "IMesh.h"

namespace Rain
{

    IMesh::IMesh()
    {
    }


    IMesh::~IMesh()
    {
    }


    void IMesh::initBoundingBox(const Point3DList& vertices, const IndexList& indices)
    {
        for (auto index : indices)
        {
            m_bbox.merge(vertices.at(index));
        }
    }

}



