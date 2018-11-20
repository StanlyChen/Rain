#pragma once
#include <string>
#include <map>
#include <set>
#include <list>

namespace Rain
{
    class MainWindow;
    class RainView;
    class IMesh;

    struct MeshRecord
    {
        IMesh* pMesh;
        RainView* pView;
    };

    class ModelDisplayManager
    {
    public:
        ModelDisplayManager(MainWindow* pMainWindow);
        ~ModelDisplayManager();

        void importModel(  RainView* pView, std::string& fileName);
        void close(RainView* pView);

    private:
        const MainWindow* m_pMainWindow;
        std::list<MeshRecord> m_meshes;

    };



}

