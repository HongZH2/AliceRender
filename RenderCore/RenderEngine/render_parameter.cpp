//
// Created by Hong on 2022/2/12.
//

#include "render_parameter.h"

namespace AliceAPI {



RenderParam::RenderParam() {

}

RenderParam::~RenderParam() {

}

void RenderParam::addParam(const std::string & key, const int32_t & val) {
    int_params_[key] = val;
}

void RenderParam::addParam(const std::string & key, const float & val) {
    float_params_[key] = val;
}

void RenderParam::addParam(const TextureType & key, const std::string & tex_name){
    texture_params_[key] = tex_name;
}

void RenderParam::addParam(const std::string & key, const GVec3 & vals) {
    vec3_params_[key] = vals;
}

void RenderParam::addParam(const std::string & key, const GMat4 & vals) {
    mat4_params_[key] = vals;
}

const std::unordered_map<TextureType, std::string> & RenderParam::getTextureMap() {
    return texture_params_;
}

const std::unordered_map<std::string, int> & RenderParam::getIntMap() {
    return int_params_;
}

const std::unordered_map<std::string, float> & RenderParam::getFloatMap() {
    return float_params_;
}

const std::unordered_map<std::string, GVec3> & RenderParam::getVec3Map() {
    return vec3_params_;
}

const std::unordered_map<std::string, GMat4> & RenderParam::getMat4Map() {
    return mat4_params_;
}

}

