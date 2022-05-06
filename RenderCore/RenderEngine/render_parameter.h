//
// Created by Hong on 2022/2/12.
//

#ifndef ALICEENGINE_RENDER_PARAMETER_H
#define ALICEENGINE_RENDER_PARAMETER_H

#include "RenderBase/engine_math.h"
#include "RenderBase/render_type.h"
#include <string>
#include <unordered_map>

namespace AliceAPI {


class RenderParam {
public:
    RenderParam();
    ~RenderParam();

    void addParam(const std::string & key, const int32_t & val);
    void addParam(const std::string & key, const float & val);
    void addParam(const std::string & key, const GVec3 & vals);
    void addParam(const std::string & key, const GMat4 & vals);
    void addParam(const TextureType & types, const std::string & name); // the name of color, normal, Bump, Roughness, Metalic

    const std::unordered_map<TextureType, std::string> & getTextureMap();
    const std::unordered_map<std::string, int32_t> & getIntMap();
    const std::unordered_map<std::string, float> & getFloatMap();
    const std::unordered_map<std::string, GVec3> & getVec3Map();
    const std::unordered_map<std::string, GMat4> & getMat4Map();

protected:
    std::unordered_map<TextureType, std::string> texture_params_;
    std::unordered_map<std::string, int32_t> int_params_;
    std::unordered_map<std::string, float> float_params_;
    std::unordered_map<std::string, GVec2> vec2_params_;
    std::unordered_map<std::string, GVec3> vec3_params_;
    std::unordered_map<std::string, GVec4> vec4_params_;
    std::unordered_map<std::string, GMat3> mat3_params_;
    std::unordered_map<std::string, GMat4> mat4_params_;
};

}


#endif //ALICEENGINE_RENDER_PARAMETER_H
