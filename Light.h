#pragma once
#include "RainOpenGL.h"
#include "RainTypes.h"

namespace Rain
{
    struct LightInfo   //pass into the shader
    {
        float lightColor[4];
        union
        {
            float lightDirection[4];
            float lightPosition[4];
        };
    };



    class Light
    {
    public:
        virtual void apply(unsigned index, LightInfo* lightsInfo) const {};
    };

    class DirectionLight : public Light
    {
    public:
        DirectionLight(const Point3D& lightColor, const Point3D& direction );
        void apply(unsigned index, LightInfo* lightsInfo) const override;

    private:
        Point3D m_direction;
        Point3D m_lightColor;
    };

    class PointLight : public Light
    {
    public:
        PointLight(const Point3D& lightColor , const Point3D& position );
        void apply(unsigned index, LightInfo* lightsInfo) const override;

    private:
        Point3D m_position;
        Point3D m_lightColor;
    };


}