#include "ModelDisplayManager.h"
#include "TriangleMesh.h"
#include "LineMesh.h"
#include "PointMesh.h"
#include "QuadMesh.h"
#include "RainView.h"
#include "MeshProfile.h"


namespace Rain
{
    using RainMeshSerialize = graphicsutil::mesh_profile::MeshSerialize<Point3DList, IndexList>;
    using RainRepData = RainMeshSerialize::RepDataType;

    ModelDisplayManager::ModelDisplayManager(MainWindow* pMainWindow)
        :m_pMainWindow(pMainWindow)
    {

    }


    ModelDisplayManager::~ModelDisplayManager()
    {
    }

    void ModelDisplayManager::loadTestModel(RainView* pView)
    {
        Point3DList vertices;
        Point3D vertex;
        float z_base = 0;
        vertex.x = 0;
        vertex.y = 0.5f;
        vertex.z = z_base + 0.f;
        vertices.push_back(vertex);
        vertex.x = 0.5;
        vertex.y = -0.5f;
        vertex.z = z_base + 0.f;
        vertices.push_back(vertex);
        vertex.x = -0.5;
        vertex.y = -0.5f;
        vertex.z = z_base + 0.f;
        vertices.push_back(vertex);
        vertex.x = 0;
        vertex.y = 0;
        vertex.z = z_base + 0.5f;
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
        Point3DList pointVertices = vertices;

        TriangleMesh * pFirstTriangle = new TriangleMesh(std::move(vertices), std::move(indices));


        MeshRecord record;
        record.pMesh = pFirstTriangle;
        record.pView = pView;
        m_meshes.push_back(std::move(record));

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

        MeshRecord record2;
        record2.pMesh = pLineMesh;
        record2.pView = pView;
        m_meshes.push_back(std::move(record2));


        IndexList pointIndices;
        pointIndices.push_back(0);
        pointIndices.push_back(1);
        pointIndices.push_back(2);
        pointIndices.push_back(3);

        PointMesh* pPointMesh = new PointMesh(std::move(pointVertices), std::move(pointIndices));

        m_meshes.push_back(MeshRecord{ pLineMesh, pView });

        pView->addMesh(pLineMesh);
        pView->addMesh(pPointMesh);
        pView->addMesh(pFirstTriangle);
    }

    void ModelDisplayManager::importModel(RainView* pView,std::string& fileName)
    {
        std::vector<RainRepData> modelData;
        RainMeshSerialize::fromFile(fileName, modelData);
        if (modelData.empty())
        {
            return loadTestModel( pView );
        }
        for (auto& repData : modelData)
        {
            Point3DList vertices = repData.verteices;
            for (auto& tessellation : repData.tessellations)
            {
                Point3DList tmpVertices = vertices;
                IndexList indices= tessellation.connects;
                Rain::IMesh* pMesh = nullptr;
                if (tessellation.primType == graphicsutil::mesh_profile::ENUM_PRIMTYPE_POINT)
                {
                    PointMesh* pPointMesh = new PointMesh(std::move(tmpVertices), std::move(indices));
                    pMesh = pPointMesh;
                }
                else if (tessellation.primType == graphicsutil::mesh_profile::ENUM_PRIMTYPE_LINE)
                {
                    LineMesh* pLineMesh = new LineMesh(std::move(tmpVertices), std::move(indices));
                    pMesh = pLineMesh;
                }
                else if (tessellation.primType == graphicsutil::mesh_profile::ENUM_PRIMTYPE_TRIANGLE)
                {
                    TriangleMesh * pTriangle = new TriangleMesh(std::move(tmpVertices), std::move(indices));
                    pMesh = pTriangle;
                }
                else if(tessellation.primType == graphicsutil::mesh_profile::ENUM_PRIMTYPE_QUAD)
                {
                    QuadMesh * pQuad = new QuadMesh(std::move(tmpVertices), std::move(indices));
                    pMesh = pQuad;
                }
                if (pMesh)
                {
                    MeshRecord record;
                    record.pMesh = pMesh;
                    record.pView = pView;
                    m_meshes.push_back(std::move(record));
                    pView->addMesh(pMesh);
                }

            }
        }


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

