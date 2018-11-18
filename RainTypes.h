#pragma once
#include <glm.hpp>
#include <vector>
#include <string>
#include <map>
#include <boost/variant.hpp>

namespace Rain
{
    using Point3D = glm::vec3;
    using Point3DList = std::vector< glm::vec3 >;
    using IndexList = std::vector< unsigned >;

    using ShaderParam = boost::variant<int, float, glm::vec3, glm::mat4x4>;
    using ShaderParams = std::map<std::string, ShaderParam>;
}