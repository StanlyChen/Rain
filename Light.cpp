#include "Light.h"

namespace Rain
{
    DirectionLight::DirectionLight(const Point3D& lightColor, const Point3D& direction)
    {
        m_direction = direction;
        m_lightColor = lightColor;
    }

    void DirectionLight::apply(unsigned index, LightInfo* lightsInfo) const
    {
        LightInfo& light = lightsInfo[index];

        light.lightColor[0] = m_lightColor[0];
        light.lightColor[1] = m_lightColor[1];
        light.lightColor[2] = m_lightColor[2];
        light.lightColor[3] = 0;

        light.lightDirection[0] = m_direction[0];
        light.lightDirection[1] = m_direction[1];
        light.lightDirection[2] = m_direction[2];
        light.lightDirection[3] = 1;

    }

    PointLight::PointLight( const Point3D& lightColor, const Point3D& position )
    {
        m_position = position;
        m_lightColor = lightColor;
    }

    void PointLight::apply(unsigned index, LightInfo* lightsInfo) const
    {
        LightInfo& light = lightsInfo[index];

        light.lightColor[0] = m_lightColor[0];
        light.lightColor[1] = m_lightColor[1];
        light.lightColor[2] = m_lightColor[2];
        light.lightColor[3] = 0;

        light.lightPosition[0] = m_position[0];
        light.lightPosition[1] = m_position[1];
        light.lightPosition[2] = m_position[2];
        light.lightDirection[3] = 2;
    }
}