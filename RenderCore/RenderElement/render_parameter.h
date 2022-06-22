//
// Created by Hong on 2022/2/12.
//

#ifndef ALICEENGINE_RENDER_PARAMETER_H
#define ALICEENGINE_RENDER_PARAMETER_H

#include "RenderBase/engine_math.h"
#include "RenderBase/render_type.h"
#include "buffer_data.h"
#include <variant>

namespace AliceAPI {

using ParamVariant = std::variant<float, double, uint32_t, int32_t, GVec3, GVec4, GVec2, GMat2, GMat3, GMat4, std::string>;


// render params for uniforms in the default uniform block
class RenderParam {
public:
    RenderParam();
    RenderParam(std::shared_ptr<RenderParam> param);
    ~RenderParam();
    void addParam(const TextureType & types, const std::string & name); // the name of color, normal, Bump, Roughness, Metalic
    
    template<typename T>
    void addParam(const std::string & key, const T & vals){
        params_[key] = vals;
    }
    
    template<typename T>
    T * getParamValue(const std::string & name){
        if(params_.find(name)!= params_.end()){
            return & std::get<T>(params_.at(name));
        }
        return nullptr;
    }

    template<typename Func>
    void traverseParams(Func func){
        for(auto const & [key, val]: params_){
            func(key, val);
        }
    }

    inline std::unordered_map<TextureType, std::string> & getTextureParams(){return texture_params_;}
    inline std::unordered_map<std::string, ParamVariant> & getParams(){return params_;}

protected:
    std::unordered_map<TextureType, std::string> texture_params_;
    std::unordered_map<std::string, ParamVariant> params_;
};


/* 
* Global Params for Uniform Block
*/

class RenderGlobalParam{
public:
    RenderGlobalParam();
    ~RenderGlobalParam();

    template<typename T>
    void addGlobalParam(const std::string & key, std::shared_ptr<DataInfo<T>> info){
        if(global_info_.find(key) == global_info_.end()){
            global_info_[key] = info;
        }
    }

    template<typename T>
    std::shared_ptr<DataInfo<T>> getGlobalParam(const std::string & key){
        if(global_info_.find(key) != global_info_.end()){
            return std::static_pointer_cast<DataInfo<T>>(global_info_[key]);
        }
        return nullptr;
    }

protected:
    std::unordered_map<std::string, std::shared_ptr<InfoBase>> global_info_;
};

}


#endif //ALICEENGINE_RENDER_PARAMETER_H
