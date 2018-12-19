#pragma once
#include "RainOpenGL.h"
#include "RainTypes.h"

namespace Rain
{
    class Light()
    {
        virtual void apply(unsigned index, RainOpenGLFuncs* pContext) {};
    }

    class DirectionLights : public Light
    {
    public:
        DirectionLights(Point3D direction, Point3D light);
        void apply(unsigned index, RainOpenGLFuncs* pContext) override;
    }
}