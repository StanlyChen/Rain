#include "ModelDisplayManager.h"
#include "TriangleMesh.h"
#include "LineMesh.h"
#include "RainView.h"

namespace Rain
{

    ModelDisplayManager::ModelDisplayManager(MainWindow* pMainWindow)
        :m_pMainWindow(pMainWindow)
    {

    }


    ModelDisplayManager::~ModelDisplayManager()
    {
    }


    void ModelDisplayManager::importModel(RainView* pView,std::string& fileName)
    {
        Point3DList vertices;
        Point3D vertex;
        vertex.x = 0;
        vertex.y = 0.5f;
        vertex.z = 0.f;
        vertices.push_back(vertex);
        vertex.x = 0.5;
        vertex.y = -0.5f;
        vertex.z = 0.f;
        vertices.push_back(vertex);
        vertex.x = -0.5;
        vertex.y = -0.5f;
        vertex.z = 0.f;
        vertices.push_back(vertex);
        vertex.x = 0;
        vertex.y = 0;
        vertex.z = 0.5f;
        vertices.push_back(vertex);

        IndexList indices;
        indices.push_back(0);
        indices.push_back(1);
        indices.push_back(2);

        indices.push_back(3);
        indices.push_back(0);
        indices.push_back(2);

        indices.push_back(0);
        indices.push_back(3);
        indices.push_back(1);

        indices.push_back(3);
        indices.push_back(2);
        indices.push_back(1);

        Point3DList lineVertices = vertices;

        TriangleMesh * pFirstTriangle = new TriangleMesh(std::move(vertices), std::move(indices));
        pView->addMesh(pFirstTriangle);

        MeshRecord record;
        record.pMesh = pFirstTriangle;
        record.pView = pView;
        m_meshes.push_back( std::move(record) );

        IndexList lineIndices;
        lineIndices.push_back(0);
        lineIndices.push_back(1);

        lineIndices.push_back(1);
        lineIndices.push_back(2);

        lineIndices.push_back(2);
        lineIndices.push_back(0);

        lineIndices.push_back(3);
        lineIndices.push_back(0);

        lineIndices.push_back(3);
        lineIndices.push_back(1);

        lineIndices.push_back(3);
        lineIndices.push_back(2);

        LineMesh * pLineMesh = new LineMesh(std::move(lineVertices), std::move(lineIndices));
        pView->addMesh(pLineMesh);

        MeshRecord record2;
        record2.pMesh = pLineMesh;
        record2.pView = pView;
        m_meshes.push_back(std::move(record2));
    }

    void ModelDisplayManager::close(RainView* pView)
    {
        for (auto record : m_meshes)
        {
            if (record.pView == pView)
            {
                pView->removeMesh(record.pMesh);
                //TODO  delay the delete
                //delete record.pMesh;
            }
        }

        m_meshes.erase(std::remove_if(m_meshes.begin(), m_meshes.end(), [pView](MeshRecord& record) 
                                                                        {  return record.pView == pView; }),
                        m_meshes.end());
    }
}

