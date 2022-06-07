//
// Created by Hong on 2022/2/12.
//

#ifndef ALICEENGINE_RENDER_PARAMETER_H
#define ALICEENGINE_RENDER_PARAMETER_H

#include "RenderBase/engine_math.h"
#include "RenderBase/render_type.h"
#include <variant>

namespace AliceAPI {

using ParamVariant = std::variant<float, double, uint32_t, int32_t, GVec3, GVec4, GVec2, GMat2, GMat3, GMat4, GMat4*, std::string>;

class RenderParam {
public:
    RenderParam();
    ~RenderParam();
    void addParam(const TextureType & types, const std::string & name); // the name of color, normal, Bump, Roughness, Metalic
    
    template<typename T>
    void addParam(const std::string & key, const T & vals){
        params[key] = vals;
    }
    
    template<typename T>
    T * getParamValue(const std::string & name){
        if(params.find(name)!= params.end()){
            return & std::get<T>(params.at(name));
        }
        return nullptr;
    }

    template<typename Func>
    void traverseParams(Func func){
        for(auto & [key, val]: params){
            func(key, val);
        }
    }

protected:
    std::unordered_map<TextureType, std::string> texture_params_;
    std::unordered_map<std::string, ParamVariant> params;
};

}


#endif //ALICEENGINE_RENDER_PARAMETER_H
